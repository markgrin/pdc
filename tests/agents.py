import matplotlib.pyplot as plt
import common

def run_method_agents(method, agents):
    method_run = common.get_method(method)
    xs = []
    ys = []
    ys2 = []
    ys3 = []
    ys4 = []
    ys5 = []
    for agent in agents:
        res = method_run(0.03, agent)
        xs.append(agent)
        ys.append(res['abandon'])
        ys2.append(res['wait'])
        ys3.append(0.03)
        ys4.append(common.test_progressive(agent)['wait'])
        ys5.append(res['limited'])
        print(agent, end='\r')
        plt.clf()
        plt.plot(xs, ys, xs, ys2, xs, ys3, xs, ys4, xs, ys5)
        plt.legend(('Abandon ratio', 'Wait ratio', '0.03 ratio', 'Progressive wait ratio', 'Progressive limited ratio'))
        plt.xlabel('Agent number')
        plt.ylabel('Ratio')
        plt.grid(True)
        plt.title(common.get_nice_name(method) + ' perfomance with different agent numbers')
        plt.savefig('agents_' + method + '_file.png')
    print('\n')
    

def make_agents(left, right, step):
    criticals = []
    while left < right:
        criticals.append(left)
        left += step
    return criticals

run_method_agents('berlang', [5, 10, 14, 20, 25, 30, 35, 40, 50, 60, 65, 70, 75, 80, 90, 100])
run_method_agents('grin', [5, 10, 14, 20, 25, 30, 35, 40, 50, 60, 65, 70, 75, 80, 90, 100])

