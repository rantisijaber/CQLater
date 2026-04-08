#ifndef CQLATER_H
#define CQLATER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "complex.h"

#ifdef __cplusplus
extern "C" {
#endif


#define BACKEND_STATE_VECTOR    0
#define BACKEND_GK_THEOREM      1

static const complex_num H[2][2] = {
    {{0.7071067811865476, 0}, {0.7071067811865476, 0}},
    {{0.7071067811865476, 0}, {-0.7071067811865476, 0}}
};



typedef struct cql_qcircuit cql_qcircuit;

void cql_qcircuit_init(cql_qcircuit** circuit, size_t qubit_count, uint8_t backend);
void cql_hadamard(cql_qcircuit* circuit, uint8_t qubit_idx);
void cql_pauliX(cql_qcircuit* circuit, uint8_t qubit_idx);
void cql_pauliY(cql_qcircuit* circuit, uint8_t qubit_idx);
void cql_circuit_destroy(cql_qcircuit* circuit);
void cql_printsv(const cql_qcircuit* circuit);
bool cql_clifvalid(const cql_qcircuit* circuit);


#ifdef __cplusplus
}
#endif



#endif
