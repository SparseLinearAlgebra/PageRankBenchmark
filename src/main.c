#include <stdio.h>
#include <stdint.h>
#include "../vendor/GraphBLAS/Include/GraphBLAS.h"

#define TRY(method)                                                          \
    {                                                                        \
        GrB_Info _info = (method);                                           \
        if (_info != GrB_SUCCESS)                                            \
        {                                                                    \
            fprintf(stderr,                                                  \
                    #method " : GraphBLAS error %d in file %s at line %d\n", \
                    _info, __FILE__, __LINE__);                              \
            return _info;                                                    \
        }                                                                    \
    }

#define VERTICES_NUMBER 12

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

// edges
typedef struct
{
    double sum;
    uint32_t count;
} EdgeTX;

void check_user_age(bool *z, const User *x, GrB_Index i, GrB_Index j, const uint8_t *y)
{

    *z = (x->age > *y);
}

bool user_filter_mul(bool *z, const User *x, const bool *y)
{
    *z = *y;
}

void check_payment_system(bool *z, const Card *x, GrB_Index _i, GrB_Index _j, const uint8_t *y)
{

    *z = ((x->system) == *y);
}

void tx_bool_mult(EdgeTX *z, const Card *x, const EdgeTX *y)
{
    *z = *y;
}

void tx_bool_mult_right(EdgeTX *z, const EdgeTX *x, const Card *y)
{

    *z = *x;
}

void tx_bool_add(EdgeTX *z, const EdgeTX *x, const EdgeTX *y)
{

    *z = *x;
}

void exp_binop(double *z, const double *x)
{
    *z = exp(*x);
}

void F_op(double *z, const EdgeTX *x)
{
    *z = (x->sum / 1000) / (x->count);
}
void divide(double *z, const double *x, const double *y)
{
    *z = (*y != 0.0) ? (*x / *y) : 0.0;
}

GrB_Type user, card;
GrB_Type tx_edge;

GrB_Info init_edges(GrB_Matrix *tx_mat, GrB_Matrix *owns_mat)
{
    GrB_Info info;
    EdgeTX edge56 = {23412.0, 6};
    EdgeTX edge59 = {62412.0, 9};
    EdgeTX edge67 = {81312.0, 7};
    EdgeTX edge69 = {92223.0, 9};
    EdgeTX edge65 = {13214.1, 5};
    EdgeTX edge95 = {16325.99, 9};
    EdgeTX edge611 = {19999.1, 6};
    EdgeTX edge116 = {69999.1, 16};
    EdgeTX edge511 = {99999.1, 5};
    EdgeTX edge115 = {79999.1, 15};
    EdgeTX edge127 = {59999.1, 12};
    EdgeTX edge712 = {8999.1, 7};
    EdgeTX edge912 = {49999.1, 12};
    EdgeTX edge129 = {999999.1, 9};

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
    bool edge45 = true;
    bool edge36 = true;
    bool edge19 = true;
    bool edge27 = true;
    bool edge28 = true;
    bool edge1011 = true;
    bool edge1012 = true;
    TRY(GrB_Matrix_setElement_BOOL(*owns_mat, &edge45, 3, 4));
    TRY(GrB_Matrix_setElement_BOOL(*owns_mat, &edge36, 2, 5));
    TRY(GrB_Matrix_setElement_BOOL(*owns_mat, &edge19, 0, 8));
    TRY(GrB_Matrix_setElement_BOOL(*owns_mat, &edge27, 1, 6));
    TRY(GrB_Matrix_setElement_BOOL(*owns_mat, &edge28, 1, 7));
    TRY(GrB_Matrix_setElement_BOOL(*owns_mat, &edge1011, 9, 10));
    TRY(GrB_Matrix_setElement_BOOL(*owns_mat, &edge1012, 9, 11));

    return GrB_SUCCESS;
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

    return GrB_SUCCESS;
}

