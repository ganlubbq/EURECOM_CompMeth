import sys
import matplotlib.pyplot as plt
import csv
import re


argv = sys.argv#[1:-2].sort(key=lambda x:re.findall('\d+', x)[-1])

fig, ax = plt.subplots()
points=[]
#for N in [64, 256, 1024, 4096]:
N=4096
for RUN in range(1):
    filename = sys.argv[1] + '_N_' + str(N) + '_RUN_' + str(RUN) + '.txt'
    points.append([x.split() for x in [line.rstrip('\n') for line in open(filename)]])
#print points

x_points = list(zip(*points[0]))[0]
print list(zip(*points[0]))[1]

y_points = []
for x in range(len(x_points)):
    y_points.append(0)
    for RUN in range(1):
        y_points[x] += float(list(zip(*points[RUN]))[1][x])
    y_points[x] /= 5

lines = plt.plot(x_points, y_points)
plt.show()

for files in sys.argv:

    if files.endswith('.txt'):
        points  = [x.split() for x in [line.rstrip('\n') for line in open(files)]]
        points = list(zip(*points))

        lines = plt.plot(points[0], points[1],  label='N = ' + re.findall('\d+', files)[-1])
        plt.setp(lines, linewidth=1)

legend = plt.legend(loc='upper right', shadow=True)
plt.grid(True)
plt.ylabel('SNR (dB)')
plt.xlabel('Input Signal (dB)')
plt.title('Distortion plot')

ticklines = ax.get_xticklines() + ax.get_yticklines()
gridlines = ax.get_xgridlines() + ax.get_ygridlines()

for line in ticklines:
    line.set_linewidth(3)

for line in gridlines:
    line.set_linestyle(':')

#plt.show()
plt.savefig('./fig/' + sys.argv[-1] + '.pdf')
