#include <stdio.h>
#include <stdint.h>
#include "../vendor/GraphBLAS/Include/GraphBLAS.h"
#include "../vendor/LAGraph/include/LAGraph.h"

char msg[LAGRAPH_MSG_LEN];

typedef enum
{
    VISA,
    MIR,
    MASTERCARD,
} System;

typedef enum
{
    MALE,
    FEMALE,
} Gender;

// typedef enum
// {
//     EDGE_OWNS,
//     EDGE_CALL,
//     EDGE_TX
// } EdgeType;

typedef struct
{
    Gender gender;
    uint8_t age;
} User;

typedef struct
{
    System system;
    double limit;
} Card;

typedef struct
{
    // EdgeType type;
    double weight;
    double aux;
} EdgeOwn;

typedef struct
{
    // EdgeType type;
    double weight;
    double aux;
} EdgeCall;

typedef struct
{
    // EdgeType type;
    double weight;
    double aux;
} EdgeTX;

void edge_mul(void *z, const void *x, const void *y)
{
}

void edge_add(void *z, const void *x, const void *y)
{
}

int main()
{
    // init graphblas
    GrB_Info info = GrB_init(GrB_NONBLOCKING);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "GraphBLAS init failed\n");
        return 1;
    }
    printf("GraphBLAS initialized.\n");
    LAGraph_Init(msg);
    printf("LAGraph initialized.\n");

    // read all input
    GrB_Matrix call_edges_mat, tx_edges_mat, owns_edges_mat;
    char *call_edges_file = "data/minimal_demo/graph/call.mtx";
    char *owns_edges_file = "data/minimal_demo/graph/owns.mtx";
    char *tx_edges_file = "data/minimal_demo/graph/transaction.mtx";
    FILE *fcall = fopen(call_edges_file, "r");
    FILE *fowns = fopen(owns_edges_file, "r");
    FILE *ftx = fopen(tx_edges_file, "r");
    LAGraph_MMRead(&call_edges_mat, fcall, msg);
    LAGraph_MMRead(&owns_edges_mat, fowns, msg);
    LAGraph_MMRead(&tx_edges_mat, ftx, msg);

    // init vetrices
    // 1 - 4 --- users
    User users[] = {
        
    };
    // 5 - 9 --- cards
    Card cards[] = {};

    // init edges
    // 4,6,7 --- call
    EdgeCall call_edges[] = {};
    // 2,3,9,11,12 --- owns
    EdgeOwn owns_edges[] = {};
    // 1,5,8,10 --- tx
    EdgeTX tx_edges[] = {};

    // apply filters

    // vertex filter: we will take only prersons over 30 and exclude cards with `mastercard` payment system

    // build matrix M

    // build matrix M'

    // run pagerank
}