int banking_pagerank(
    // output
    GrB_Vector *centrality,
    int *iters,
    // input
    GrB_Vector subgraph,
    const GrB_Matrix A,
    float tol,
    int itermax)
{
    GrB_Vector r = NULL, t = NULL;
    GrB_Matrix AT;
    GrB_Index n;
    GrB_Matrix_nrows(&n, A);
    GrB_Matrix_new(&AT, GrB_FP64, n, n);
    GrB_transpose(AT, NULL, NULL, A, NULL);

    // ------------------------------------------------------------------------
    // initialization
    // ------------------------------------------------------------------------

    GrB_Vector_new(&t, GrB_FP64, n);
    GrB_Vector_new(&r, GrB_FP64, n);

    double init = 1.0 / (double)n;
    GrB_assign(r, subgraph, NULL, init, GrB_ALL, n, NULL);

    double rdiff = 1.0;

    // ------------------------------------------------------------------------
    // iterations
    // ------------------------------------------------------------------------
    for ((*iters) = 0; rdiff > tol && (*iters) < itermax; (*iters)++)
    {
        // swap
        GrB_Vector temp = t;
        t = r;
        r = temp;

        // r = A' * t
        GrB_mxv(r, NULL, NULL, GxB_PLUS_TIMES_FP64, AT, t, NULL);

        // normalize r so that sum(r) = 1. otherwise we lost this invariant
        double sum_r = 0.0;
        GrB_reduce(&sum_r, NULL, GrB_PLUS_MONOID_FP64, r, NULL);
        if (sum_r > 0.0)
        {
            GrB_apply(r, NULL, NULL, GrB_DIV_FP64, r, sum_r, NULL);
        }

        // compute difference
        GrB_assign(t, NULL, GrB_MINUS_FP64, r, GrB_ALL, n, NULL);
        GrB_apply(t, NULL, NULL, GrB_ABS_FP64, t, NULL);
        GrB_reduce(&rdiff, NULL, GrB_PLUS_MONOID_FP64, t, NULL);
    }

    // ------------------------------------------------------------------------
    // finalize
    // ------------------------------------------------------------------------
    *centrality = r;
    GrB_free(&t);
    return GrB_SUCCESS;
}

