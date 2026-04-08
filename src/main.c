#include "cqlater.h"
#include <stdint.h>
#include <stdio.h>

int main(void) {
    cql_qcircuit* circuit;
    cql_qcircuit_init(&circuit, 3, BACKEND_STATE_VECTOR);
    
    cql_hadamard(circuit, 2);
    cql_printsv(circuit);

    return 0;
}
