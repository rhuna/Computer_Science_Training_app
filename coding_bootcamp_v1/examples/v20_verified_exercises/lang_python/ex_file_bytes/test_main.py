import unittest
import main
class ExerciseTest(unittest.TestCase):
    def test_expected_token(self):
        self.assertIn("PASS_CS_BOOTCAMP_EXERCISE", main.solve())
if __name__ == "__main__":
    unittest.main()
