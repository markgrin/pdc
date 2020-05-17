import numpy as np
import matplotlib.pyplot as plt
from subprocess import Popen, PIPE, STDOUT
import subprocess
import numpy
import time

def common_command(dist, ratio, busy):
    commands = ""
    commands += "generate_data\n"
    commands += "test\n"
    commands += "1500\n"
    commands += "B\n"
    commands += str(busy) + "\n"
    if dist == 'E':
        commands += "E\n"
        commands += str(0.1 * ratio) + "\n"
        commands += "E\n"
        commands += "0.1\n"
    elif dist == 'U':
        commands += "U\n"
        commands += "1\n"
        commands += "30\n"
        commands += "U\n"
        commands += "1\n"
        commands += str(30 * ratio) + "\n"
    commands += "simulate\n"
    return commands

def common_spec(agents):
    commands = ""
    commands += "test\n"
    commands += str(agents) + "\n"
    commands += "0.1\n"
    commands += "exit\n"
    return commands

def run_commands(commands):
    best_of = 3
    ret = {}
    ret['limited'] = 0
    ret['wait'] = 0
    ret['abandon'] = 0
    for i in range(best_of):
        p = Popen(['./build/analyzer'], stdout=PIPE, stdin=PIPE, stderr=STDOUT)
        grep_stdout = p.communicate(input=bytes(commands, 'ascii'))[0]
        result = grep_stdout.decode()
        ret['limited'] += float(result.split('\n')[-3].split(':')[1])
        ret['wait'] += float(result.split('\n')[-4].split(':')[1])
        ret['abandon'] += float(result.split('\n')[-5].split(':')[1])
    ret['limited'] /= best_of
    ret['wait'] /= best_of
    ret['abandon'] /= best_of
    time.sleep(1)
    print('sleeping')
    return ret

def test_berlang(critical, agents, dist, ratio, busy):
    commands = common_command(dist, ratio, busy)
    commands += "berlang\n"
    commands += str(critical) + "\n"
    commands += common_spec(agents)
    return run_commands(commands)


def test_progressive(agents, dist, ratio, busy):
    commands = common_command(dist, ratio, busy)
    commands += "progressive\n"
    commands += common_spec(agents)
    return run_commands(commands)

def test_grin(critical, agents, dist, ratio, busy):
    commands = common_command(dist, ratio, busy)
    commands += "grin\n"
    commands += str(1 - critical) + "\n"
    commands += common_spec(agents)
    print('Passing to grin critical:' + str(1 - critical))
    return run_commands(commands)

def get_method(name):
    if name == 'grin':
        return test_grin
    elif name == 'berlang':
        return test_berlang
    return None

def get_nice_name(name):
    if name == 'grin':
        return 'Grin method'
    elif name == 'berlang':
        return 'B-Erlang method'
    return 'Unknown method'

def get_time():
    return './images/' + str(time.time())

