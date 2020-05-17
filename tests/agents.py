import matplotlib.pyplot as plt
import common

def run_method_agents(method, agents):
    grin_method = common.get_method('grin')
    berlang_method = common.get_method('berlang')

    xs = []
    ys = []
    ys2 = []
    ys3 = []
    for agent in agents:
        print('prog:{}'.format(agent), end='\r')
        ys.append(common.test_progressive(agent, 'U', 1, 0.5)['wait'])
        print('grin:{}'.format(agent), end='\r')
        ys2.append(grin_method(0.03, agent, 'U', 1, 0.5)['wait'])
        print('berlang:{}'.format(agent), end='\r')
        ys3.append(berlang_method(0.03, agent, 'U', 1, 0.5)['wait'])
        xs.append(agent)
        plt.clf()
        plt.plot(xs, ys, xs, ys2, xs, ys3)
        plt.legend(('Progressive wait ratio', 'Grin wait ratio', 'B-Erlang wait ratio'))
        plt.xlabel('Agent number')
        plt.ylabel('Ratio')
        plt.grid(True)
        plt.title('Methods ' + ' perfomance with different agent numbers')
        plt.savefig(common.get_time() + 'agents_' + 'compare' + '_file.png')
    print('\n')
    

def make_agents(left, right, step):
    criticals = []
    while left < right:
        criticals.append(left)
        left += step
    return criticals

#run_method_agents('berlang', [1, 2, 3, 5, 8, 10, 15, 20, 25, 30, 35, 40, 50, 60])
run_method_agents('berlang', [20, 25])

