# https://gist.github.com/jaddison06/eaf1a5760e484d4de9ce7256f3d95ee4

import os
import os.path as path
from sys import argv
from shutil import rmtree
from platform import system

def makefile_item(name: str, dependencies: list[str], commands: list[str]) -> str:
    out = f'{name}:'
    for dep in dependencies: out += f' {dep}'
    for cmd in commands: out += f'\n	{cmd}'
    out += '\n\n'
    return out

def all_with_extension(*exts: str) -> list[str]:
    exts_list = list(exts)
    for i, ext in enumerate(exts_list):
        if not ext.startswith('.'): exts_list[i] = f'.{ext}'

    out: list[str] = []

    for (dirpath, _, filenames) in os.walk('.'):
        for file in filenames:
            if path.splitext(file)[1] in exts_list: out.append(f'{dirpath}/{file}')

    return out

COMPILER = 'gcc'
DEBUG_DEFINES: dict[str, str] = {'OCRPI_DEBUG': '1'}
LIBS: dict[str, list[str]] = {}
EXECUTABLE = 'ocrpi'
SOURCE_EXTS = ['.c']
HEADER_EXTS = ['.h']
PYTHON = 'python'
CLOC = 'C:/Users/jjadd/Downloads/cloc-1.92.exe' if system() == 'Windows' else 'cloc'
CODEGEN_OUTPUT = './generated'
# If these files change, recompile EVERYTHING
COMMON_DEPENDENCIES = []

def fs_util():
    match argv[1]:
        case 'rm_file':
            if path.exists(argv[2]):
                os.remove(argv[2])
        case 'rm_dir':
            if path.exists(argv[2]):
                rmtree(argv[2])
        case 'mkdir':
            if not path.exists(argv[2]):
                os.makedirs(argv[2])
        case _: pass
    
def fs_cmd(*args: str) -> str:
    return f'{PYTHON} build/generate-makefile.py {" ".join(args)}'

def main():
    if len(argv) > 1:
        fs_util()
        exit(0)
    
    source_files = all_with_extension(*SOURCE_EXTS)
    headers = {path.splitext(header)[0]: header for header in all_with_extension(*HEADER_EXTS)}

    makefile = ''

    objects: list[str] = []
    debug_objects: list[str] = []

    defines_str = ''
    for k, v in DEBUG_DEFINES.items():
        defines_str += f'-D {k}={v} '
    defines_str = defines_str.strip()

    if f'{CODEGEN_OUTPUT}.c' not in source_files:
        print('generated files not found!!')
        source_files.append(f'{CODEGEN_OUTPUT}.c')
        headers[CODEGEN_OUTPUT] = f'{CODEGEN_OUTPUT}.h'

    for file in source_files:
        dirname = 'build/objects/' + path.dirname(file)
        base = path.splitext(file)[0]
        obj_name       = 'build/objects/' + base + '.o'
        debug_obj_name = 'build/objects/' + base + '-debug.o'
        dependencies = [file]
        if base in headers: dependencies.append(headers[base])
        dependencies += COMMON_DEPENDENCIES

        makefile += makefile_item(obj_name,       dependencies, [fs_cmd('mkdir', dirname), f'{COMPILER} -c {file} -I. -o {obj_name}'])
        makefile += makefile_item(debug_obj_name, dependencies, [fs_cmd('mkdir', dirname), f'{COMPILER} -g {defines_str} -c {file} -I. -o {debug_obj_name}'])

        objects.append(obj_name)
        debug_objects.append(debug_obj_name)
    
    
    libs_str = ' -l'.join(LIBS.get(system(), []))
    if libs_str: libs_str = ' -l' + libs_str

    # can't modify a constant or mypy will murder my family
    executable = EXECUTABLE
    if system() == 'Windows' and not executable.endswith('.exe'): executable = f'{executable}.exe'
    
    makefile = '.PHONY: makefile\n\n' \
    + makefile_item(
        'all',
        ['codegen'] + objects,
        [f'{COMPILER} {" ".join(objects)} -o {executable}{libs_str}']
    ) + makefile_item(
        'debug',
        ['codegen'] + debug_objects,
        [f'{COMPILER} -g -rdynamic {" ".join(debug_objects)} -o {executable}{libs_str}']
    ) + makefile_item(
        'run',
        ['all'],
        [f'./{executable}']
    ) + makefile_item(
        'run-debug',
        ['debug'],
        [f'./{executable}']
    ) + makefile_item(
        'makefile',
        [],
        [f'{PYTHON} build/generate-makefile.py']
    ) + makefile_item(
        'codegen',
        [],
        [
            f'{PYTHON} build/codegen.py {CODEGEN_OUTPUT}'
        ]
    ) + makefile_item(
        'clean',
        [],
        [
            fs_cmd('rm_dir', 'build/objects'),
            fs_cmd('rm_file', executable),
            fs_cmd('rm_file', 'generated.c'),
            fs_cmd('rm_file', 'generated.h')
        ]
    ) + makefile_item(
        'cloc',
        [],
        [
            f'{CLOC} . --exclude-list=cloc_exclude.txt'
        ]
    ) + makefile

    with open('Makefile', 'wt') as fh: fh.write(makefile)
    
if __name__ == '__main__': main()