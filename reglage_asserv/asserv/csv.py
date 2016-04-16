import csv

def csv_to_tables(filepath):
    tables = []
    with open(filepath) as csvfile:
        mplab_csv_reader = csv.reader(csvfile)
        for row in mplab_csv_reader:
            current_row = list(map(str.strip, row[:-1]))
            for i,val in enumerate(current_row):
                if i < len(tables):
                    tables[i].append(val)
                else:
                    tables.append([val])
    return tables

def convert(table, elements_type):
    return list(map(elements_type, table))

def import_data(filepath, fields):
    tables = csv_to_tables(filepath)
    return {field[0]:convert(tables[i], field[1]) for i,field in enumerate(fields) if field}
