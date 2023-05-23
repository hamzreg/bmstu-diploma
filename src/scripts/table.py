import argparse
import pandas as pd

from dataclasses import dataclass
from prettytable import PrettyTable


@dataclass
class Format:
    pretty = 'pretty'
    csv = 'csv'

OUTPUT_PATH = '/home/regina/bmstu/bmstu-diploma/src/scripts/stat/'

COLUMNS_NUM = 5
COLUMNS = {'entropy': 0, 'entropy_time': 1, 
           'compression_time': 0, 'compressed_size': 1, 'handling_time': 2}
PAGE_SIZE = 4096

SEPARATOR = ': '

def create_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('optimization', choices=['y', 'n'], help='тип сжатия')
    parser.add_argument('logfile', help='системный файл')
    parser.add_argument('format', choices=[Format.pretty, Format.csv], help='формат вывода')

    return parser


def create_pretty_table(fields):
    table = PrettyTable()
    table.field_names = fields

    return table


def parse_lines(optimization, lines):
    columns_num = COLUMNS_NUM if optimization else COLUMNS_NUM - 2
    data = []

    page_num = len(lines) // columns_num
    
    for i in range(page_num):
        data.append([i + 1])

        for j in range(columns_num):
            line = lines[i * columns_num + j]
            value = line.split(SEPARATOR)[2]
            value = value.split()[0]

            data[i].append(value)

        data[i][-2], data[i][-1] = data[i][-1], data[i][-2]
        data[i].insert(columns_num, PAGE_SIZE)
        data[i].append(float(data[i][-2]) / float(data[i][-1]))

    return data


def get_data(optimization, logfile):
    data = []
    lines = []

    with open(logfile, 'r') as f:
        lines = f.readlines()

    data = parse_lines(optimization, lines)

    return data


# | ID | ENTROPY | ENTROPY_TIME | COMPRESSION_TIME | HANDLING_TIME | SIZE | COMPRESSED_SIZE | COMPRESSION_RATIO | ... |
# | -- | ------- | ------------ | ---------------- | ------------- | ---- | --------------- | ----------------- | ... |

def get_table(optimization, logfile, format):
    fields = ['ID', 
              'COMPRESSION_TIME', 'HANDLING_TIME', 
              'SIZE', 'COMPRESSED_SIZE',
              'COMPRESSION_RATIO']

    if optimization:
        fields.insert(1, 'ENTROPY')
        fields.insert(2, 'ENTROPY_TIME')

    data = get_data(optimization, logfile)

    if format == Format.pretty:
        table = create_pretty_table(fields)
        table.add_rows(data)
        print(table)
    else:
        df = pd.DataFrame(data, columns=fields)
        vm = 'vm2/' if optimization else 'vm1/'
        df.to_csv(OUTPUT_PATH + vm + 'stat.csv')


if __name__ == '__main__':
    parser = create_parser()
    args = parser.parse_args()

    if args.optimization == 'y':
        optimization = True
    else:
        optimization = False

    get_table(optimization, args.logfile, args.format)
