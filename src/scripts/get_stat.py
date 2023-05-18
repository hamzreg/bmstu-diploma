import argparse

from prettytable import PrettyTable


SEPARATOR = ': '


def create_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('vm', choices=['1', '2'], help='номер виртуальной машины')
    parser.add_argument('stat_type', choices=['time', 'memory'], help='форма статистики')
    parser.add_argument('stat_file', help='файл статистики')

    return parser


def create_table(fields):
    table = PrettyTable()
    table.field_names = fields

    return table


def get_vm1_time(logfile):
    print('ВМ 1: время\n')

    table = create_table(['Страница', 'Обработка (нс)'])
    page = 1

    with open(logfile, 'r') as f:
        for line in f:
            time = line.split(SEPARATOR)[2]
            time = time.split()[0]

            table.add_row([page, time])
            page += 1

    print(table)


def get_vm2_time(logfile):
    print('ВМ 2: время\n')

    table = create_table(['Страница', 'Метод скользящего окна (нс)', 'Обработка (нс)'])
    page, i = 1, 0

    with open(logfile, 'r') as f:
        entropy_time, handling_time = '', ''

        for line in f:
            time = line.split(SEPARATOR)[2]
            time = time.split()[0]

            if i % 2 == 0:
                entropy_time = time
            else:
                handling_time = time
                table.add_row([page, entropy_time, handling_time])
                page += 1

            i += 1

    print(table)


def get_memory(logfile):
    with open(logfile, 'r') as f:
        line = f.read()

    line = ' '.join(line.split())
    line = line.split()

    table = create_table(['X', 'Xсж', 'Kсж'])
    k = float(line[0]) / float(line[1])
    table.add_row([line[0], line[1], str(k)])

    print(table)


if __name__ == '__main__':
    parser = create_parser()
    args = parser.parse_args()

    if args.stat_type == 'time':
        if args.vm == '1':
            get_vm1_time(args.stat_file)
        elif args.vm == '2':
            get_vm2_time(args.stat_file)
    elif args.stat_type == 'memory':
        print(f'ВМ {args.vm}: память\n')
        get_memory(args.stat_file)
