# Name: Quentin Truong
# Assignment 3. Modifying and rewriting software
#
# comm.py

import random, sys
from optparse import OptionParser

def parse_options():
    parser = OptionParser()
    parser.add_option("-1", action="store_false", dest="print1", default=True, help="Suppress the output column of lines unique to file1.")
    parser.add_option("-2", action="store_false", dest="print2", default=True, help="Suppress the output column of lines unique to file2.")
    parser.add_option("-3", action="store_false", dest="print3", default=True, help="Suppress the output column of lines duplicated in file1 and file2.")
    parser.add_option("-u", action="store_true", dest="sort", default=False, help="work even if its inputs are not sorted")

    return parser.parse_args(sys.argv[1:])

def read_files(file_names):
    file_contents = [[], []]
    file_num = 0

    for file_name in file_names:
        if file_name == '-':
            for line in sys.stdin.read().splitlines():
                file_contents[file_num].append(line.rstrip())
            file_num += 1
        else:
            with open(file_name) as file:
                for line in file.readlines():
                    file_contents[file_num].append(line.rstrip())
                file_num += 1

    return file_contents

def check_files(file_contents):
    for content in file_contents:
        if not content:
            return False

    return True

def compare_files_sort(file_contents, options):
    tab2 = ''
    tab3 = ''
    if options.print1:
        tab2 += '\t'
        tab3 += '\t'
    if options.print2:
        tab3 += '\t'

    other = file_contents[1][:]
    col1, col2, col3 = [], [], []
    for line in file_contents[0]:
        if line in other:
            other.remove(line)
            print('{}{}'.format(tab3, line))
        else:
            print(line)

    other = file_contents[0][:]
    for line in file_contents[1]:
        if line in other:
            other.remove(line)
        else:
            print('{}{}'.format(tab2, line))

def compare_files(file_contents, options):
    tab2 = ''
    tab3 = ''
    if options.print1:
        tab2 += '\t'
        tab3 += '\t'
    if options.print2:
        tab3 += '\t'

    other = file_contents[1][:]
    col1, col2, col3 = [], [], []
    for line in file_contents[0]:
        if line in other:
            other.remove(line)
            col3.append((line, '{}{}'.format(tab3, line)))
        else:
            col1.append((line, line))

    other = file_contents[0][:]
    for line in file_contents[1]:
        if line in other:
            other.remove(line)
        else:
            col2.append((line, '{}{}'.format(tab2, line)))
    
    out = []
    if options.print2:
        out += col2
    if options.print3:
        out += col3
    if options.print1:
        out += col1
    out = sorted(out, key=lambda x : x[0])
    for tup in out:
        print(tup[1])

def main():
    options, args = parse_options()

    if len(args) != 2:
        print('Error: Incorrect number of files')
        return

    file_contents = read_files(args)

    if not check_files(file_contents):
        print('Error: Incorrect number of files')
        return

    if options.sort:
        compare_files_sort(file_contents, options)
    else:
        compare_files(file_contents, options)


if __name__ == '__main__':
    main()