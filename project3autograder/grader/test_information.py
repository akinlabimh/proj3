class TestInformation:
    def __init__(self, binary_name, test_name, score):
        self.binary_name = binary_name
        self.test_name = test_name
        self.score = score

    def full_name(self) -> str:
        return self.binary_name + "_" + self.test_name
