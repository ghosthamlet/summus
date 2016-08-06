#ifndef SMM_AST_MATCHER_H
#define SMM_AST_MATCHER_H

#include "../compiler/smmcommon.h"
#include "../compiler/smmutil.h"
#include "../compiler/smmparser.h"
#include "CuTest.h"
#include <stdio.h>

void smmAssertASTEquals(CuTest* tc, PSmmAstNode ex, PSmmAstNode got);

#endif
