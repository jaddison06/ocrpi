# https://gist.github.com/jaddison06/eaf1a5760e484d4de9ce7256f3d95ee4

import os
import os.path as path
from sys import argv, executable
from shutil import rmtree
from platform import system
from typing import Callable

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
TEST_DEFINES: dict[str, str] = {**DEBUG_DEFINES, 'OCRPI_TEST': '1'}
LIBS: dict[str, list[str]] = {'Linux': ['m']}
EXECUTABLE = 'ocrpi'
SOURCE_EXTS = ['.c']
HEADER_EXTS = ['.h']
PYTHON = executable
CLOC = 'C:/Users/jjadd/Downloads/cloc-1.92.exe' if system() == 'Windows' else 'cloc'
CODEGEN_CONFIG = 'generate.yaml'
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

def defines_str(definesList: dict[str, str]) -> str:
    out = ''
    for k, v in definesList.items():
        out += f'-D {k}={v} '
    out = out.strip()
    return out

def main():
    if len(argv) > 1:
        fs_util()
        exit(0)
    
    source_files = all_with_extension(*SOURCE_EXTS)
    headers = {path.splitext(header)[0]: header for header in all_with_extension(*HEADER_EXTS)}

    makefile = ''

    objects: list[str] = []
    debug_objects: list[str] = []
    test_objects: list[str] = []

    debug_defines = defines_str(DEBUG_DEFINES)
    test_defines  = defines_str(TEST_DEFINES)

    if f'{CODEGEN_OUTPUT}.c' not in source_files:
        source_files.append(f'{CODEGEN_OUTPUT}.c')
        headers[CODEGEN_OUTPUT] = f'{CODEGEN_OUTPUT}.h'

    for file in source_files:
        dirname = 'build/objects/' + path.dirname(file)
        base = path.splitext(file)[0]
        obj_name       = f'build/objects/{base}.o'
        debug_obj_name = f'build/objects/{base}-debug.o'
        test_obj_name  = f'build/objects/{base}-test.o'
        dependencies = [file]
        if base in headers: dependencies.append(headers[base])
        dependencies += COMMON_DEPENDENCIES

        makefile += makefile_item(obj_name,       dependencies, [fs_cmd('mkdir', dirname), f'{COMPILER} -c {file} -I. -o {obj_name}'])
        makefile += makefile_item(debug_obj_name, dependencies, [fs_cmd('mkdir', dirname), f'{COMPILER} -g {debug_defines} -c {file} -I. -o {debug_obj_name}'])
        makefile += makefile_item(test_obj_name,  dependencies, [fs_cmd('mkdir', dirname), f'{COMPILER} -g {test_defines} -c {file} -I. -o {test_obj_name}'])

        objects.append(obj_name)
        debug_objects.append(debug_obj_name)
        test_objects.append(test_obj_name)
    
    
    libs_str = ' -l'.join(LIBS.get(system(), []))
    if libs_str: libs_str = ' -l' + libs_str

    # can't modify a constant or mypy will murder my family
    executable = EXECUTABLE
    if system() == 'Windows' and not executable.endswith('.exe'): executable = f'{executable}.exe'

    run_item: Callable[[str, str], str] = lambda name, dep: makefile_item(name, [dep], [f'./{executable} $(source)'])
    codegen_output_item: Callable[[str], str] = lambda ext: makefile_item(f'{CODEGEN_OUTPUT}{ext}', [CODEGEN_CONFIG], [f'{PYTHON} build/codegen.py {CODEGEN_CONFIG} {CODEGEN_OUTPUT}'])
    
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
        'test',
        ['codegen'] + test_objects,
        [f'{COMPILER} -g -rdynamic {" ".join(test_objects)} -o {executable}{libs_str}']
    ) + run_item(
        'run', 'all'
    ) + run_item(
        'run-debug', 'debug'
    ) + run_item(
        'run-test', 'test'
    ) + makefile_item(
        'makefile',
        [],
        [f'{PYTHON} build/generate-makefile.py']
    ) + makefile_item(
        'codegen',
        [f'{CODEGEN_OUTPUT}.c', f'{CODEGEN_OUTPUT}.h'],
        []
    ) + codegen_output_item(
        '.c'
    ) + codegen_output_item(
        '.h'
    )+ makefile_item(
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
