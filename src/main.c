#include <stdio.h>
#include <stdint.h>
#include "../vendor/GraphBLAS/Include/GraphBLAS.h"
#include "../vendor/LAGraph/include/LAGraph.h"
#include "../vendor/LAGraph/include/LAGraphX.h"

#define TRY(method)                                     \
    {                                                   \
        GrB_Info _info = (method);                      \
        if (_info != GrB_SUCCESS)                       \
        {                                               \
            fprintf(stderr,                             \
                    #method " : GraphBLAS error %d \n", \
                    _info);                             \
            return _info;                               \
        }                                               \
    }

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
void check_payment_system(bool *z, const Card *x, GrB_Index _i, GrB_Index _j, const uint8_t *y)
{
    {
        *z = ((x->system) == MIR);
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
void divide(double *z, const double *x, const double *y)
{
    *z = (*y != 0.0) ? (*x / *y) : 0.0;
}

GrB_Info init_edges(GrB_Matrix *tx_mat, GrB_Matrix *owns_mat)
{
    GrB_Info info;
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

    TRY(GrB_Matrix_setElement_UDT(*tx_mat, &edge56, 4, 5));
    TRY(GrB_Matrix_setElement_UDT(*tx_mat, &edge59, 4, 8));
    TRY(GrB_Matrix_setElement_UDT(*tx_mat, &edge67, 5, 6));
    TRY(GrB_Matrix_setElement_UDT(*tx_mat, &edge69, 5, 8));
    TRY(GrB_Matrix_setElement_UDT(*tx_mat, &edge95, 8, 4));
    TRY(GrB_Matrix_setElement_UDT(*tx_mat, &edge611, 5, 10));
    TRY(GrB_Matrix_setElement_UDT(*tx_mat, &edge116, 10, 5));
    TRY(GrB_Matrix_setElement_UDT(*tx_mat, &edge511, 4, 10));
    TRY(GrB_Matrix_setElement_UDT(*tx_mat, &edge115, 10, 4));
    TRY(GrB_Matrix_setElement_UDT(*tx_mat, &edge127, 11, 6));
    TRY(GrB_Matrix_setElement_UDT(*tx_mat, &edge712, 6, 11));
    TRY(GrB_Matrix_setElement_UDT(*tx_mat, &edge65, 5, 4));
    TRY(GrB_Matrix_setElement_UDT(*tx_mat, &edge912, 8, 11));
    TRY(GrB_Matrix_setElement_UDT(*tx_mat, &edge129, 11, 8));

    // fill owns_mat
    EdgeOwns edge45 = {45};
    EdgeOwns edge36 = {36};
    EdgeOwns edge19 = {19};
    EdgeOwns edge27 = {27};
    EdgeOwns edge28 = {28};
    EdgeOwns edge1011 = {21};
    EdgeOwns edge1012 = {22};
    TRY(GrB_Matrix_setElement_UDT(*owns_mat, &edge45, 3, 4));
    TRY(GrB_Matrix_setElement_UDT(*owns_mat, &edge36, 2, 5));
    TRY(GrB_Matrix_setElement_UDT(*owns_mat, &edge19, 0, 8));
    TRY(GrB_Matrix_setElement_UDT(*owns_mat, &edge27, 1, 6));
    TRY(GrB_Matrix_setElement_UDT(*owns_mat, &edge28, 1, 7));
    TRY(GrB_Matrix_setElement_UDT(*owns_mat, &edge1011, 9, 10));
    TRY(GrB_Matrix_setElement_UDT(*owns_mat, &edge1012, 9, 11));

    return info;
}

GrB_Info init_vertices(GrB_Vector *users, GrB_Vector *cards)
{
    GrB_Info info;
    // 1 - 4 & 10 --- users
    User user1 = {FEMALE, 52};
    User user2 = {FEMALE, 25};
    User user3 = {FEMALE, 40};
    User user4 = {MALE, 42};
    User user10 = {MALE, 35};
    TRY(GrB_Vector_setElement_UDT(*users, &user1, 0));
    TRY(GrB_Vector_setElement_UDT(*users, &user2, 1));
    TRY(GrB_Vector_setElement_UDT(*users, &user3, 2));
    TRY(GrB_Vector_setElement_UDT(*users, &user4, 3));
    TRY(GrB_Vector_setElement_UDT(*users, &user10, 9));

    // 5 - 9 & 11 - 12 --- cards
    Card card5 = {MIR, 600000.0};
    Card card6 = {MIR, 700000.0};
    Card card7 = {VISA, 800000.0};
    Card card8 = {MASTERCARD, 900000.0};
    Card card9 = {VISA, 10000000.0};
    Card card11 = {MIR, 99000000.0};
    Card card12 = {MIR, 99000000.0};
    TRY(GrB_Vector_setElement_UDT(*cards, &card5, 4));
    TRY(GrB_Vector_setElement_UDT(*cards, &card6, 5));
    TRY(GrB_Vector_setElement_UDT(*cards, &card7, 6));
    TRY(GrB_Vector_setElement_UDT(*cards, &card8, 7));
    TRY(GrB_Vector_setElement_UDT(*cards, &card9, 8));
    TRY(GrB_Vector_setElement_UDT(*cards, &card11, 10));
    TRY(GrB_Vector_setElement_UDT(*cards, &card12, 11));

    return info;
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
    TRY(GrB_Type_new(&tx_edge, sizeof(EdgeTX)));
    TRY(GrB_Type_new(&owns_edge, sizeof(EdgeOwns)));

    // edge decomposition

    GrB_Matrix tx_edge_mat, owns_edge_mat;
    TRY(GrB_Matrix_new(&tx_edge_mat, tx_edge, VERTICES_NUMBER, VERTICES_NUMBER));
    TRY(GrB_Matrix_new(&owns_edge_mat, owns_edge, VERTICES_NUMBER, VERTICES_NUMBER));
    init_edges(&tx_edge_mat, &owns_edge_mat);
    // ------------------------------------------------------------------------
    // init vertices vectors
    // ------------------------------------------------------------------------

    GrB_Type user, card;
    TRY(GrB_Type_new(&user, sizeof(User)));

    TRY(GrB_Type_new(&card, sizeof(Card)));

    GrB_Vector users;
    TRY(GrB_Vector_new(&users, user, VERTICES_NUMBER));

    GrB_Vector cards;
    TRY(GrB_Vector_new(&cards, card, VERTICES_NUMBER));
    TRY(init_vertices(&users, &cards));
    // ------------------------------------------------------------------------
    // build user filters
    // ------------------------------------------------------------------------

    // vertex filter: we will take only prersons over 30
    GrB_Matrix ID;
    GrB_Vector v;
    TRY(GrB_Vector_new(&v, GrB_BOOL, VERTICES_NUMBER));
    TRY(GrB_Vector_assign_BOOL(v, NULL, NULL, false, GrB_ALL, VERTICES_NUMBER, NULL));

    // create selector
    GrB_IndexUnaryOp user_age;
    TRY(GrB_IndexUnaryOp_new(&user_age, (GxB_index_unary_function)&check_user_age, GrB_BOOL, user, GrB_UINT8));
    uint8_t age = 30;
    TRY(GrB_Vector_apply_IndexOp_UDT(v, NULL, NULL, user_age, users, &age, NULL));
    GxB_print(v, GxB_COMPLETE);
    TRY(GrB_Matrix_diag(&ID, v, 0));

    // ------------------------------------------------------------------------
    // apply user filters
    // ------------------------------------------------------------------------
    GrB_BinaryOp bool_add_op;
    TRY(GrB_BinaryOp_new(&bool_add_op, (GxB_binary_function)&owns_bool_add, GrB_BOOL, GrB_BOOL, GrB_BOOL));
    GrB_BinaryOp owns_bool_mul_op;
    TRY(GrB_BinaryOp_new(&owns_bool_mul_op, (GxB_binary_function)&owns_bool_mult, GrB_BOOL, GrB_BOOL, owns_edge));

    GrB_Monoid owns_bool_monoid;
    bool owns_bool_identity = false;
    TRY(GrB_Monoid_new_BOOL(&owns_bool_monoid, bool_add_op, (void *)&owns_bool_identity));

    GrB_Semiring owns_semiring_bool;
    TRY(GrB_Semiring_new(&owns_semiring_bool, owns_bool_monoid, owns_bool_mul_op));

    GrB_Matrix owns_mat_filtered;
    TRY(GrB_Matrix_new(&owns_mat_filtered, GrB_BOOL, VERTICES_NUMBER, VERTICES_NUMBER));
    // apply filter
    TRY(GrB_mxm(owns_mat_filtered, NULL, NULL, owns_semiring_bool, ID, owns_edge_mat, NULL));

    // ------------------------------------------------------------------------
    // get cards of filtered users
    // ------------------------------------------------------------------------

    GrB_Vector filtered_cards;
    TRY(GrB_Vector_new(&filtered_cards, GrB_BOOL, VERTICES_NUMBER));
    GxB_print(owns_mat_filtered, GxB_COMPLETE);
    TRY(GrB_Matrix_reduce_Monoid(filtered_cards, NULL, NULL, GrB_LOR_MONOID_BOOL, owns_mat_filtered, GrB_DESC_T0));

    // ------------------------------------------------------------------------
    // build filter for tx matrix
    // ------------------------------------------------------------------------
    
    // get cards with MIR payment system only
    TRY(GrB_Matrix_free(&ID));
    TRY(GrB_Vector_free(&v));
    TRY(GrB_Vector_new(&v, GrB_BOOL, VERTICES_NUMBER));
    TRY(GrB_Vector_assign_BOOL(v, NULL, NULL, false, GrB_ALL, VERTICES_NUMBER, NULL));
    GrB_IndexUnaryOp payment_system;
    TRY(GrB_IndexUnaryOp_new(&payment_system, (GxB_index_unary_function)&check_payment_system, GrB_BOOL, card, GrB_UINT8));
    uint8_t pay_sys = MIR;
    TRY(GrB_Vector_apply_IndexOp_UDT(v, NULL, NULL, payment_system, cards, &pay_sys, NULL));
    TRY(GrB_Vector_eWiseMult_BinaryOp(filtered_cards, NULL, NULL, GrB_LAND, filtered_cards, v, NULL));

    TRY(GrB_Matrix_diag(&ID, filtered_cards, 0));
    GxB_print(ID, GxB_COMPLETE);

    // ------------------------------------------------------------------------
    // apply cards filter to tx matrix
    // ------------------------------------------------------------------------

    GrB_BinaryOp tx_bool_add_op;
    TRY(GrB_BinaryOp_new(&tx_bool_add_op, (GxB_binary_function)&tx_bool_add, tx_edge, tx_edge, tx_edge));

    GrB_BinaryOp tx_bool_mul_op;
    TRY(GrB_BinaryOp_new(&tx_bool_mul_op, (GxB_binary_function)&tx_bool_mult, tx_edge, GrB_BOOL, tx_edge));

    EdgeTX tx_identity = {0.0, 0};
    GrB_Monoid tx_bool_monoid;
    TRY(GrB_Monoid_new_UDT(&tx_bool_monoid, tx_bool_add_op, &tx_identity));

    GrB_Semiring tx_bool_semiring;
    TRY(GrB_Semiring_new(&tx_bool_semiring, tx_bool_monoid, tx_bool_mul_op));

    GrB_BinaryOp tx_bool_mul_right_op;
    TRY(GrB_BinaryOp_new(&tx_bool_mul_right_op, (GxB_binary_function)&tx_bool_mult_right, tx_edge, tx_edge, GrB_BOOL));

    GrB_Semiring tx_bool_semiring_right;
    TRY(GrB_Semiring_new(&tx_bool_semiring_right, tx_bool_monoid, tx_bool_mul_right_op));
    GrB_Matrix tx_mat_filtered;
    TRY(GrB_Matrix_new(&tx_mat_filtered, tx_edge, VERTICES_NUMBER, VERTICES_NUMBER));
    TRY(GrB_mxm(tx_mat_filtered, NULL, NULL, tx_bool_semiring, ID, tx_edge_mat, NULL));
    GrB_Matrix tx_mat_filtered2;
    TRY(GrB_Matrix_new(&tx_mat_filtered2, tx_edge, VERTICES_NUMBER, VERTICES_NUMBER));
    TRY(GrB_mxm(tx_mat_filtered2, NULL, NULL, tx_bool_semiring_right, tx_mat_filtered, ID, NULL));

    GxB_print(tx_mat_filtered2, GxB_COMPLETE);

    GrB_UnaryOp tx_is_nonempty_op;
    TRY(GxB_UnaryOp_new(&tx_is_nonempty_op, (GxB_unary_function)&tx_is_nonempty, GrB_BOOL, tx_edge, NULL, NULL));

    GrB_Matrix keep;
    TRY(GrB_Matrix_new(&keep, GrB_BOOL, VERTICES_NUMBER, VERTICES_NUMBER));
    TRY(GrB_apply(keep, NULL, NULL, tx_is_nonempty_op, tx_mat_filtered2, NULL));
    GxB_print(keep, GxB_COMPLETE);
    GrB_Matrix tx_clean;
    TRY(GrB_Matrix_new(&tx_clean, tx_edge, VERTICES_NUMBER, VERTICES_NUMBER));

    TRY(GrB_assign(tx_clean, keep, NULL, tx_mat_filtered2, GrB_ALL, VERTICES_NUMBER, GrB_ALL, VERTICES_NUMBER, NULL));

    GxB_print(tx_clean, GxB_COMPLETE);

    // ------------------------------------------------------------------------
    // build matrix for pagerank
    // ------------------------------------------------------------------------

    // apply some F function to every element of result EdgeTX matrix (Fmat)
    GrB_UnaryOp mean_op;
    TRY(GrB_UnaryOp_new(&mean_op, (GxB_unary_function)&F_op, GrB_FP64, tx_edge));
    GrB_Matrix Fmat;
    TRY(GrB_Matrix_new(&Fmat, GrB_FP64, VERTICES_NUMBER, VERTICES_NUMBER));
    TRY(GrB_Matrix_apply(Fmat, NULL, NULL, mean_op, tx_clean, NULL));
    GxB_print(Fmat, GxB_COMPLETE);

    // apply exp function to every element of every element of matrix (lEXPmat)
    GrB_Matrix EXPmat;
    GrB_UnaryOp exp_op;
    TRY(GrB_UnaryOp_new(&exp_op, (GxB_unary_function)&exp_binop, GrB_FP64, GrB_FP64));
    TRY(GrB_Matrix_new(&EXPmat, GrB_FP64, VERTICES_NUMBER, VERTICES_NUMBER));
    TRY(GrB_Matrix_apply(EXPmat, NULL, NULL, exp_op, Fmat, NULL));
    GxB_print(EXPmat, GxB_COMPLETE);

    // reduce EXPmat and receive vector of rows sum (EXPSUMvec)
    GrB_Vector EXPSUMvec;
    TRY(GrB_Vector_new(&EXPSUMvec, GrB_FP64, VERTICES_NUMBER));
    TRY(GrB_Matrix_reduce_Monoid(EXPSUMvec, NULL, NULL, GrB_PLUS_MONOID_FP64, EXPmat, NULL));
    GxB_print(EXPSUMvec, GxB_COMPLETE);

    // do masked kroneker (mask: EXPmat, A: EXPSUMvec, B: ID vector) (KRONEXPSUMmat)

    GrB_Vector id_final;
    TRY(GrB_Vector_new(&id_final, GrB_FP64, VERTICES_NUMBER));
    TRY(GrB_Vector_assign_BOOL(id_final, NULL, NULL, 1.0, GrB_ALL, VERTICES_NUMBER, NULL));
    GrB_Matrix v_mat, id_mat;
    TRY(GrB_Matrix_new(&v_mat, GrB_FP64, VERTICES_NUMBER, 1));
    TRY(GrB_Col_assign(v_mat, NULL, NULL, EXPSUMvec, GrB_ALL, VERTICES_NUMBER, 0, NULL));

    TRY(GrB_Matrix_new(&id_mat, GrB_FP64, 1, VERTICES_NUMBER));
    TRY(GrB_Row_assign(id_mat, NULL, NULL, id_final, 0, GrB_ALL, VERTICES_NUMBER, NULL));

    GrB_Matrix KRONEXPSUMmat;
    TRY(GrB_Matrix_new(&KRONEXPSUMmat, GrB_FP64, VERTICES_NUMBER, VERTICES_NUMBER));

    TRY(GrB_mxm(KRONEXPSUMmat, NULL, NULL, GxB_PLUS_TIMES_FP64, v_mat, id_mat, NULL));
    GxB_print(KRONEXPSUMmat, GxB_COMPLETE);

    // apply div to (EXPmat and KRONEXPSUMmat) (M)
    GrB_Matrix M;
    TRY(GrB_Matrix_new(&M, GrB_FP64, VERTICES_NUMBER, VERTICES_NUMBER));
    // define add operation (A + B = A / B) (div)
    GrB_BinaryOp divide_op;
    TRY(GrB_BinaryOp_new(&divide_op, (GxB_binary_function)&divide, GrB_FP64, GrB_FP64, GrB_FP64));
    TRY(GrB_Matrix_eWiseAdd_BinaryOp(M, EXPmat, NULL, divide_op, EXPmat, KRONEXPSUMmat, NULL));
    GxB_print(M, GxB_COMPLETE);

    // ------------------------------------------------------------------------
    // run pagerank
    // ------------------------------------------------------------------------
    int iteraions = 0;
    GrB_Vector pagerank_ans;
    TRY(GrB_Vector_new(&pagerank_ans, GrB_FP64, VERTICES_NUMBER));

    LAGraph_Graph G = NULL;

    TRY(LAGraph_New(&G, &M, LAGraph_ADJACENCY_DIRECTED, msg));
    TRY(LAGraph_Cached_AT(G, msg));

    TRY(LAGraph_Cached_OutDegree(G, msg));

    TRY(LAGr_PageRank(&pagerank_ans, &iteraions, G, 0.85, 1e-4, 100, msg));
    GxB_print(pagerank_ans, GxB_COMPLETE);
}