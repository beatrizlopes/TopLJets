from itertools import product
from json import load
from sys import argv

from lib.submit import QSubmitter as submit

ma = 'beatriz.lopes@desy.de'
mo = False
number = 20 #100
test = False


def KinAlg4Tree(filelist):
    args = [filelist]
    names = filelist
    submit(
        'jobs/KinAlg4tree_{0}.sh'.format(names), filelist=filelist
    )

for arg in argv[1:]:
    if arg in ():
        thejob = locals()[arg]
        if not switchConfignummodel:
            for config in configs:
                json = '{0}/res/hist/Fill{1}.json'.format(submit.cwd(), config)
                with open(json) as f:
                    bcids = load(f)['bcids']
                for i, bcid in enumerate(bcids):
                    for model, version in modelversion:
                        thejob(config, i, model, bcid, json, version)
        else:
            for config, i, model, version in confignummodel:
                json = '{0}/res/hist/Fill{1}.json'.format(submit.cwd(), config)
                with open(json) as f:
                    bcid = load(f)['bcids'][i]
                thejob(config, i, model, bcid, json, version)

    elif arg.startswith('makeHtml'):
        fill = arg[8:]
        names = ['html', fill]
        submit(
            'res/jobs/makeHtml_{0}.sh'.format(fill), names=names, ma=ma, mo=mo,
            rt=1
        )

    elif arg in ('shapeFitter_v3', 'shapeFitter_v4'):
        for config in configs:
            json = '{0}/res/hist/Fill{1}.json'.format(submit.cwd(), config)
            with open(json) as f:
                bcids = load(f)['bcids']
            for i, bcid in enumerate(bcids):
                mymo = mo
                for model, version in modelversion:
                    if version != arg[-2:]:
                        continue
                    for j in range(10, 10+number):
                        if j == 5:
                            mymo = False
                        args = [json, str(bcid), model, str(j)]
                        names = ['sF', str(j)] + config.split('_') + [
                            str(i), model
                        ]
                        submit(
                            'res/jobs/{0}.sh'.format(arg), args=args,
                            names=names, ma=ma, mo=mymo, rt=5
                        )

    elif arg == 'closureTest':
        for i, then in enumerate(n):
            for toy, fit in toyfitmodels:
                mymo = mo
                for j in range(number):
                    if j == 5:
                        mymo = False
                    numb = 100+i*number+j
                    args = [
                        toy, fit, 'basic_{0}'.format(numb), str(0.7), str(n[i])
                    ]
                    names = ['cT', toy, fit, str(numb), version]
                    submit(
                        'res/jobs/closureTest_{0}.sh'.format(version),
                        args=args, names=names, ma=ma, mo=mymo, rt=then*8,
                        vmem='5G'
                    )
