#!/usr/bin/python3


from test_runner import run_tests
from test_information import TestInformation


def run_autograder() -> None:
    all_tests = [
        TestInformation("search_tests", "Search Test 1", 5),
        TestInformation("search_tests", "Search Test 2", 5),
        TestInformation("search_tests", "Search Test 3", 5),
        TestInformation("search_tests", "Search Test 4", 5),
        TestInformation("search_tests", "Search Test 5", 5),
        TestInformation("reverse_array_tests", "Reverse 1", 5),
        TestInformation("reverse_array_tests", "Reverse 2", 5),
        TestInformation("reverse_array_tests", "Reverse 3", 5),
        TestInformation("reverse_array_tests", "Reverse 4", 5),
        TestInformation("reverse_array_tests", "Reverse 5", 5),
        TestInformation("word_analysis_tests", "Test 01", 5),
        TestInformation("word_analysis_tests", "Test 02", 5),
        TestInformation("word_analysis_tests", "Test 03", 5),
        TestInformation("word_analysis_tests", "Test 04", 5),
        TestInformation("word_analysis_tests", "Test 05", 5),
        TestInformation("word_analysis_tests", "Test 06", 5),
        TestInformation("word_analysis_tests", "Test 07", 5),
        TestInformation("word_analysis_tests", "Test 08", 5),
        TestInformation("word_analysis_tests", "Test 09", 5),
        TestInformation("word_analysis_tests", "Test 10", 5),
    ]

    files = [
        (f"submission/{name}", f"code/src/{name}")
        for name in [
            "reverse_array.cpp",
            "search.cpp",
            "word_analysis.cpp",
        ]
    ]

    run_tests(files, all_tests)
    

if __name__ == "__main__":
    run_autograder()
