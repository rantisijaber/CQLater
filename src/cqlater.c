#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "cqlater.h"
#include "quantum_gate.h"

struct cql_qcircuit {
    struct {
        complex_num* values;
        size_t size;
    } state_vector;
    cql_gate_array gate_array;
    size_t qubit_count;
    size_t gate_pos;
    uint8_t backend_type;
};


void cql_qcircuit_init(cql_qcircuit** circuit, size_t qubit_count, uint8_t backend) {
    *circuit = (cql_qcircuit*) malloc(sizeof(cql_qcircuit));
    if (backend == BACKEND_GK_THEOREM) {} else {
        (*circuit)->state_vector.values = (complex_num*) malloc(sizeof(complex_num) * (1 << qubit_count));
        (*circuit)->state_vector.size = 1 << qubit_count;
        (*circuit)->state_vector.values[0].real = 1.0;
    }
    
    (*circuit)->backend_type = backend;
    (*circuit)->qubit_count = qubit_count;
    (*circuit)->gate_pos = 0;
    gate_array_init(&((*circuit)->gate_array), 10);
}

void cql_circuit_destroy(cql_qcircuit* circuit) {
    if (circuit->backend_type == BACKEND_STATE_VECTOR) {
        free(&(circuit->state_vector.values));
        circuit->state_vector.values = NULL;
    }
}

void cql_hadamard(cql_qcircuit* circuit, uint8_t qubit_idx) {
    complex_num altered_states[circuit->state_vector.size];
    for (size_t i = 0; i < circuit->state_vector.size; i++) {
        uint32_t pair_idx = i ^ (1 << qubit_idx);
        if ((i & (1 << qubit_idx)) == 0) {
            altered_states[i] = complex_add(complex_multiply(H[0][0], circuit->state_vector.values[i]), 
                    complex_multiply(H[0][1], circuit->state_vector.values[pair_idx]));
            altered_states[pair_idx] = complex_add(complex_multiply(H[1][0], circuit->state_vector.values[i]),
                    complex_multiply(H[1][1], circuit->state_vector.values[pair_idx]));
    
        }
    }

    for (uint32_t i = 0; i < circuit->state_vector.size; i++) {
        circuit->state_vector.values[i] = altered_states[i];
    }
    
    gate_array_append(&circuit->gate_array, (cql_gate) {
            .gate_type = Hadamard, 
            .circuit_pos = circuit->gate_pos++, 
            .target_qubit = qubit_idx, 
            .control_qubit = -1
        });
}

void cql_pauliX(cql_qcircuit* circuit, uint8_t qubit_idx) {
    for (size_t i = 0; i < (1 << circuit->qubit_count) / 2; i++) {
        uint32_t pair_idx = i ^ (1 << qubit_idx);
        complex_num temp = circuit->state_vector.values[i];
        if ((i & (1 << qubit_idx)) == 0) {
            circuit->state_vector.values[i] = circuit->state_vector.values[pair_idx];
            circuit->state_vector.values[pair_idx] = temp;
        }
    }

    gate_array_append(&circuit->gate_array, (cql_gate) {
            .gate_type = PauliX, 
            .circuit_pos = circuit->gate_pos++, 
            .target_qubit = qubit_idx, 
            .control_qubit = -1
        });
}

void cql_pauliY(cql_qcircuit* circuit, uint8_t qubit_idx) {
    for (size_t i = 0; i < circuit->state_vector.size; i++) {
        uint32_t pair_idx = i ^ (1 << qubit_idx);
        if ((i & (1 << qubit_idx)) == 0) {
            circuit->state_vector.values[i] = complex_multiply(circuit->state_vector.values[pair_idx], (complex_num) {0, -1});
            circuit->state_vector.values[pair_idx] = complex_multiply(circuit->state_vector.values[i], (complex_num) {0, 1});
        }
    }

    gate_array_append(&circuit->gate_array, (cql_gate) {
            .gate_type = PauliY,
            .circuit_pos = circuit->gate_pos++,
            .target_qubit = qubit_idx,
            .control_qubit = -1
        });
}

void cql_pauliZ(cql_qcircuit* circuit, uint8_t qubit_idx) {
    for (size_t i = 0; i < circuit->state_vector.size; i++) {
        if ((i & (1 << qubit_idx)) == 1) {
            circuit->state_vector.values[i] = complex_multiply(circuit->state_vector.values[i], (complex_num) {-1, 0});
        }
    }

    gate_array_append(&circuit->gate_array, (cql_gate) {
            .gate_type = PauliZ,
            .circuit_pos = circuit->gate_pos++,
            .target_qubit = qubit_idx,
            .control_qubit = -1
        });
}

void cql_printsv(const cql_qcircuit* circuit) {
    for (size_t i = 0; i < circuit->state_vector.size; i++) {
        printf("%f + %fi\n", circuit->state_vector.values[i].real, 
                circuit->state_vector.values[i].imag);
    }
}
