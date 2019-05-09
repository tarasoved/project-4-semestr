#ifndef GRAV_CALC
#define GRAV_CALC

#include <iostream>
#include <fstream>
#include "tetgen.h"
#include <string>

REAL triple_product(REAL *a, REAL *b, REAL *c);
void grav_in_point(tetgenio *out, REAL *p, REAL *v);
void tetrahedralization(tetgenio *in, tetgenio *out, tetgenbehavior *behavior, std::ifstream *fin);

#endif // GRAV_CALC

