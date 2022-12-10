#ifdef OCRPI_DEBUG

#include "testing.h"

int main() {
    testAll();
}

#else

#include "readFile.h"
#include "lexer.h"
#include "parser.h"

static void panic(char* msg) {
    printf("\033[0;31m%s\033[0m\n", msg);
    exit(-1);
}

static bool checkExtension(char* fname, char* ext) {
    return strncmp(ext, fname + strlen(fname) - strlen(ext), strlen(ext)) == 0;
}

int main(int argc, char** argv) {
    if (argc != 2) panic("Usage: ocrpi <source-file>");
    
    if (checkExtension(argv[1], ".ocr")) {
        ParseOutput po = parse(lex(readFile(argv[1])));
        if (po.errors.len > 0) exit(1);
        interpret(po);
    } else if (checkExtension(argv[1], ".ocrx")) {
        // lex, parse, check, compile
        panic("Extended mode not supported yet!");
    } else {
        panic("Unknown file extension!");
    }
}

#endif