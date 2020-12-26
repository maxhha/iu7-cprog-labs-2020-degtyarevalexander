import unittest
from src.array import rotate_array, filter_full_squares_array

class TestArray(unittest.TestCase):

    def test_rotate_array(self):
        self.assertEqual(rotate_array([1, 2, 3, 4, 5], 2), [3, 4, 5, 1, 2])

    def test_rotate_empty_array(self):
        self.assertEqual(rotate_array([], 2), [])

    def test_rotate_array_many_periods(self):
        self.assertEqual(rotate_array([1, 2, 3, 4, 5], 100), [1, 2, 3, 4, 5])

    def test_rotate_array_neg_shift(self):
        with self.assertRaises(Exception) as cm:
            rotate_array([1, 2, 3, 4, 5], -2)

    def test_filter_squares(self):
        self.assertEqual(
            filter_full_squares_array([1, 3, 4, 5, 16, 24, 64]),
            [1, 4, 16, 64])

    def test_filter_squares_negative_element(self):
        self.assertEqual(
            filter_full_squares_array([1, -3, -4, 5, -16, -24, 64]),
            [1, 64])

    def test_filter_squares_empty_result(self):
        self.assertEqual(
            filter_full_squares_array([-3, -4, 5, -16, -24]),
            [])

    def test_filter_squares_empty_array(self):
        self.assertEqual(
            filter_full_squares_array([]),
            [])

if __name__ == "__main__":
    unittest.main()
