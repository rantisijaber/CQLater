#include "quantum_gate.h"
#include <stdlib.h>

void gate_array_init(cql_gate_array* gate_array, size_t capacity) {
    gate_array->gates = (cql_gate*) malloc(sizeof(cql_gate) * capacity);
    if (gate_array->gates == NULL) return;
    gate_array->size = 0;
    gate_array->capacity = capacity;
}

void gate_array_destroy(cql_gate_array* gate_array) {
    free(gate_array->gates);
    gate_array->gates = NULL;
}

void gate_array_append(cql_gate_array* gate_array, cql_gate gate) {
    if (gate_array->size == gate_array->capacity) {
        gate_array->capacity *= 2;
        void* temp = realloc(gate_array->gates, sizeof(cql_gate) * gate_array->capacity);
        if (temp == NULL) return;
    }
    
    gate_array->gates[gate_array->size++] = gate;

}
