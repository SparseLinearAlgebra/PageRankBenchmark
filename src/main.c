#include <stdio.h>
#include <stdint.h>
#include "../vendor/GraphBLAS/Include/GraphBLAS.h"
#include "../vendor/LAGraph/include/LAGraph.h"
#include "../vendor/LAGraph/include/LAGraphX.h"

#define VERTICES_NUMBER 12
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

// vertices

typedef struct User
{
    Gender gender;
    uint8_t age;
} User;

typedef struct Card
{
    System system;
    double limit;
} Card;

// edges

typedef struct EdgeOwns
{
    int days;
} EdgeOwns;

typedef struct EdgeTX
{
    double sum;
    uint32_t count;
} EdgeTX;

void check_user_age(bool *z, const User *x, GrB_Index _i, GrB_Index _j, const uint8_t *y) // EdgeOwns
{
    {
        *z = (x->age > *y);
    }
}

void owns_bool_mult(bool *z, const bool *x, const EdgeOwns *y)
{
    *z = *x;
}

void owns_bool_add(bool *z, const bool *x, const bool *y)
{
    *z = (*x || *y);
}

void tx_bool_mult(EdgeTX *z, const bool *x, const EdgeTX *y)
{
    if (*x)
        *z = *y;
    else
        z->sum = 0, z->count = 0;
}

void tx_bool_mult_right(EdgeTX *z, const EdgeTX *x, const bool *y)
{
    if (*y)
        *z = *x;
    else
        z->sum = 0, z->count = 0;
}

void tx_bool_add(EdgeTX *z, const EdgeTX *x, const EdgeTX *y)
{
    if (x->count > 0 || y->count > 0)
        *z = (x->count > 0) ? *x : *y;
    else
        z->sum = 0, z->count = 0;
}

void tx_is_nonempty(bool *z, const EdgeTX *x)
{
    *z = (x->count != 0);
}

void exp_binop(double *z, const double *x)
{
    *z = exp(*x);
}

