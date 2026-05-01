import unittest
import main

class TestWordFrequency(unittest.TestCase):
    def test_pass_token(self):
        self.assertIn("PASS_WORD_FREQUENCY", main.solve())

if __name__ == "__main__":
    unittest.main()
