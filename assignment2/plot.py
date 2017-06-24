from pprint import pprint
import pandas as pd
import matplotlib.pyplot as plt
import scipy
import sys
import csv
import re

argv = sys.argv

baseline = [256, 512, 1024, 2048, 4096, 8192, 16384, 32768]

scalar_speedup = [1, 1, 1, 1, 1, 1, 1, 1]
sse_speedup = [ 6.37, 8.20, 9.08, 9.92, 10.02, 4.54, 4.49, 4.49 ]
avx_speedup =  [8.59, 12.11, 15.41, 18.02, 18.68,  4.84, 4.72, 4.71]

scalar_avg = [395,  763, 1526, 2956, 5810,11742,23239,46595]
sse_avg = [   62,   93,  168,  298,  580, 2587, 5171,10387]
avx_avg = [  46,  63,  99, 164, 311,2428,4928,9889]


scalar_speedup = [1, 1, 1, 1, 1, 1, 1, 1]
see_speedup = [0.91, 0.84,0.72,0.69,0.64,1.01,0.95,1.02]
avx_speedup = [1.01, 1.31,1.27,1.25,1.20,1.00,0.96,1.00]

scalar_avg = [   70,  102,  155,  268,  487, 2637, 5223, 10799,]
sse_avg = [   77,  122,  215,  389,  765, 2621, 5475,10626,]
avx_avg = [   69,    78,   122,   214,   406,  2645,  5414, 10770, ]
