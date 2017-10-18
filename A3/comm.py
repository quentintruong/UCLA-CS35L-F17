# Name: Quentin Truong
# Assignment 3. Modifying and rewriting software
#
# comm.py

import fileinput
import random, sys
from optparse import OptionParser

def parse_options():
    parser = OptionParser()
    parser.add_option("-1", action="store_false", dest="print1", default=True, help="Suppress the output column of lines unique to file1.")
    parser.add_option("-2", action="store_false", dest="print2", default=True, help="Suppress the output column of lines unique to file2.")
    parser.add_option("-3", action="store_false", dest="print3", default=True, help="Suppress the output column of lines duplicated in file1 and file2.")
    parser.add_option("-u", action="store_true", dest="sort", default=False, help="work even if its inputs are not sorted")

    return parser.parse_args(sys.argv[1:])

def read_files(file_inputs):
    file_contents = [[], []]
    file_num = -1

    for line in file_inputs:
        if fileinput.isfirstline():
            file_num += 1
        file_contents[file_num].append(line.rstrip())

    return file_contents

def check_files(file_contents):
    for content in file_contents:
        if not content:
            return False

    return True

def compare_files_sort(file_contents, options):
    tabs = ''

    for line in file_contents[0]:
        if line not in set(file_contents[1]) and options.print1:
            print(line)
        elif line in set(file_contents[1]) and options.print3:
            print('\t\t{}'.format(line))
    for line in file_contents[1]:
        if line not in set(file_contents[0]) and options.print2:
            print('\t{}'.format(line))

def compare_files(file_contents, options):
    tabs = ''

    col1, col2, col3 = {}, {}, {}
    if options.print1:
        col1 = {"{}".format(line): line for line in file_contents[0] if line not in set(file_contents[1])}
        tabs += '\t'

    if options.print2:
        col2 = {"{}{}".format(tabs, line): line for line in file_contents[1] if line not in set(file_contents[0])}
        tabs += '\t'

    if options.print3:
        col3 = {"{}{}".format(tabs, line): line for line in file_contents[0] if line in set(file_contents[1])}

    output = col1
    output.update(col2)
    output.update(col3)

    output = sorted(output, key=output.__getitem__)
    for line in output:
        print(line)


def main():
    options, args = parse_options()

    if len(args) != 2:
        print('Error: Incorrect number of files')
        return

    file_input = fileinput.input(args)
    file_contents = read_files(file_input)

    if not check_files(file_contents):
        print('Error: Incorrect number of files')
        return

    if options.sort:
        compare_files_sort(file_contents, options)
    else:
        compare_files(file_contents, options)


if __name__ == '__main__':
    main()