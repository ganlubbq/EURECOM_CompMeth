import sys
import matplotlib.pyplot as plt
import csv
import re

argv = sys.argv

for files in sys.argv:
    if files.endswith('.txt'):
        points  = [x.split() for x in [line.rstrip('\n') for line in open(files)]]
        points = list(zip(*points))

        plt.plot(points[0], points[1], label='N = ' + re.findall('\d+', files)[1])


legend = plt.legend(loc='upper right', shadow=True)

plt.ylabel('SNR (dB)')
plt.xlabel('Input Signal (dB)')
plt.title('Distortion plot')

plt.savefig('./fig/' + sys.argv[-1] + '.pdf')

#plt.show()

