
#include "quantum_circuit.h"
#include <stdint.h>
#include <stdio.h>

int main(void) {
    QuantumCircuit circuit = {0};
    cql_circuit_init(&circuit, 3);
    for (uint8_t i = 0; i < (1 << circuit.qubit_count); i++) {
        printf("|%f + %fi|\n", circuit.state_vector[i].real, circuit.state_vector[i].imag);
    }
    printf("---------------------------------\n");
    cql_pauliX(&circuit, 0);
    for (uint8_t i = 0; i < (1 << circuit.qubit_count); i++) {
        printf("|%f + %fi|\n", circuit.state_vector[i].real, circuit.state_vector[i].imag);
    }
    

    printf("---------------------------------\n");

    cql_hadamard(&circuit, 2);
    for (uint8_t i = 0; i < (1 << circuit.qubit_count); i++) {
        printf("|%f + %fi|\n", circuit.state_vector[i].real, circuit.state_vector[i].imag);
    }
    

    cql_hadamard(&circuit, 0);
    printf("---------------------------------\n");

    for (uint8_t i = 0; i < (1 << circuit.qubit_count); i++) {
        printf("|%f + %fi|\n", circuit.state_vector[i].real, circuit.state_vector[i].imag);
    }

    printf("---------------------------------\n");

    
}
