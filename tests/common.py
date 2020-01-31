import numpy as np
import matplotlib.pyplot as plt
from subprocess import Popen, PIPE, STDOUT
import subprocess
import numpy

def test_berlang(critical):
    commands = ""
    commands += "generate_data\n"
    commands += "test\n"
    commands += "10000\n"
    commands += "B\n"
    commands += "0.5\n"
    commands += "E\n"
    commands += "0.1\n"
    commands += "E\n"
    commands += "0.1\n"
    commands += "simulate\n"
    commands += "berlang\n"
    commands += str(critical) + "\n"
    commands += "test\n"
    commands += "20\n"
    commands += "0.1\n"
    commands += "exit\n"
    p = Popen(['./build/analyzer'], stdout=PIPE, stdin=PIPE, stderr=STDOUT)
    grep_stdout = p.communicate(input=bytes(commands, 'ascii'))[0]
    result = grep_stdout.decode()
    ret = {}
    ret['wait'] = float(result.split('\n')[-3].split(':')[1])
    ret['abandon'] = float(result.split('\n')[-4].split(':')[1])
    return ret
def test_progressive():
    commands = ""
    commands += "generate_data\n"
    commands += "test\n"
    commands += "10000\n"
    commands += "B\n"
    commands += "0.5\n"
    commands += "E\n"
    commands += "0.1\n"
    commands += "E\n"
    commands += "0.1\n"
    commands += "simulate\n"
    commands += "progressive\n"
    commands += "test\n"
    commands += "20\n"
    commands += "0.1\n"
    commands += "exit\n"
    p = Popen(['./build/analyzer'], stdout=PIPE, stdin=PIPE, stderr=STDOUT)
    grep_stdout = p.communicate(input=bytes(commands, 'ascii'))[0]
    result = grep_stdout.decode()
    ret = {}
    ret['wait'] = float(result.split('\n')[-3].split(':')[1])
    ret['abandon'] = float(result.split('\n')[-4].split(':')[1])
    return ret

critical = 0
xs = []
ys = []
ys2 = []
ys3 = []
ys4 = []
step = 0.03
while critical + step < 1:
    critical += step
    res = test_berlang(critical)
    xs.append(critical)
    ys.append(res['abandon'])
    ys2.append(res['wait'])
    ys3.append(0.03)
    ys4.append(test_progressive()['wait'])
    print(res['abandon'])
    print(res['wait'])
    print(critical)

plt.plot(xs, ys, xs, ys2, xs, ys3, xs, ys4)
plt.legend(('Abandon ratio', 'Wait ratio', '0.03 ratio', 'Progressive wait ratio'))
plt.xlabel('Critical value')
plt.ylabel('Ratio')
plt.grid(True)
plt.title('B-Erlang method perfomance')

plt.savefig('file.png')


