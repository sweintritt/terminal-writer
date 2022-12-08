#!/usr/bin/env python3

import random
import sys
import time

modes = {
    'human': {
        'name': 'human',
        'description': 'Writes like a real person.',
        'characterWait-min': 75,
        'characterWait-max': 375,
        'lineWait-min': 15,
        'lineWait-max': 675
    },
    '80s': {
        'name': '80s',
        'description': 'Prints text like in old movies.',
        'characterWait-min': 5,
        'characterWait-max': 25,
        'lineWait-min': 15,
        'lineWait-max': 675
    },
    '80s-fast': {
        'name': '80s-fast',
        'description': 'Prints text like in old movies, but a bit faster.',
        'characterWait-min': 5,
        'characterWait-max': 15,
        'lineWait-min': 15,
        'lineWait-max': 275
    }, 
    'wc4': {
        'name': 'wc4',
        'description': 'Like the mission screen in Wing Commander 4.',
        'characterWait-min': 45,
        'characterWait-max': 55,
        'lineWait-min': 45,
        'lineWait-max': 75
    }
}


def show_help():
    print('terminal-writer - Reads text from stdin an writes it to stdout like in old movies.\n');
    print('tw [MODE]\n')
    print('Modes:\n')

    for mode in modes:
        print('  {0: <11} {1}'.format(modes[mode]['name'], modes[mode]['description']))

    sys.exit()


def run(mode):
    for line in sys.stdin:
        for i in range(0, len(line)):
            sys.stdout.write(line[i])
            sys.stdout.flush()
            time.sleep(random.uniform(mode['characterWait-min'], mode['characterWait-max']) / 1000.0)
        
        time.sleep(random.uniform(mode['lineWait-min'], mode['lineWait-max']) / 1000.0)


if len(sys.argv) > 1:
    cmd = sys.argv[1];

    if cmd == "help":
        show_help()
    elif cmd in modes:
        run(modes[cmd])
    else:
        print('Unknown mode: ' + cmd)
        print('See \'help\' for more information.')
else:
    print('No mode given')
    print('See \'help\' for more information.')
