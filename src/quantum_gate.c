#include "quantum_gate.h"
#include <stdlib.h>

void gate_array_init(GateArray* gate_array, size_t capacity) {
    gate_array->gates = malloc(sizeof(Gate) * capacity);
    if (gate_array->gates == NULL) return;
    gate_array->size = 0;
    gate_array->capacity = capacity;
}

void gate_array_append(GateArray* gate_array, Gate gate) {
    if (gate_array->size == gate_array->capacity) { 
        void* temp = realloc(gate_array->gates, gate_array->capacity * 2);
        if (temp == NULL) return;
    }
    
    gate_array->gates[gate_array->size++] = gate;

}
