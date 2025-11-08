#include <stdio.h>
#include <stdint.h>
#include "../vendor/GraphBLAS/Include/GraphBLAS.h"
#include "../vendor/LAGraph/include/LAGraph.h"
#include "../vendor/LAGraph/include/LAGraphX.h"

#define VERTICES_NUMBER 9
#define EDGES_NUBMER 12
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

// operations TODO

void tx_add(EdgeTX *z, EdgeTX *x, EdgeTX *y)
{
}
void tx_mul(EdgeTX *z, EdgeTX *x, EdgeTX *y)
{
}
void owns_add(EdgeOwns *z, EdgeOwns *x, EdgeOwns *y)
{
}
void owns_mul(EdgeOwns *z, EdgeOwns *x, EdgeOwns *y)
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
    printf("LAGraph initialized.\n\n");

    // init edge matrices

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

    // monoid and semiring
    GrB_BinaryOp tx_plus, tx_mult;
    GrB_Monoid tx_monoid;
    GrB_Semiring tx_semiring;
    EdgeTX tx_edge_id;
    info = GrB_BinaryOp_new(&tx_plus, (GxB_binary_function)&tx_add, tx_edge, tx_edge, tx_edge);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"tx_plus\" binop\n");
        return 1;
    }
    info = GrB_BinaryOp_new(&tx_mult, (GxB_binary_function)&tx_mul, tx_edge, tx_edge, tx_edge);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"tx_mult\" binop\n");
        return 1;
    }
    info = GrB_Monoid_new(&tx_monoid, tx_plus, (void *)&tx_edge_id);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"tx\" monoud\n");
        return 1;
    }
    info = GrB_Semiring_new(&tx_semiring, tx_monoid, tx_mult);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"tx\" semiring\n");
        return 1;
    }

    GrB_BinaryOp owns_plus, owns_mult;
    GrB_Monoid owns_monoid;
    GrB_Semiring owns_semiring;
    EdgeOwns owns_edge_id;
    info = GrB_BinaryOp_new(&owns_plus, (GxB_binary_function)&owns_add, owns_edge, owns_edge, owns_edge);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"owns_plus\" binop\n");
        return 1;
    }
    info = GrB_BinaryOp_new(&owns_mult, (GxB_binary_function)&owns_mul, owns_edge, owns_edge, owns_edge);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"tx_mult\" binop\n");
        return 1;
    }
    info = GrB_Monoid_new(&owns_monoid, owns_plus, (void *)&owns_edge_id);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"owns\" monoid\n");
        return 1;
    }
    info = GrB_Semiring_new(&owns_semiring, owns_monoid, owns_mult);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"tx\" semiring\n");
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
    EdgeTX edge56 = {56, 2223412.0};
    EdgeTX edge59 = {59, 6223412.0};
    EdgeTX edge67 = {67, 8913212.0};
    EdgeTX edge69 = {69, 92223412.0};
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

    // fill owns_mat
    EdgeOwns edge45 = {45};
    EdgeOwns edge36 = {36};
    EdgeOwns edge19 = {19};
    EdgeOwns edge27 = {27};
    EdgeOwns edge28 = {28};
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

    // init vetrices vectors
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
    // 1 - 4 --- users
    GrB_Vector users;
    info = GrB_Vector_new(&users, user, VERTICES_NUMBER);
    if (info != GrB_SUCCESS)
    {
        fprintf(stderr, "failed to create \"users\" vector\n");
        return 1;
    }
    User user1 = {MALE, 25};
    User user2 = {MALE, 52};
    User user3 = {FEMALE, 19};
    User user4 = {MALE, 42};
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
    // // 5 - 9 --- cards
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

    // build filters
    // GrB_Index width, height;
    // GrB_Matrix_nrows(&height, call_edges_mat);
    // GrB_Matrix_ncols(&width, call_edges_mat);

    // // all matrices are squared so let n be a dimension
    // GrB_Index n = width;

    // // vertex filter: we will take only prersons over 30 and exclude cards with `mastercard` payment system
    // GrB_Matrix ID;
    // GrB_Vector v;
    // GrB_Vector_new(&v, GrB_BOOL, n);
    // GrB_Vector_assign_BOOL(v, NULL, NULL, true, GrB_ALL, n, NULL);

    // GrB_Index size = 0;
    // GrB_Index *zeros = malloc(n * sizeof(GrB_Index));
    // // GrB_select !!!
    // for (size_t i = 0; i < 4; i++)
    // {
    //     if (users[i].age > 30)
    //     {
    //         GrB_Info e = GrB_Vector_setElement_BOOL(v, false, i);
    //     }
    // }

    // free(zeros);
    // GrB_Matrix_diag(&ID, v, 0);

    // // DEBUG
    // printf("filter matrix content: \n");
    // for (GrB_Index i = 0; i < n; i++)
    // {
    //     bool val;
    //     GrB_Info info = GrB_Matrix_extractElement_BOOL(&val, ID, i, i);
    //     if (info == GrB_SUCCESS)
    //     {
    //         printf("[%lu,%lu] = %d\n", i, i, val);
    //     }
    //     else
    //     {
    //         printf("[%lu,%lu] error\n", i, i);
    //     }
    // }

    // // apply filters

    // // verices filter
    // // фильтр только owns фильтруем с одной стороны (исходящие ребра) (поправить рисунок)
    // GrB_Matrix owns_mat_filtered;
    // // M x ID
    // GrB_mxm(owns_mat_filtered,NULL,NULL,GxB_ANY_PAIR_BOOL,call_edges_mat,ID,NULL);
    // // ID x M
    // GrB_mxm(owns_mat_filtered,NULL,NULL,GxB_ANY_PAIR_BOOL,ID,call_edges_mat,NULL); // A*
    // // в итоге получаем ребра исходящие из отобранных пользователем

    // /*--------------------------- PART 2 --------------------------*/

    // теперь нужно взять карты (редукция по строчкам или по столбцам)
    // редуцируем карты (строим вектор карты, которые относятся к отфильтрованным пользователем )
    // строим ID матрицу
    // ID с двух сторон на матрицу транзакций
    // получили подграф на нужных транзакциях
    // теперь строим матрицу для pagerank (пункт ниже). softmax. (посмотреть как можно сделать не по дебильному с помощью GB)
    /// снова редуцируем по строчкам , получаем знаменатель softmax
    /// 2
    // build matrix M'

    // run pagerank
}