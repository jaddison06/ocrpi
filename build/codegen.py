import yaml
from io import StringIO

def codegen():
    with open('generate.yaml', 'rt') as fh:
        genFile = yaml.safe_load(fh)

    sio = StringIO()

    sio.write(
'''// GENERATED FILE - DO NOT EDIT
#ifndef GENERATED_H
#define GENERATED_H

''')

    for name, values in genFile['enums'].items():
        sio.write('typedef enum {\n')
        for i, value in enumerate(values):
            sio.write(f'    {value} = {i},\n')
        sio.write(f'}} {name};\n\n')
        sio.write(f'char* {name}ToString({name} theEnum) {{\n')
        sio.write('    char* values[] = {')
        for i, value in enumerate(values):
            sio.write(f'"{value}"')
            if i != len(values) - 1:
                sio.write(', ')
        sio.write('};\n');
        sio.write('    return values[theEnum];\n}\n\n')
    

    sio.write('#endif // GENERATED_H')


    with open(genFile['config']['out'], 'wt') as fh:
        fh.write(sio.getvalue())

if __name__ == '__main__': codegen()