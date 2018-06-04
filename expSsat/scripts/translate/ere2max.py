import numpy as np
import sys

eVars = []
rVars = []
var_num = None
cls_num = None
start = True
beforeInd = True

with open(sys.argv[1], 'r') as f1:
    with open(sys.argv[2], 'w') as f2:
        f2.write('c generated by ere2max.py\n')
        for idx, line in enumerate(f1):
            if line[0] not in 'cpera':
                if start:
                    f2.write('p cnf %s %s\n' % (var_num, cls_num))
                    start = False
                f2.write(line)
                continue

            if line[-1] == '\n':
                line = line[:-1]

            if line[:5] == 'p cnf':
                var_num, cls_num = map(int, line[5:].split())
            elif line[0] == 'e':
                if beforeInd:
                    tmp = [ ch for ch in line.split(' ') if ch.isdigit() ]
                    f2.write('c max ' + ' '.join(tmp) + '\n')
            elif line[0] == 'r':
                beforeInd = False
                tmp = [ ch for ch in line.split(' ') if ch.isdigit() ]
                f2.write('c ind ' + ' '.join(tmp) + '\n')
