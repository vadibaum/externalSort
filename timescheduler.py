import argparse
import os
import re
from subprocess import PIPE, run
import sys

results = []
time_re = re.compile('([a-z]+)\s([0-9]+)m([0-9]+\.[0-9]+)s')

def mands(datum):
    """Combines minutes and seconds into seconds total"""
    result = datum['s']
    if datum['m'] > 0:
        result += datum['m'] * 60

    return result

APP = 'externalSort'
COMMAND = 'blockgenerate'
LOOP = 10

prev = None

for N in [int(2 ** i) for i in range(20)]:
    results = []
    for l in range(LOOP):
        script = 'time ./{APP} --{COMMAND} 50 {N} > result.txt'.format(APP=APP, COMMAND=COMMAND, N=N)

        result = run(script, stdout=PIPE, stderr=PIPE, universal_newlines=True, shell=True)
        # CompletedProcess .args .returncode .stdout .stderr
        output = result.stderr
        match = time_re.findall(output)
        # print("match: {}".format(match))
        datum = {
            'real': {'m': int(match[0][1]), 's': float(match[0][2])},
            'user': {'m': int(match[1][1]), 's': float(match[1][2])},
            'sys': {'m': int(match[2][1]), 's': float(match[2][2])},
        }
        exit_code = result.returncode
        if exit_code == 0:
            results.append(datum)
        else:
            print('BREAK: exit_code: {}'.format(exit_code))
            break
        results.append(datum)

    ARR = [mands(e['real']) for e in results]
    SUM = sum(ARR)
    MEAN = SUM / len(ARR)
    if prev:
        ratio = MEAN / prev
        prev = MEAN
        print("{:5d} {:5.5f} {:.5f}".format(N, MEAN, ratio))
    else:
        print("{:5d} {:6.5f}".format(N, MEAN))
        prev = MEAN

