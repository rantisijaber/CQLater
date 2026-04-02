
#include <stdlib.h>
#include <stdint.h>
#include "quantum_circuit.h"
#include "complex.h"
#include "quantum_gate.h"


void cql_circuit_init(QuantumCircuit* circuit, size_t qubit_count) {
    circuit->state_vector = malloc(sizeof(ComplexNum) * (1 << qubit_count));
    circuit->state_vector[0].real = 1;
    circuit->qubit_count = qubit_count;
    circuit->state_vector_size = 1 << circuit->qubit_count;
    circuit->gate_pos = 0;
    gate_array_init(&circuit->gate_array, 10);
}


void cql_hadamard(QuantumCircuit* circuit, uint8_t qubit_idx) {
    ComplexNum altered_states[circuit->state_vector_size];
    for (size_t i = 0; i < circuit->state_vector_size; i++) {
        uint32_t pair_idx = i ^ (1 << qubit_idx);
        if ((i & (1 << qubit_idx)) == 0) {
            altered_states[i] = complex_add(complex_multiply(H[0][0], circuit->state_vector[i]), 
                    complex_multiply(H[0][1], circuit->state_vector[pair_idx]));
            altered_states[pair_idx] = complex_add(complex_multiply(H[1][0], circuit->state_vector[i]),
                    complex_multiply(H[1][1], circuit->state_vector[pair_idx]));
    
        }
    }

    for (uint32_t i = 0; i < circuit->state_vector_size; i++) {
        circuit->state_vector[i] = altered_states[i];
    }
    
    gate_array_append(&circuit->gate_array, (Gate) {
            .gate_type = Hadamard, 
            .circuit_pos = circuit->gate_pos++, 
            .target_qubit = qubit_idx, 
            .control_qubit = -1
        });
}


void cql_pauliX(QuantumCircuit* circuit, uint8_t qubit_idx) {
    for (size_t i = 0; i < (1 << circuit->qubit_count) / 2; i++) {
        uint32_t pair_idx = i ^ (1 << qubit_idx);
        ComplexNum temp = circuit->state_vector[i];
        if ((i & (1 << qubit_idx)) == 0) {
            circuit->state_vector[i] = circuit->state_vector[pair_idx];
            circuit->state_vector[pair_idx] = temp;
        }
    }

    gate_array_append(&circuit->gate_array, (Gate) {
            .gate_type = PauliX, 
            .circuit_pos = circuit->gate_pos++, 
            .target_qubit = qubit_idx, 
            .control_qubit = -1
        });
}

void cql_pauliY(QuantumCircuit* circuit, uint8_t qubit_idx) {
    for (size_t i = 0; i < circuit->state_vector_size; i++) {
        uint32_t pair_idx = i ^ (1 << qubit_idx);
        if ((i & (1 << qubit_idx)) == 0) {
            circuit->state_vector[i] = complex_multiply(circuit->state_vector[pair_idx], (ComplexNum) {0, -1});
            circuit->state_vector[pair_idx] = complex_multiply(circuit->state_vector[i], (ComplexNum) {0, 1});
        }
    }

    gate_array_append(&circuit->gate_array, (Gate) {
            .gate_type = PauliY,
            .circuit_pos = circuit->gate_pos++,
            .target_qubit = qubit_idx,
            .control_qubit = -1
        });
}

void cql_pauliZ(QuantumCircuit* circuit, uint8_t qubit_idx) {
    for (size_t i = 0; i < circuit->state_vector_size; i++) {
        if ((i & (1 << qubit_idx)) == 1) {
            circuit->state_vector[i] = complex_multiply(circuit->state_vector[i], (ComplexNum) {-1, 0});
        }
    }

    gate_array_append(&circuit->gate_array, (Gate) {
            .gate_type = PauliZ,
            .circuit_pos = circuit->gate_pos++,
            .target_qubit = qubit_idx,
            .control_qubit = -1
        });
}
