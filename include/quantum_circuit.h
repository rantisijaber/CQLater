#ifndef QUANTUM_CIRCUIT_H
#define QUANTUM_CIRCUIT_H

#include <stddef.h>
#include <stdint.h>
#include "quantum_gate.h"
#include "complex.h"

#define QUBIT_COUNT_MAX         12

typedef struct {
    ComplexNum* state_vector;
    GateArray gate_array;
    size_t qubit_count;
    size_t state_vector_size;
    size_t gate_pos;
} QuantumCircuit;

static const ComplexNum H[2][2] = {
    {{0.7071067811865476, 0}, {0.7071067811865476, 0}},
    {{0.7071067811865476, 0}, {-0.7071067811865476, 0}}
};

void cql_circuit_init(QuantumCircuit* circuit, size_t qubit_count);
void cql_hadamard(QuantumCircuit* circuit, uint8_t qubit_idx);
void cql_pauliX(QuantumCircuit* circuit, uint8_t qubit_idx);






#endif
