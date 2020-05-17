import matplotlib.pyplot as plt
import common

def run_method_ratios(dist, ratios):
    grin_method = common.get_method('grin')
    berlang_method = common.get_method('berlang')

    xs = []
    ys = []
    ys2 = []
    ys3 = []
    for ratio in ratios:
        print('prog:{}'.format(ratio), end='\r')
        ys.append(common.test_progressive(20, dist, ratio, 0.5)['wait'])
        print('grin:{}'.format(ratio), end='\r')
        ys2.append(grin_method(0.03, 20, dist, ratio, 0.5)['wait'])
        print('berlang:{}'.format(ratio), end='\r')
        ys3.append(berlang_method(0.03, 20, dist, ratio, 0.5)['wait'])
        xs.append(ratio)
        plt.clf()
        plt.plot(xs, ys, xs, ys2, xs, ys3)
        plt.legend(('Progressive wait ratio', 'Grin wait ratio', 'B-Erlang wait ratio'))
        plt.ylabel('Ratio')
        plt.grid(True)
        if (dist == 'E'):
            plt.xlabel('service to setup lambda ratio')
            name='exponentially'
            plt.title('Perfomance with different service to setup lambda ratio.\nBoth distributed ' + name + '.')
        else:
            plt.xlabel('service to setup ratio')
            name='uniformly'
            plt.title('Perfomance with different service to setup ratio.\nBoth distributed ' + name + '.')

        plt.savefig(common.get_time() + 'dist' + 'compare'+ name + '_file.png')
    print('\n')
    


#run_method_ratios('U', [0.1, 0.2, 0.5, 0.7, 0.8, 1, 1.2, 1.3, 1.5, 1.7, 1.9, 2])
#run_method_ratios('E', [0.1, 0.2, 0.5, 0.7, 0.8, 1, 1.2, 1.3, 1.5, 1.7, 1.9, 2])

run_method_ratios('U', [0.8, 1, 1.2])
run_method_ratios('E', [0.8, 1, 1.2])

