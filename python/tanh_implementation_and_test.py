# -*- coding: utf-8 -*-
"""
Created on Wed Nov 11 18:57:18 2020

@author: alfredo

@brief: 
"""

import matplotlib.pyplot as plt
import numpy as np

plt.close('all')


lut_precision = 21
lut_full = 10

def ttp_lut_inverse( n ):
    
    # the range of the input in bits - 8    
    r = np.zeros(n.shape)
    for nidx in range(0 , r.shape[0]):
        
        if n[nidx] == 0:
            n[nidx] = 1
        
        # this is just a very quick (and very bad) implementation of a bit range finder for the sake of the exercise.
        # hopefully I will have time to code something better. on top of my head, a set of comparators would do
        # because the input is bandwidth (bitdepth) bound. 
        if n[nidx] > pow(2.0, lut_full) - 1:
            r[nidx] = (np.floor(np.log2( n[nidx] )) - lut_full ) + 1
        
        if r[nidx] < 0: 
            r[nidx]  = 0
        
    # simulate the input range right bitshift
    n_ishift = np.floor(n * pow(2.0, -r)) 
    
    # print('n_ishift = ',  n_ishift)
    
    #8 bit lookup table output
    lut_output = np.floor(pow(2.0 , lut_precision)/n_ishift)
    
    #rescaling for range
    lut_output_resc = lut_output * pow(2.0 , -r)
    
    return lut_output_resc

def clamp( x, minx, maxx ):

    if (x < minx):
        return minx
    
    elif (x > maxx):
        return maxx
    
    else:
        return x

def ttp_tanh( x, gain ):
    
    #calculate the square and apply round and clip point
    x_sq = x *x
    
    #clamp x_sq to remove asymmetry
    x_sq_cl = np.clip(x_sq, 0, pow(2.0,32)-1)
        
    #apply squared gain
    xg = x_sq * (gain**2)
    
    #apply round and clip point
    xg_rc = np.floor(xg *pow(2.0, -15 -8))
    
    plt.figure('xg_rc')
    plt.plot( x/pow(2.0, 15), xg_rc/pow(2.0, 15))
    plt.show()
        
    # calculate (27 + xg)
    numerator = 27*pow(2.0,15) + xg_rc
    
    plt.figure('numerator')
    plt.plot( x/pow(2.0, 15), numerator/pow(2.0, 15))
    plt.show()
    
    #calculate denominator (n in the doc)
    denominator = numerator + xg_rc * pow(2.0 , 3)
    plt.figure('denominator')
    plt.plot( x/pow(2.0, 15), denominator/pow(2.0, 15))
    plt.show()
    
    # calculate the inverse m
    m = ttp_lut_inverse(denominator)
    
    #multiply the inverse and the numerator
    ratio = m*numerator
    plt.figure('ratio')
    plt.plot( x/pow(2.0, 15), ratio)
    plt.show()
        
    # renormalise for lut precision rc point
    ratio_norm = np.floor(ratio * pow(2.0, - lut_precision + 16));
    
    plt.figure('ratio norm')
    plt.plot( x/pow(2.0, 15), ratio_norm/pow(2.0, 16))
    plt.show()
    
    #multiply by x    
    y_rc = x * ratio_norm
        
    #apply output rc
    y_out = np.floor(y_rc * pow(2.0, - 16))
    
    
    return y_out
    
#------------------------------------------------------------------------------
def test_inverse():
    
    #generate a unsigned range
    x_in = np.arange( 1, pow(2.0, 16) -1, 16 )
    
    # fixed point. x = 256 => x_norm = 1.0 , x =1 => x_norm = 1.0/256.0    
    x_norm = x_in/pow(2.0,8) 
    
    
    # fixed point     
    y = ttp_lut_inverse(x_in) * pow(2.0, -lut_precision)# + 16) uncomment for integ representation 
    y_approx = y * pow(2.0,8) # so that ttp_lut_inverse(1) = 1/(1/256) = 256 and ttp_lut_inverse(256) = 1, ttp_lut_inverse(512) = 2 etc
        
    y_ideal = 1/x_norm 
    
    plt.figure('inverse')
    plt.plot( x_norm, y_ideal,'-b') 
    plt.plot( x_norm, y_approx,':r')
    plt.xscale('log')
    plt.yscale('log')
    plt.show()
    
    plt.figure('diff (log2)')
    plt.plot( x_norm, np.log2( pow(2.0,16) * np.abs(y_approx - y_ideal)),'-b') 
    plt.xscale('log')
    
    plt.figure('diff (float)')
    plt.plot( x_norm, np.abs(y_approx - y_ideal),'-b') 
    plt.xscale('log')

    plt.figure('diff (relative)')
    plt.plot( x_norm, np.abs(y_approx - y_ideal)/y_ideal,'-b') 
    plt.xscale('log')

#------------------------------------------------------------------------------
def test_tanh():
    
    #generate a fixed point ramp [-1,1). fractional precision 15 bit        
    x_in = np.arange( 0, pow(2.0, 16) -1, 64 )
    
    #convert to sign
    x_in_s = x_in - pow(2.0,15)
    
    
    gain = 1.0
    # calculate gain in fixed precision
    gain_fp = np.floor(gain *pow(2.0, 8)) / pow(2.0, 4)
    
    #apply tanh
    y = ttp_tanh(x_in_s, gain_fp)
    
    y_norm = y*pow(2.0,-(15 ))
    
    # reference
    x_in_s_norm = x_in_s/pow(2,15)
    y_approx = x_in_s_norm*(27 + pow(x_in_s_norm,2.0))/(27  + 9*pow(x_in_s_norm, 2.0))    
    
    
    plt.figure('y')
    #plt.plot( x_in_s/pow(2.0,15), y_approx, 'b')
    plt.plot( x_in_s/pow(2.0,15), y_norm, 'r')
    plt.show()
    
    
    plt.figure('abs diff')
    plt.plot( x_in_s/pow(2.0,15), np.abs(y_norm - y_approx))
    plt.show()
    
    
    return

#-----------------------------------------------------------------------------

x = np.arange(-1.0, 1.0, 0.0001)

y_ideal = np.tanh(x)
y_approx = x*(27 + pow(x,2.0))/(27  + 9*pow(x, 2.0))
plt.figure('reference')
plt.plot(x, y_ideal, '-b')
plt.plot(x, y_approx, '-r')

test_inverse()
test_tanh()






