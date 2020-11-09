# -*- coding: utf-8 -*-
"""
Created on Fri Nov  6 23:59:25 2020

@author: alfre
"""

def return_function_value(x):
    return x



input_bitdepth = 20
input_signed = True
input_int = 1
input_precision = [input_signed,input_int,input_bitdepth-input_int -int(input_signed)]


#the lookup table will provide a non uniform subdivision of the input range
#based on the curve. this is stored as comparators

lut_address_bitdepth = 10
lut_size = 1 << lut_address_bitdepth



  