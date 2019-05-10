#include <iostream>
#include <fstream>
#include "tetgen.h"
#include <string>

REAL triple_product(REAL *a, REAL *b, REAL *c) {
    return a[0] * b[1] * c[2] + a[1] * b[2] * c[0] + a[2] * b[0] * c[1] -
           a[2] * b[1] * c[0] + a[1] * b[0] * c[2] + a[0] * b[2] * c[1];
}

void grav_in_point(tetgenio *out, REAL *p, REAL *v) {

    int i, m;
    REAL v1, v2, v3;
    REAL a[3], b[3], c[3];
    REAL K;

    v[0] = 0;
    v[1] = 0;
    v[2] = 0;

    for(i = 0; i < out->numberoftetrahedra; i++) {
        m = out->tetrahedronlist[i] * 4;
        v1 = (out->pointlist[m * 3] +
              out->pointlist[(m + 1) * 3] +
              out->pointlist[(m + 2) * 3] +
              out->pointlist[(m + 3) * 3]) / 4;
        v2 = (out->pointlist[m * 3 + 1] +
              out->pointlist[(m + 1) * 3 + 1] +
              out->pointlist[(m + 2) * 3 + 1] +
              out->pointlist[(m + 3) * 3 + 1]) / 4;
        v3 = (out->pointlist[m * 3 + 2] +
              out->pointlist[(m + 1) * 3 + 2] +
              out->pointlist[(m + 2) * 3 + 2] +
              out->pointlist[(m + 3) * 3 + 2]) / 4;
        v1 -= p[0];
        v2 -= p[1];
        v3 -= p[2];
        a[0] = out->pointlist[m * 3] - out->pointlist[(m + 1) * 3];
        a[1] = out->pointlist[m * 3 + 1] - out->pointlist[(m + 1) * 3 + 1];
        a[2] = out->pointlist[m * 3 + 2] - out->pointlist[(m + 1) * 3 + 2];
        b[0] = out->pointlist[m * 3] - out->pointlist[(m + 2) * 3];
        b[1] = out->pointlist[m * 3 + 1] - out->pointlist[(m + 2) * 3 + 1];
        b[2] = out->pointlist[m * 3 + 2] - out->pointlist[(m + 2) * 3 + 2];
        c[0] = out->pointlist[m * 3] - out->pointlist[(m + 3) * 3];
        c[1] = out->pointlist[m * 3 + 1] - out->pointlist[(m + 3) * 3 + 1];
        c[2] = out->pointlist[m * 3 + 2] - out->pointlist[(m + 3) * 3 + 2];
        K = abs(triple_product(a, b, c)) / pow(v1 * v1 + v2 * v2 + v3 * v3, 1.5);
        v[0] += K * v1;
        v[1] += K * v2;
        v[2] += K * v3;
    }
}

void tetrahedralization(tetgenio *in, tetgenio *out, tetgenbehavior *behavior, std::ifstream *fin) {
    int i;
    *fin >> in->numberofpoints;
    *fin >> in->numberoftrifaces;
    REAL points[in->numberofpoints * 3];
    for(i = 0; i < (in->numberofpoints * 3); i++)
        *fin >> points[i];
    int faces[in->numberoftrifaces * 3];
    for(i = 0; i < (in->numberoftrifaces * 3); i++)
        *fin >> faces[i];
    in->pointlist = points;
    in->trifacelist = faces;
    tetrahedralize(behavior, in, out);
}