void F_op(double *z, const EdgeTX *x)
{
    *z = log(x->sum);
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
    printf("LAGraph initialized.\n\n");

    // ------------------------------------------------------------------------
    // init edge matrices
    // ------------------------------------------------------------------------

    // custom types for edges
    GrB_Type tx_edge, owns_edge;
    info = GrB_Type_new(&tx_edge, sizeof(EdgeTX));
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"tx_edge\" type\n");
        return 1;
    }
    info = GrB_Type_new(&owns_edge, sizeof(EdgeOwns));
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"tx_edge\" type\n");
        return 1;
    }

    // edge decomposition

    GrB_Matrix tx_edge_mat, owns_edge_mat;
    info = GrB_Matrix_new(&tx_edge_mat, tx_edge, VERTICES_NUMBER, VERTICES_NUMBER);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"tx\" matrix\n");
        return 1;
    }
    info = GrB_Matrix_new(&owns_edge_mat, owns_edge, VERTICES_NUMBER, VERTICES_NUMBER);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"owns\" matrix\n");
        return 1;
    }

    // fill tx_mat
    EdgeTX edge56 = {2223412.0, 56};
    EdgeTX edge59 = {6223412.0, 59};
    EdgeTX edge67 = {8913212.0, 67};
    EdgeTX edge69 = {92223412.0, 69};
    EdgeTX edge65 = {133214.1, 65};
    EdgeTX edge95 = {1267325.99, 95};
    EdgeTX edge611 = {1999999.1, 611};
    EdgeTX edge116 = {6999999.1, 116};
    EdgeTX edge511 = {9999999.1, 511};
    EdgeTX edge115 = {8999999.1, 115};
    EdgeTX edge127 = {8999999.1, 127};
    EdgeTX edge712 = {8999999.1, 712};
    EdgeTX edge912 = {899999999.1, 912};
    EdgeTX edge129 = {99999999.1, 129};

    info = GrB_Matrix_setElement_UDT(tx_edge_mat, &edge56, 4, 5);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge56\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(tx_edge_mat, &edge59, 4, 8);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge59\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(tx_edge_mat, &edge67, 5, 6);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge67\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(tx_edge_mat, &edge69, 5, 8);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge69\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(tx_edge_mat, &edge65, 5, 4);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge69\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(tx_edge_mat, &edge95, 8, 4);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge69\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(tx_edge_mat, &edge611, 5, 10);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge69\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(tx_edge_mat, &edge116, 10, 5);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge69\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(tx_edge_mat, &edge511, 4, 10);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge69\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(tx_edge_mat, &edge115, 10, 4);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge69\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(tx_edge_mat, &edge127, 11, 6);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge69\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(tx_edge_mat, &edge712, 6, 11);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge69\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(tx_edge_mat, &edge912, 8, 11);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge69\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(tx_edge_mat, &edge129, 11, 8);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge69\" in matrix\n");
        return 1;
    }
    // fill owns_mat
    EdgeOwns edge45 = {45};
    EdgeOwns edge36 = {36};
    EdgeOwns edge19 = {19};
    EdgeOwns edge27 = {27};
    EdgeOwns edge28 = {28};
    EdgeOwns edge1011 = {21};
    EdgeOwns edge1012 = {22};
    info = GrB_Matrix_setElement_UDT(owns_edge_mat, &edge45, 3, 4);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge45\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(owns_edge_mat, &edge36, 2, 5);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge36\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(owns_edge_mat, &edge19, 0, 8);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge19\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(owns_edge_mat, &edge27, 1, 6);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge27\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(owns_edge_mat, &edge28, 1, 7);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge28\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(owns_edge_mat, &edge1011, 9, 10);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge1011\" in matrix\n");
        return 1;
    }
    info = GrB_Matrix_setElement_UDT(owns_edge_mat, &edge1012, 9, 11);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge1011\" in matrix\n");
        return 1;
    }

    // ------------------------------------------------------------------------
    // init vertices vectors
    // ------------------------------------------------------------------------

    GrB_Type user, card;
    info = GrB_Type_new(&user, sizeof(User));

    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"user\" type\n");
        return 1;
    }
    info = GrB_Type_new(&card, sizeof(Card));
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"card\" type\n");
        return 1;
    }

    // 1 - 4 & 10 --- users
    GrB_Vector users;
    info = GrB_Vector_new(&users, user, VERTICES_NUMBER);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"users\" vector\n");
        return 1;
    }
    User user1 = {MALE, 52};
    User user2 = {MALE, 25};
    User user3 = {FEMALE, 40};
    User user4 = {MALE, 42};
    User user10 = {MALE, 35};
    info = GrB_Vector_setElement_UDT(users, &user1, 0);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"user1\" in vector\n");
        return 1;
    }
    info = GrB_Vector_setElement_UDT(users, &user2, 1);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"edge2\" in vector\n");
        return 1;
    }
    info = GrB_Vector_setElement_UDT(users, &user3, 2);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"user3\" in vector\n");
        return 1;
    }
    info = GrB_Vector_setElement_UDT(users, &user4, 3);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"user4\" in vector\n");
        return 1;
    }
    info = GrB_Vector_setElement_UDT(users, &user10, 9);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"user4\" in vector\n");
        return 1;
    }

    // 5 - 9 & 11 - 12 --- cards
    GrB_Vector cards;
    info = GrB_Vector_new(&cards, card, VERTICES_NUMBER);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"cards\" vector\n");
        return 1;
    }
    Card card5 = {MIR, 600000.0};
    Card card6 = {MIR, 700000.0};
    Card card7 = {VISA, 800000.0};
    Card card8 = {MASTERCARD, 900000.0};
    Card card9 = {MASTERCARD, 10000000.0};
    Card card11 = {MASTERCARD, 99000000.0};
    Card card12 = {MASTERCARD, 99000000.0};
    info = GrB_Vector_setElement_UDT(cards, &card5, 4);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"card5\" in vector\n");
        return 1;
    }
    info = GrB_Vector_setElement_UDT(cards, &card6, 5);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"card6\" in vector\n");
        return 1;
    }
    info = GrB_Vector_setElement_UDT(cards, &card7, 6);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"card7\" in vector\n");
        return 1;
    }
    info = GrB_Vector_setElement_UDT(cards, &card8, 7);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"card8\" in vector\n");
        return 1;
    }
    info = GrB_Vector_setElement_UDT(cards, &card9, 8);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"card9\" in vector\n");
        return 1;
    }
    info = GrB_Vector_setElement_UDT(cards, &card11, 10);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"card9\" in vector\n");
        return 1;
    }
    info = GrB_Vector_setElement_UDT(cards, &card12, 11);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to insert \"card9\" in vector\n");
        return 1;
    }

    // ------------------------------------------------------------------------
    // build user filters
    // ------------------------------------------------------------------------

    // vertex filter: we will take only prersons over 30 and exclude cards with `mastercard` payment system
    GrB_Matrix ID;
    GrB_Vector v;
    info = GrB_Vector_new(&v, GrB_BOOL, VERTICES_NUMBER);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"ID\" vector\n");
        return 1;
    }
    info = GrB_Vector_assign_BOOL(v, NULL, NULL, false, GrB_ALL, VERTICES_NUMBER, NULL);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to assign values to \"v\" vector\n");
        return 1;
    }

    // create selector
    GrB_IndexUnaryOp user_age;
    info = GrB_IndexUnaryOp_new(&user_age, (GxB_index_unary_function)&check_user_age, GrB_BOOL, user, GrB_UINT8); // TODO
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"user_age\" unop\n");
        return 1;
    }
    uint8_t age = 30;
    info = GrB_Vector_apply_IndexOp_UDT(v, NULL, NULL, user_age, users, &age, NULL);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to select elements from users vector: %d\n", info);
        return 1;
    }
    GxB_print(v, GxB_COMPLETE);
    info = GrB_Matrix_diag(&ID, v, 0);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create filter matrix %d\n", info);
        return 1;
    }
    // GrB_Matrix v_mat, id_mat;
    // GrB_Matrix_new(&v_mat, GrB_BOOL, VERTICES_NUMBER, 1);
    // GrB_Col_assign(v_mat, NULL, NULL, v, GrB_ALL, VERTICES_NUMBER, 0, NULL);

    // GrB_Vector id;
    // info = GrB_Vector_new(&id, GrB_BOOL, VERTICES_NUMBER);
    // info = GrB_Vector_assign_BOOL(id, NULL, NULL, true, GrB_ALL, VERTICES_NUMBER, NULL);
    // GrB_Matrix_new(&id_mat, GrB_BOOL, 1, VERTICES_NUMBER);
    // GrB_Row_assign(id_mat, NULL, NULL, id, 0, GrB_ALL, VERTICES_NUMBER, NULL);

    // GrB_Matrix kron;
    // GrB_Matrix_new(&kron, GrB_BOOL, VERTICES_NUMBER, VERTICES_NUMBER);
    // // GxB_print(v_mat, GxB_COMPLETE);
    // // GxB_print(id_mat, GxB_COMPLETE);
    // info = GrB_kronecker(kron, NULL, NULL, GrB_LAND, v_mat, id_mat, NULL);

    // DEBUG
    printf("filter matrix content: \n");
    for (GrB_Index i = 0; i < VERTICES_NUMBER; i++)
        for (GrB_Index j = 0; j < VERTICES_NUMBER; j++)
        {
            bool val;
            GrB_Info info = GrB_Matrix_extractElement_BOOL(&val, ID, i, j);
            if (info == GrB_SUCCESS)
            {
                printf("[%lu,%lu] = %d\n", i, j, val);
            }
            // else if (info == GrB_NO_VALUE)
            // {
            //     printf("[%lu,%lu] no value\n", i, j);
            // }
            // else
            // {
            //     printf("[%lu,%lu] error code: %d\n", i, j, info);
            // }
        }
    // for (GrB_Index i = 0; i < VERTICES_NUMBER; i++)
    // {
    //     bool val;
    //     GrB_Info info = GrB_Matrix_extractElement_BOOL(&val, kron, i, i);
    //     if (info == GrB_SUCCESS)
    //     {
    //         printf("[%lu,%lu] = %d\n", i, i, val);
    //     }
    //     else if (info == GrB_NO_VALUE)
    //     {
    //         printf("[%lu,%lu] no value\n", i, i);
    //     }
    //     else
    //     {
    //         printf("[%lu,%lu] error code: %d\n", i, i, info);
    //     }
    // }

    // ------------------------------------------------------------------------
    // apply user filters
    // ------------------------------------------------------------------------
    GrB_BinaryOp bool_add_op;
    info = GrB_BinaryOp_new(&bool_add_op, (GxB_binary_function)&owns_bool_add, GrB_BOOL, GrB_BOOL, GrB_BOOL);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create owns bool add binop %d\n", info);
        return 1;
    }
    GrB_BinaryOp owns_bool_mul_op;
    info = GrB_BinaryOp_new(&owns_bool_mul_op, (GxB_binary_function)&owns_bool_mult, GrB_BOOL, GrB_BOOL, owns_edge);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create owns bool mul binop %d\n", info);
        return 1;
    }

    GrB_Monoid owns_bool_monoid;
    bool owns_bool_identity = false;
    info = GrB_Monoid_new_BOOL(&owns_bool_monoid, bool_add_op, (void *)&owns_bool_identity);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create owns bool monoid %d\n", info);
        return 1;
    }

    // GrB_Monoid any_monoid;
    // EdgeOwns ownsID = {1};
    // GrB_Monoid_new_UDT(&any_monoid, any_op, (void *)&ownsID);

    GrB_Semiring owns_semiring_bool;
    GrB_Semiring_new(&owns_semiring_bool, owns_bool_monoid, owns_bool_mul_op);

    GrB_Matrix owns_mat_filtered;
    GrB_Matrix_new(&owns_mat_filtered, GrB_BOOL, VERTICES_NUMBER, VERTICES_NUMBER);
    printf("\nowns edge mat before filter\n");
    for (GrB_Index i = 0; i < VERTICES_NUMBER; i++)
        for (GrB_Index j = 0; j < VERTICES_NUMBER; j++)
        {
            EdgeOwns val;
            GrB_Info info = GrB_Matrix_extractElement_UDT(&val, owns_edge_mat, i, j);
            if (info == GrB_SUCCESS)
            {
                printf("[%lu,%lu] = %d\n", i, j, val.days);
            }
            // else if (info == GrB_NO_VALUE)
            // {
            //     printf("[%lu,%lu] no value\n", i, j);
            // }
            // else
            // {
            //     printf("[%lu,%lu] error code: %d\n", i, j, info);
            // }
        }
    // apply filter
    // info = GrB_Matrix_assign(owns_mat_filtered, kron, NULL, owns_edge_mat, GrB_ALL, VERTICES_NUMBER, GrB_ALL, VERTICES_NUMBER, NULL);
    info = GrB_mxm(owns_mat_filtered, NULL, NULL, owns_semiring_bool, ID, owns_edge_mat, NULL);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to apply filter to owns matrix %d\n", info);
        return 1;
    }
    printf("\nowns edge mat after filter\n");
    for (GrB_Index i = 0; i < VERTICES_NUMBER; i++)
        for (GrB_Index j = 0; j < VERTICES_NUMBER; j++)
        {
            EdgeOwns val;
            GrB_Info info = GrB_Matrix_extractElement_UDT(&val, owns_mat_filtered, i, j);
            if (info == GrB_SUCCESS)
            {
                printf("[%lu,%lu] = %d\n", i, j, val.days);
            }
            // else if (info == GrB_NO_VALUE)
            // {
            //     printf("[%lu,%lu] no value\n", i, j);
            // }
            // else
            // {
            //     printf("[%lu,%lu] error code: %d\n", i, j, info);
            // }
        }

    // ------------------------------------------------------------------------
    // get cards of filtered users
    // ------------------------------------------------------------------------

    GrB_Vector filtered_cards;
    info = GrB_Vector_new(&filtered_cards, GrB_BOOL, VERTICES_NUMBER);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create filtered cards vector %d\n", info);
        return 1;
    }
    GxB_print(owns_mat_filtered, GxB_COMPLETE);
    info = GrB_Matrix_reduce_Monoid(filtered_cards, NULL, NULL, GrB_LOR_MONOID_BOOL, owns_mat_filtered, GrB_DESC_T0);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to filter cards %d\n", info);
        return 1;
    }

    // ------------------------------------------------------------------------
    // build filter for tx matrix
    // ------------------------------------------------------------------------
    GrB_Matrix_free(&ID);
    info = GrB_Matrix_diag(&ID, filtered_cards, 0);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create filter matrix %d\n", info);
        return 1;
    }
    GxB_print(ID, GxB_COMPLETE);

    // ------------------------------------------------------------------------
    // apply cards filter to tx matrix
    // ------------------------------------------------------------------------

    GrB_BinaryOp tx_bool_add_op;
    info = GrB_BinaryOp_new(&tx_bool_add_op,
                            (GxB_binary_function)&tx_bool_add,
                            tx_edge,
                            tx_edge,
                            tx_edge);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create tx bool add binop %d\n", info);
        return 1;
    }

    GrB_BinaryOp tx_bool_mul_op;
    info = GrB_BinaryOp_new(&tx_bool_mul_op,
                            (GxB_binary_function)&tx_bool_mult,
                            tx_edge,
                            GrB_BOOL,
                            tx_edge);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create tx bool mul binop %d\n", info);
        return 1;
    }

    EdgeTX tx_identity = {0.0, 0};
    GrB_Monoid tx_bool_monoid;
    info = GrB_Monoid_new_UDT(&tx_bool_monoid, tx_bool_add_op, &tx_identity);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create tx bool monoid %d\n", info);
        return 1;
    }

    GrB_Semiring tx_bool_semiring;
    info = GrB_Semiring_new(&tx_bool_semiring, tx_bool_monoid, tx_bool_mul_op);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create tx bool semiring %d\n", info);
        return 1;
    }

    GrB_BinaryOp tx_bool_mul_right_op;
    info = GrB_BinaryOp_new(&tx_bool_mul_right_op,
                            (GxB_binary_function)&tx_bool_mult_right,
                            tx_edge,
                            tx_edge,
                            GrB_BOOL);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create tx right binop %d\n", info);
        return 1;
    }

    GrB_Semiring tx_bool_semiring_right;
    info = GrB_Semiring_new(&tx_bool_semiring_right, tx_bool_monoid, tx_bool_mul_right_op);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create tx right semiring %d\n", info);
        return 1;
    }
    GrB_Matrix tx_mat_filtered;
    GrB_Matrix_new(&tx_mat_filtered, tx_edge, VERTICES_NUMBER, VERTICES_NUMBER);
    info = GrB_mxm(tx_mat_filtered, NULL, NULL, tx_bool_semiring, ID, tx_edge_mat, NULL);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to apply1 filter to tx matrix %d\n", info);
        return 1;
    }
    GrB_Matrix tx_mat_filtered2;
    GrB_Matrix_new(&tx_mat_filtered2, tx_edge, VERTICES_NUMBER, VERTICES_NUMBER);
    info = GrB_mxm(tx_mat_filtered2, NULL, NULL, tx_bool_semiring_right, tx_mat_filtered, ID, NULL);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to apply2 filter to tx matrix %d\n", info);
        return 1;
    }

    GxB_print(tx_mat_filtered2, GxB_COMPLETE);
    printf("Non-zero edges in tx_mat_filtered2:\n");
    for (GrB_Index i = 0; i < VERTICES_NUMBER; i++)
        for (GrB_Index j = 0; j < VERTICES_NUMBER; j++)
        {
            EdgeTX val;
            if (GrB_Matrix_extractElement_UDT(&val, tx_mat_filtered2, i, j) == GrB_SUCCESS)
            {
                if (val.count > 0)
                    printf("(%lu,%lu): sum=%.1f count=%u\n", i, j, val.sum, val.count);
            }
        }
    GrB_UnaryOp tx_is_nonempty_op;
    info = GxB_UnaryOp_new(&tx_is_nonempty_op,
                           (GxB_unary_function)&tx_is_nonempty,
                           GrB_BOOL,
                           tx_edge, NULL, NULL);
    if (info != GrB_SUCCESS)
    { /* handle */
    }

    GrB_Matrix keep;
    info = GrB_Matrix_new(&keep, GrB_BOOL, VERTICES_NUMBER, VERTICES_NUMBER);
    if (info != GrB_SUCCESS)
    { /* handle */
    }

    info = GrB_apply(keep, NULL, NULL, tx_is_nonempty_op, tx_mat_filtered2, NULL);
    if (info != GrB_SUCCESS)
    { /* handle */
    }
    GxB_print(keep, GxB_COMPLETE);
    GrB_Matrix tx_clean;
    info = GrB_Matrix_new(&tx_clean, tx_edge, VERTICES_NUMBER, VERTICES_NUMBER);
    if (info != GrB_SUCCESS)
    { /* handle */
    }

    info = GrB_assign(tx_clean, keep, NULL,
                      tx_mat_filtered2,
                      GrB_ALL, VERTICES_NUMBER,
                      GrB_ALL, VERTICES_NUMBER,
                      NULL);
    if (info != GrB_SUCCESS)
    { /* handle */
    }

    GxB_print(tx_clean, GxB_COMPLETE);

    // ------------------------------------------------------------------------
    // build matrix for pagerank
    // ------------------------------------------------------------------------

    // apply some F function to every element of result EdgeTX matrix (Fmat)
    GrB_UnaryOp mean_op;
    info = GrB_UnaryOp_new(&mean_op, (GxB_unary_function)&F_op, GrB_FP64, tx_edge);
    GrB_Matrix Fmat;
    info = GrB_Matrix_new(&Fmat, GrB_FP64, VERTICES_NUMBER, VERTICES_NUMBER);
    info = GrB_Matrix_apply(Fmat, NULL, NULL, mean_op, tx_clean, NULL);
    GxB_print(Fmat, GxB_COMPLETE);

    // apply exp function to every element of every element of matrix (lEXPmat)
    GrB_Matrix EXPmat;
    GrB_UnaryOp exp_op;
    info = GrB_UnaryOp_new(&exp_op, (GxB_unary_function)&exp_binop, GrB_FP64, GrB_FP64);
    info = GrB_Matrix_new(&EXPmat, GrB_FP64, VERTICES_NUMBER, VERTICES_NUMBER);
    info = GrB_Matrix_apply(EXPmat, NULL, NULL, exp_op, Fmat, NULL);
    GxB_print(EXPmat, GxB_COMPLETE);

    // reduce EXPmat and receive vector of rows sum (EXPSUMvec)
    GrB_Vector EXPSUMvec;
    info = GrB_Vector_new(&EXPSUMvec,GrB_FP64,VERTICES_NUMBER);
    info = GrB_Matrix_reduce_Monoid(EXPSUMvec,NULL,NULL,GrB_PLUS_MONOID_FP64,EXPmat,NULL);
    GxB_print(EXPSUMvec, GxB_COMPLETE);

    // do masked kroneker (mask: EXPmat, A: EXPSUMvec, B: ID vector) (KRONEXPSUMmat)
    GrB_Matrix KRONEXPSUMmat;
    GrB_Vector id_final;
    info = GrB_Vector_new(&id_final,GrB_FP64,VERTICES_NUMBER);
    info = GrB_Vector_assign_BOOL(v, NULL, NULL, 1.0, GrB_ALL, VERTICES_NUMBER, NULL);
    
    

    // define add operation (A + B = A / B) (divv)

    // apply divv to (EXPmat and KRONEXPSUMmat) (M)
    GrB_Matrix M;
    // ------------------------------------------------------------------------
    // run pagerank
    // ------------------------------------------------------------------------
    int iteraions = 0;
    GrB_Vector pagerank_ans;
    GrB_Vector_new(&pagerank_ans, GrB_FP64, VERTICES_NUMBER);

    LAGraph_Graph G = NULL;

    info = LAGraph_New(&G, &M, LAGraph_ADJACENCY_DIRECTED, msg);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create LAGraph_Graph: %d\n", info);
        return 1;
    }

    LAGr_PageRank(&pagerank_ans, &iteraions, G, 0.85, 1e-4, 100, msg);
}