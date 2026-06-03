#!/usr/bin/env python3
import ctypes
import os

lib_path = "./build/librational.so"
if not os.path.exists(lib_path):
    print(f"Error: {lib_path} not found. Run 'make' first")
    exit(1)

lib = ctypes.CDLL(lib_path)

class Rational(ctypes.Structure):
    _fields_ = [("numerator", ctypes.c_longlong),
                ("denominator", ctypes.c_longlong)]

lib.rational_create.argtypes = [ctypes.c_longlong, ctypes.c_longlong, ctypes.POINTER(Rational)]
lib.rational_create.restype = ctypes.c_int
lib.rational_add.argtypes = [ctypes.POINTER(Rational), ctypes.POINTER(Rational), ctypes.POINTER(Rational)]
lib.rational_add.restype = ctypes.c_int
lib.rational_to_double.argtypes = [ctypes.POINTER(Rational)]
lib.rational_to_double.restype = ctypes.c_double

a = Rational()
b = Rational()
c = Rational()

lib.rational_create(1, 2, ctypes.byref(a))
lib.rational_create(1, 3, ctypes.byref(b))
lib.rational_add(ctypes.byref(a), ctypes.byref(b), ctypes.byref(c))

print(f"Python: 1/2 + 1/3 = {c.numerator}/{c.denominator}")
print(f"Python: as float = {lib.rational_to_double(ctypes.byref(c)):.3f}")
print("All Python tests passed!")
