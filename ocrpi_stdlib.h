#pragma once

#include "interpreter.h"

void stl_print(ObjList args);
InterpreterObj stl_typeof(ObjList args);

InterpreterObj stl_bool(ObjList args);
InterpreterObj stl_string(ObjList args);
InterpreterObj stl_float(ObjList args);
InterpreterObj stl_int(ObjList args);