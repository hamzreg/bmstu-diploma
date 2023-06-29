import argparse

from prettytable import PrettyTable


def create_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('vm1', help='файл первой вм')
    parser.add_argument('vm2', help='файл второй вм')

    return parser


def create_pretty_table(fields):
    table = PrettyTable()
    table.field_names = fields

    return table


def get_data(file):
    data = []
    lines = []

    with open(file, 'r') as f:
        lines = f.readlines()

    lines = lines[0].split()

    data.append(int(lines[0]))
    data.append(int(lines[1]))
    data.append(int(lines[5]))    
    data.append(int(lines[7]))

    return data


def get_table(vm1, vm2):
    fields = ['Исходный объем (Б)', 'Объем сжатых (Б)',
              'С повторяющимся элементом (стр)', 'Несжимаемые (стр)']

    data1 = [get_data(vm1)]
    data2 = [get_data(vm2)]

    table1 = create_pretty_table(fields)
    table1.add_rows(data1)

    table2 = create_pretty_table(fields)
    table2.add_rows(data2)

    print('Без оптимизации:\n')
    print(table1)

    print('\nС оптимизацией:\n')
    print(table2)


if __name__ == '__main__':
    parser = create_parser()
    args = parser.parse_args()

    get_table(args.vm1, args.vm2)
