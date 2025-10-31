#include <stdio.h>
#include <stdint.h>
#include "../vendor/GraphBLAS/Include/GraphBLAS.h"
#include "../vendor/LAGraph/include/LAGraph.h"
typedef enum {
    VISA,
    MIR,
    MASTERCARD,
} System;

typedef enum {
    MALE,
    FEMALE,
} Gender;

typedef enum {
    EDGE_OWNS,
    EDGE_CALL,
    EDGE_TX
} EdgeType;

typedef struct {
    Gender gender;
    uint8_t age;
} User;

typedef struct {
    System system;
    double limit;
} Card;

typedef struct {
    EdgeType type;
    double weight;
    double aux;
} EdgeInfo;

void edge_mul(void *z, const void *x, const void *y) {

}

void edge_add(void *z, const void *x, const void *y) {

}

int main()
{
    // init graphblas
    GrB_Info info = GrB_init(GrB_NONBLOCKING);
    if (info != GrB_SUCCESS) {
        fprintf(stderr, "GraphBLAS init failed\n");
        return 1;
    }
    printf("GraphBLAS initialized.\n");

    // custom type
    GrB_Type EdgeInfo_Type;
    GrB_Type_new(&EdgeInfo_Type, sizeof(EdgeInfo));


}