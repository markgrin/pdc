import matplotlib.pyplot as plt
import common

def run_method_critical(method, criticals):
    method_run = common.get_method(method)
    xs = []
    ys = []
    ys2 = []
    ys3 = []
    ys4 = []
    ys5 = []
    for critical in criticals:
        print('Running with critical:{}'.format(critical))
        res = method_run(critical, 20, 'U', 1, 0.5)
        xs.append(critical)
        ys.append(res['abandon'])
        ys2.append(res['wait'])
        ys3.append(0.03)
        ys4.append(common.test_progressive(20, 'U', 1, 0.5)['wait'])
        ys5.append(res['limited'])
        print(critical, end='\r')
    
        plt.clf()
        plt.plot(xs, ys, xs, ys2, xs, ys3, xs, ys4, xs, ys5)
        plt.legend(('Abandon ratio', 'Wait ratio', '0.03 ratio', 'Progressive wait ratio', 'Progressive limited ratio'))
        plt.xlabel('Critical value')
        plt.ylabel('Ratio')
        plt.grid(True)
        plt.title(common.get_nice_name(method) + ' perfomance with different critical values')
        
    plt.savefig(common.get_time() + 'critical_' + method + '_file.png')
    print('\n')

def make_criticals(left, right, step):
    criticals = []
    while left < right:
        criticals.append(left)
        left += step
    return criticals

#run_method_critical('berlang', [0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2])
#run_method_critical('grin', [0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2])

run_method_critical('berlang', [0.02, 0.03, 0.04])
run_method_critical('grin', [0.02, 0.03, 0.04])

