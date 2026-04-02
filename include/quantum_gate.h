#ifndef QUANTUM_GATE_H
#define QUANTUM_GATE_H

#include <stddef.h>
#include <stdint.h>
typedef enum {
    PauliX,
    PauliY,
    PauliZ,
    Hadamard
} GateType;

typedef struct {
    GateType gate_type;
    size_t circuit_pos;
    uint8_t target_qubit;
    uint8_t control_qubit;
} Gate;

typedef struct {
    Gate* gates;
    size_t size;
    size_t capacity;
} GateArray;

void gate_array_init(GateArray* gate_array, size_t capacity);
void gate_array_destroy(GateArray* gate_array);
void gate_array_append(GateArray* gate_array, Gate gate);








#endif
