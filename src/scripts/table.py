import argparse
import pandas as pd

from dataclasses import dataclass
from prettytable import PrettyTable
from math import log, e


@dataclass
class Format:
    pretty = 'pretty'
    csv = 'csv'

OUTPUT_PATH = '/home/regina/bmstu/bmstu-diploma/src/scripts/stat/'

EXTENDED_COLUMNS = 15
BASE_COLUMNS = 3
PAGE_SIZE = 4096

SEPARATOR = ': '

def create_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('optimization', choices=['y', 'n'], help='тип сжатия')
    parser.add_argument('logfile', help='системный файл')
    parser.add_argument('format', choices=[Format.pretty, Format.csv], help='формат вывода')
    parser.add_argument('statfile', help='имя файла статистики')

    return parser


def create_pretty_table(fields):
    table = PrettyTable()
    table.field_names = fields

    return table


def parse_lines(optimization, lines):
    columns_num = EXTENDED_COLUMNS if optimization else BASE_COLUMNS
    data = []

    for i, line in enumerate(lines):
        values = line.split(SEPARATOR)[1]
        values = values.split()

        if float(values[-1]) == 0:
            continue

        data.append([i + 1])

        for value in values:
            value = value[:-1] if value[-1] == ',' else value
            data[i].append(value)

        data[i].insert(columns_num, PAGE_SIZE)

        compression_ratio = float(PAGE_SIZE) / float(data[i][-1])
        compression_factor = 1 / compression_ratio
        space_savings = 1 - compression_factor

        if compression_ratio == 1:
            compression_gain = 0
        else:
            compression_gain = 100 * log(compression_ratio)

        data[i].append(compression_ratio)
        data[i].append(compression_factor)
        data[i].append(space_savings)
        data[i].append(compression_gain)

    return data


def get_data(optimization, logfile):
    data = []
    lines = []

    with open(logfile, 'r') as f:
        lines = f.readlines()

    data = parse_lines(optimization, lines)

    return data


def get_table(optimization, logfile, format, statfile):
    fields = ['ID']

    if optimization:
        fields.extend(['SW_ENTROPY', 'SW_TIME',
                       'SW4_ENTROPY', 'SW4_TIME',
                       'B2_ENTROPY', 'B2_TIME',
                       'B4_ENTROPY', 'B4_TIME',
                       'KH_ENTROPY', 'KH_TIME',
                       'KH2_ENTROPY', 'KH2_TIME'])
        
    fields.extend(['COMPRESSION_TIME', 'HANDLING_TIME', 
                   'SIZE', 'COMPRESSED_SIZE',
                   'COMPRESSION_RATIO', 'COMPRESSION_FACTOR',
                   'SPACE_SAVINGS', 'COMPRESSION_GAIN'])

    data = get_data(optimization, logfile)

    if format == Format.pretty:
        table = create_pretty_table(fields)
        table.add_rows(data)
        print(table)
    else:
        df = pd.DataFrame(data, columns=fields)
        vm = 'vm2/' if optimization else 'vm1/'
        df.to_csv(OUTPUT_PATH + vm + statfile + '.csv')


if __name__ == '__main__':
    parser = create_parser()
    args = parser.parse_args()

    if args.optimization == 'y':
        optimization = True
    else:
        optimization = False

    get_table(optimization, args.logfile, args.format, args.statfile)
