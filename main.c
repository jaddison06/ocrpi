#ifdef OCRPI_TEST

#include "testing.h"

int main() {
    testAll();
}

#else

#include "readFile.h"
#include "panic.h"
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

static bool checkExtension(char* fname, char* ext) {
    return strncmp(ext, fname + strlen(fname) - strlen(ext), strlen(ext)) == 0;
}

int main(int argc, char** argv) {
    if (argc != 2) panic(Panic_Main, "Usage: ocrpi <source-file>");
    
    if (checkExtension(argv[1], ".ocr")) {
        ParseOutput po = parse(lex(readFile(argv[1])));
        if (po.errors.len > 0) exit(1);
        interpret(po);
    } else if (checkExtension(argv[1], ".ocrx")) {
        // lex, parse, check, compile
        panic(Panic_Main, "Extended mode not supported yet!");
    } else {
        panic(Panic_Main, "Unknown file extension! (%s)", argv[1]);
    }
}

#endif