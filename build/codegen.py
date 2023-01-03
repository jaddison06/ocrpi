import yaml
from io import StringIO
from sys import exit, argv

def codegen():
    if len(argv) != 2: exit('Usage: codegen.py <output file basename>')

    with open('generate.yaml', 'rt') as fh:
        genFile = yaml.safe_load(fh)

    header = StringIO()

    header.write(
'''// GENERATED FILE - DO NOT EDIT
#ifndef GENERATED_H
#define GENERATED_H

''')

    for name, values in genFile['enums'].items():
        header.write('typedef enum {\n')
        for i, value in enumerate(values):
            header.write(f'    {name}_{value} = {i},\n')
        header.write(f'}} {name};\n\n')
        
        header.write(f'char* {name}ToString({name} theEnum);\n\n')
    
    header.write('#endif // GENERATED_H')


    with open(f'{argv[1]}.h', 'wt') as fh:
        fh.write(header.getvalue())


    source = StringIO()

    source.write(f'// GENERATED FILE - DO NOT EDIT\n\n#include "{argv[1]}.h"\n\n')
    for name, values in genFile['enums'].items():
        source.write(f'char* {name}ToString({name} theEnum) {{\n')
        source.write('    char* values[] = {')
        for i, value in enumerate(values):
            source.write(f'"{value}"')
            if i != len(values) - 1:
                source.write(', ')
        source.write('};\n')
        source.write('    return values[theEnum];\n}\n\n')
    

    with open(f'{argv[1]}.c', 'wt') as fh:
        fh.write(source.getvalue())

if __name__ == '__main__': codegen()