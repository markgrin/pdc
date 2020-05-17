import matplotlib.pyplot as plt
import common

def run_method_busy(busies):
    grin_method = common.get_method('grin')
    berlang_method = common.get_method('berlang')

    xs = []
    ys = []
    ys2 = []
    ys3 = []
    for busy in busies:
        print('prog:{}'.format(busy), end='\r')
        ys.append(common.test_progressive(20, 'U', 1, busy)['wait'])
        print('grin:{}'.format(busy), end='\r')
        ys2.append(grin_method(0.03, 20, 'U', 1, busy)['wait'])
        print('berlang:{}'.format(busy), end='\r')
        ys3.append(berlang_method(0.03, 20, 'U', 1, busy)['wait'])
        xs.append(busy)
        plt.clf()
        plt.plot(xs, ys, xs, ys2, xs, ys3)
        plt.legend(('Progressive wait ratio', 'Grin wait ratio', 'B-Erlang wait ratio'))
        plt.xlabel('busy ratio')
        plt.ylabel('Ratio')
        plt.grid(True)
        plt.title('Methods ' + 'perfomance with different busy ratios')
        plt.savefig(common.get_time() + 'busy' + 'compare'+ 'busy' + '_file.png')
    print('\n')
    


#run_method_busy([0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9])
run_method_busy([0.55, 0.6, 0.65])
