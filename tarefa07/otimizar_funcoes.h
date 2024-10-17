// Struct de um nó para a árvore
typedef struct node_type *node;
struct node_type {
    char data;
    node left;
    node right;
    int is_negative;
};


// Função para liberar uma árvore binária
void free_tree(node root);


// Função para ler uma expressão e armazená-la como árvore binária
// Retorna a raiz da árvore principal
node read_expression(char expression[], int *reading_pos, int is_negative);


// Função suporte para inverter o atributo is_negative de um nó
// Altera o atributo diretamente
void invert_negative(int *is_negative);


// Função para aplicar o Teorema de De Morgan sobre uma árvore
// Altera a árvore diretamente
void de_morgan(node root);


// Checa se o dado de um nós é um operador ("&" ou "|")
// Retorna um valor inteiro como booleano
int is_operator(node node);


// Função para checar se duas expressões são equivalentes
// Retorna um valor inteiro como booleano
int is_equivalent(node root_expression1, node root_expression2);


// Função para simplificar uma expressão, percorrendo a árvore em pós-ordem
// Altera a árvore diretamente
void simplify_expression(node root);


// Função para imprimir uma expressão a partir de uma árvore
void print_tree(node root);