GrB_Info analyze_graph(GrB_Matrix tx_edge_mat, GrB_Matrix owns_edge_mat, GrB_Vector users, GrB_Vector cards)
{
    // ------------------------------------------------------------------------
    // build user filters
    // ------------------------------------------------------------------------

    // take persons over 30
    GrB_IndexUnaryOp user_age;
    TRY(GrB_IndexUnaryOp_new(&user_age, (GxB_index_unary_function)&check_user_age, GrB_BOOL, user, GrB_UINT8));

    uint8_t age = 30;
    GrB_Vector v;
    TRY(GrB_Vector_new(&v, user, VERTICES_NUMBER));

    TRY(GrB_Vector_select_UDT(v, NULL, NULL, user_age, users, &age, NULL));

    GxB_print(v, GxB_COMPLETE);

    // ------------------------------------------------------------------------
    // apply user filters
    // ------------------------------------------------------------------------

    GrB_BinaryOp user_filter_mul_op;
    TRY(GrB_BinaryOp_new(&user_filter_mul_op, (GxB_binary_function)user_filter_mul,
                         GrB_BOOL, user, GrB_BOOL));

    GrB_Semiring user_filter_semiring;
    TRY(GrB_Semiring_new(&user_filter_semiring, GrB_LOR_MONOID_BOOL, user_filter_mul_op));
    GrB_Vector filtered_cards;
    TRY(GrB_Vector_new(&filtered_cards, GrB_BOOL, VERTICES_NUMBER));
    // apply filter
    TRY(GrB_vxm(filtered_cards, NULL, NULL, user_filter_semiring, v, owns_edge_mat, NULL));
    GxB_print(filtered_cards, GxB_COMPLETE);

    // ------------------------------------------------------------------------
    // build filter for tx matrix
    // ------------------------------------------------------------------------

    // get cards with MIR payment system only
    GrB_Matrix ID;
    TRY(GrB_Vector_free(&v));
    TRY(GrB_Vector_new(&v, card, VERTICES_NUMBER));
    GrB_IndexUnaryOp payment_system;
    TRY(GrB_IndexUnaryOp_new(&payment_system, (GxB_index_unary_function)&check_payment_system, GrB_BOOL, card, GrB_UINT8));
    uint8_t pay_sys = MIR;
    TRY(GrB_Vector_select_UDT(v, NULL, NULL, payment_system, cards, &pay_sys, NULL));
    GxB_print(filtered_cards, GxB_COMPLETE);
    GxB_print(v, GxB_COMPLETE);
    GrB_Vector result_cards;
    GrB_Vector_new(&result_cards, card, VERTICES_NUMBER);
    TRY(GrB_Vector_assign(result_cards, filtered_cards, NULL, v, GrB_ALL, VERTICES_NUMBER, NULL));
    GxB_print(result_cards, GxB_COMPLETE);

    TRY(GrB_Matrix_diag(&ID, result_cards, 0));
    GxB_print(ID, GxB_COMPLETE);

    // ------------------------------------------------------------------------
    // apply cards filter to tx matrix
    // ------------------------------------------------------------------------

    // receive transactions between cards of the "MIR" payment system for users over 30 years old

    // create semiring to process A x B where A has type Card and B has type EdgeTX
    GrB_BinaryOp tx_bool_add_op;
    TRY(GrB_BinaryOp_new(&tx_bool_add_op, (GxB_binary_function)&tx_bool_add, tx_edge, tx_edge, tx_edge));

    GrB_BinaryOp tx_bool_mul_op;
    TRY(GrB_BinaryOp_new(&tx_bool_mul_op, (GxB_binary_function)&tx_bool_mult, tx_edge, card, tx_edge));

    EdgeTX tx_identity = {0.0, 0};
    GrB_Monoid tx_bool_monoid;
    TRY(GrB_Monoid_new_UDT(&tx_bool_monoid, tx_bool_add_op, &tx_identity));

    GrB_Semiring tx_bool_semiring;
    TRY(GrB_Semiring_new(&tx_bool_semiring, tx_bool_monoid, tx_bool_mul_op));

    GrB_Matrix tx_mat_filtered;
    TRY(GrB_Matrix_new(&tx_mat_filtered, tx_edge, VERTICES_NUMBER, VERTICES_NUMBER));

    // filter rows of source transactions matrix
    TRY(GrB_mxm(tx_mat_filtered, NULL, NULL, tx_bool_semiring, ID, tx_edge_mat, NULL));

    // create semiring to process A x B where A has type EdgeTX and B has type Card
    GrB_Matrix tx_mat_filtered2;
    GrB_BinaryOp tx_bool_mul_right_op;
    TRY(GrB_BinaryOp_new(&tx_bool_mul_right_op, (GxB_binary_function)&tx_bool_mult_right, tx_edge, tx_edge, card));

    GrB_Semiring tx_bool_semiring_right;
    TRY(GrB_Semiring_new(&tx_bool_semiring_right, tx_bool_monoid, tx_bool_mul_right_op));

    TRY(GrB_Matrix_new(&tx_mat_filtered2, tx_edge, VERTICES_NUMBER, VERTICES_NUMBER));
    // filter columns of source transactions matrix
    TRY(GrB_mxm(tx_mat_filtered2, NULL, NULL, tx_bool_semiring_right, tx_mat_filtered, ID, NULL));

    GxB_print(tx_mat_filtered2, GxB_COMPLETE);

    // ------------------------------------------------------------------------
    // build matrix for pagerank
    // ------------------------------------------------------------------------

    // apply some F function to every element of result EdgeTX matrix (Fmat)
    GrB_UnaryOp mean_op;
    TRY(GrB_UnaryOp_new(&mean_op, (GxB_unary_function)&F_op, GrB_FP64, tx_edge));
    GrB_Matrix Fmat;
    TRY(GrB_Matrix_new(&Fmat, GrB_FP64, VERTICES_NUMBER, VERTICES_NUMBER));
    TRY(GrB_Matrix_apply(Fmat, NULL, NULL, mean_op, tx_mat_filtered2, NULL));
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

    // do masked mxm (mask: EXPmat, A: EXPSUMvec, B: ID vector) (EXPSUMmat)

    GrB_Vector id_final;
    TRY(GrB_Vector_new(&id_final, GrB_FP64, VERTICES_NUMBER));
    TRY(GrB_Vector_assign_BOOL(id_final, NULL, NULL, true, GrB_ALL, VERTICES_NUMBER, NULL));
    GrB_Matrix v_mat, id_mat;
    TRY(GrB_Matrix_new(&v_mat, GrB_FP64, VERTICES_NUMBER, 1));
    TRY(GrB_Col_assign(v_mat, NULL, NULL, EXPSUMvec, GrB_ALL, VERTICES_NUMBER, 0, NULL));

    TRY(GrB_Matrix_new(&id_mat, GrB_FP64, 1, VERTICES_NUMBER));
    TRY(GrB_Row_assign(id_mat, NULL, NULL, id_final, 0, GrB_ALL, VERTICES_NUMBER, NULL));

    GrB_Matrix EXPSUMmat;
    TRY(GrB_Matrix_new(&EXPSUMmat, GrB_FP64, VERTICES_NUMBER, VERTICES_NUMBER));

    TRY(GrB_mxm(EXPSUMmat, EXPmat, NULL, GxB_PLUS_TIMES_FP64, v_mat, id_mat, NULL));
    GxB_print(EXPSUMmat, GxB_COMPLETE);

    // apply div to (EXPmat and EXPSUMmat) (M)
    GrB_Matrix M;
    TRY(GrB_Matrix_new(&M, GrB_FP64, VERTICES_NUMBER, VERTICES_NUMBER));
    // define add operation (A + B = A / B) (div)
    GrB_BinaryOp divide_op;
    TRY(GrB_BinaryOp_new(&divide_op, (GxB_binary_function)&divide, GrB_FP64, GrB_FP64, GrB_FP64));
    TRY(GrB_Matrix_eWiseAdd_BinaryOp(M, NULL, NULL, divide_op, EXPmat, EXPSUMmat, NULL));
    GxB_print(M, GxB_COMPLETE);

    // ------------------------------------------------------------------------
    // run pagerank
    // ------------------------------------------------------------------------

    int iteraions = 0;
    GrB_Vector pagerank_ans;
    TRY(GrB_Vector_new(&pagerank_ans, GrB_FP64, VERTICES_NUMBER));

    TRY(banking_pagerank(&pagerank_ans, &iteraions, EXPSUMvec, M, 1e-4, 100));
    GxB_print(pagerank_ans, GxB_COMPLETE);

    // ------------------------------------------------------------------------
    // clean up
    // ------------------------------------------------------------------------

    GrB_free(&ID);
    GrB_free(&v);
    GrB_free(&filtered_cards);
    GrB_free(&tx_bool_add_op);
    GrB_free(&tx_bool_mul_op);
    GrB_free(&tx_bool_mul_right_op);
    GrB_free(&tx_bool_monoid);
    GrB_free(&tx_bool_semiring);
    GrB_free(&tx_bool_semiring_right);
    GrB_free(&tx_mat_filtered);
    GrB_free(&tx_mat_filtered2);
    GrB_free(&mean_op);
    GrB_free(&exp_op);
    GrB_free(&Fmat);
    GrB_free(&EXPmat);
    GrB_free(&EXPSUMvec);
    GrB_free(&id_final);
    GrB_free(&v_mat);
    GrB_free(&id_mat);
    GrB_free(&EXPSUMmat);
    GrB_free(&divide_op);
    GrB_free(&M);
    GrB_free(&pagerank_ans);

    return GrB_SUCCESS;
}

