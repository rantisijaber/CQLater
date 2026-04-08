#ifndef QUANTUM_GATE_H
#define QUANTUM_GATE_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    PauliX,
    PauliY,
    PauliZ,
    Hadamard
} cql_gate_type;

typedef struct {
    cql_gate_type gate_type;
    size_t circuit_pos;
    uint8_t target_qubit;
    uint8_t control_qubit;
} cql_gate;

typedef struct {
    cql_gate* gates;
    size_t size;
    size_t capacity;
} cql_gate_array;

void gate_array_init(cql_gate_array* gate_array, size_t capacity);
void gate_array_destroy(cql_gate_array* gate_array);
void gate_array_append(cql_gate_array* gate_array, cql_gate gate);








#endif
