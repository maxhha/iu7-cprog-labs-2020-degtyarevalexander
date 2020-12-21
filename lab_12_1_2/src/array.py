from ctypes import c_void_p, c_size_t, c_int, POINTER, sizeof
import ctypes

LIB = ctypes.CDLL("deps/array/libarr.so")

LIB.rotate.argtypes = [
    c_void_p,
    c_size_t,
    c_size_t,
    c_size_t
]

LIB.rotate.restype = c_int

LIB.copy_full_squares.argtypes = [
    POINTER(c_int),
    c_size_t,
    POINTER(c_int),
]
LIB.copy_full_squares.restype = c_size_t

def rotate_array(a, shift):
    if len(a) == 0:
        raise Exception("Пустой массив")

    if shift < 0:
        raise Exception("Отрицательный сдвиг")

    c_a = (c_int * len(a))(*a)

    rc = LIB.rotate(
        c_a,
        c_size_t(len(c_a)),
        c_size_t(sizeof(c_int)),
        c_size_t(shift)
    )

    if rc:
        raise Exception("libarr.so: не получилось сдвинуть")

    return [i for i in c_a]

def filter_full_squares_array(a):
    c_a = (c_int * len(a))(*a)

    n = LIB.copy_full_squares(c_a, c_size_t(len(c_a)), None)

    if n == 0:
        return []

    c_result = (c_int * n)()
    LIB.copy_full_squares(c_a, c_size_t(len(c_a)), c_result)

    return [i for i in c_result]