int main()
{
    GrB_init(GrB_NONBLOCKING);
    printf("GraphBLAS initialized.\n\n");

    // ------------------------------------------------------------------------
    // init edge matrices
    // ------------------------------------------------------------------------

    // custom type for transaction edges
    TRY(GrB_Type_new(&tx_edge, sizeof(EdgeTX)));

    // edge decomposition

    GrB_Matrix tx_edge_mat, owns_edge_mat;
    TRY(GrB_Matrix_new(&tx_edge_mat, tx_edge, VERTICES_NUMBER, VERTICES_NUMBER));
    TRY(GrB_Matrix_new(&owns_edge_mat, GrB_BOOL, VERTICES_NUMBER, VERTICES_NUMBER));
    init_edges(&tx_edge_mat, &owns_edge_mat);

    // ------------------------------------------------------------------------
    // init vertices vectors
    // ------------------------------------------------------------------------

    TRY(GrB_Type_new(&user, sizeof(User)));

    TRY(GrB_Type_new(&card, sizeof(Card)));

    GrB_Vector users;
    TRY(GrB_Vector_new(&users, user, VERTICES_NUMBER));

    GrB_Vector cards;
    TRY(GrB_Vector_new(&cards, card, VERTICES_NUMBER));
    TRY(init_vertices(&users, &cards));

    // ------------------------------------------------------------------------
    // run solver
    // ------------------------------------------------------------------------

    TRY(analyze_graph(tx_edge_mat, owns_edge_mat, users, cards));

    // ------------------------------------------------------------------------
    // clean up
    // ------------------------------------------------------------------------

    GrB_free(&tx_edge_mat);
    GrB_free(&owns_edge_mat);
    GrB_free(&users);
    GrB_free(&cards);
    GrB_free(&user);
    GrB_free(&card);
    GrB_free(&tx_edge);
    GrB_finalize();
}
