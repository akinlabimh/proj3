import json
import os
import shutil
from subprocess import Popen, PIPE
import subprocess
import time
from typing import List, Dict


from test_information import TestInformation

BUILD_PATH = "build"

class RunResult:
    def __init__(self, success, msg, stderr, stdout):
        self.success = success
        self.msg = msg
        self.stderr = stderr
        self.stdout = stdout


class StopClock:
    def __init__(self):
        self.start_time = time.time()

    def time_elapsed_s(self):
        return time.time() - self.start_time


def process_proc(proc_handle) -> RunResult:
    try:
        # anything over 2 seconds will be considered a failure
        result = proc_handle.wait(2)
        success = proc_handle.returncode == 0
        msg = "Succeed" if success else "Failed with exit code of : " + proc_handle.return_code
    except subprocess.TimeoutExpired as timeout:
        success = False
        msg = "Timed out"
    except Exception as ex:
        success = False
        msg = "Encountered exception: " + str(ex)
    return RunResult(success, msg, proc_handle.stderr, proc_handle.stdout)
        

def compile(base_path: str) -> None:
    result = subprocess.run(["cmake", f"{base_path}/code", f"-B{BUILD_PATH}"])
    print("Configuring Result: {}".format(result.returncode))
    if result.returncode != 0:
        raise Exception("Configuring Failed")

    result = subprocess.run(["cmake", "--build", "build"])
    print("Compilation Result: {}".format(result.returncode))
    if result.returncode != 0:
        raise Exception("Compilation Failed")

def dump_results(output: Dict) -> None:
    with open("results/results.json", "w") as result_file:
            result_file.write(json.dumps(output))


def copy_files(to_copy: List, base_path: str) -> None:
    for ori, dst in to_copy:
        shutil.copyfile(ori, "{}/{}".format(base_path, dst))


def run_tests(to_copy: List, all_tests: List) -> None:
    base = (os.getenv("AUTOGRADER_SOURCE") or ".") + "/source"
    run_tests_impl(to_copy, all_tests, base)


def blank_output(stop_clock) -> Dict:
    output = {}
    output["execution_time"] = stop_clock.time_elapsed_s()
    output["visibility"] = "hidden"
    output["stdout_visibility"] = "hidden"
    output["extra_data"] = None 
    return output


def run_tests_impl(to_copy: List, all_tests: List, base_path: str) -> None:
    start = StopClock()
    try:
        copy_files(to_copy, base_path)
    except Exception as ex:
        print(str(ex))
        output = blank_output(start)
        output["score"] = 0
        output["output"] = str(ex)
        dump_results(output)
        return

    try:
        compile(base_path)
    except Exception as ex:
        print(str(ex))
        output = blank_output(start)
        output["score"] = 0
        output["output"] = str(ex)
        dump_results(output)
        return

    procs = {
        test:
        Popen(
            [f"{BUILD_PATH}/{test.binary_name}", f"\"{test.test_name}\""],
            stdout=PIPE, 
            stderr=PIPE,
        )
        for test in all_tests
    }

    run_results = {
        test: process_proc(proc_handle)
        for test, proc_handle in procs.items()
    }

    for test, result in run_results.items():
        print("Test {}: {}".format(
            test.full_name(),
            "succeed" if result.success else "failed",
        ))
        if not result.success:
            print(result.stdout.read(10000))
            print(result.stderr.read(10000))

    execution_time = 10
    output = blank_output(start)
    output["output"] = "Text relevant to the entire submission"
    output["tests"] = [
        {
            "score": test.score if run_results[test].success else 0,
            "max_score": test.score,
            "name": test.full_name(),
        }
        for test in all_tests
    ]
    dump_results(output)
    