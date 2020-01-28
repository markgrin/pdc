import matplotlib
import matplotlib.pyplot
from subprocess import Popen, PIPE, STDOUT
import subprocess

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
    ret['wait'] = result.split('\n')[-3].split(':')[1]
    ret['abandon'] = result.split('\n')[-4].split(':')[1]
    return ret

critical = 0
xs = []
ys = []
ys2 = []
step = 0.05
while critical + step < 1:
    critical += step
    res = test_berlang(critical)
    xs.append(critical)
    ys.append(res['abandon'])
    ys2.append(res['wait'])
    print(critical)

matplotlib.pyplot.plot(xs, ys, 'ro', xs, ys2, 'ro')
matplotlib.pyplot.legend(('Abandon ratio', 'Wait ratio'))

matplotlib.pyplot.savefig('file.png')

