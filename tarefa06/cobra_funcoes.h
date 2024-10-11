// Struct do tabuleiro, contendo dimensões e uma matriz com os caracteres de cada célula
typedef struct board {
    char **data;
    int size_x;
    int size_y;
} board;

// Struct de posição (x, y)
typedef struct pos {
    int x;
    int y;
} pos;

// Struct de um nó para a lista duplamente ligada
typedef struct node_type *node;
struct node_type {
    pos position;
    int is_head;
    node previous;
    node next;
};

// Função para a operação módulo
// Retorna a mod b
int mod(int a, int b);

// Função para criar uma matriz i×j, atribuindo o char '_'  a todas as células
// Retorna uma matriz i×j de char '_'
char **create_matrix(int i, int j);

// Função para criar um nó relacionado à cabeça da cobra na posição (head_x, head_y)
// Retorna o nó head
node create_head(int head_x, int head_y);

// Função para criar a fruta na posição (head_x, head_y)
// Retorna a pos fruit
pos create_fruit(int fruit_x, int fruit_y);

// Função utilizada ao comer uma fruta
void eat_fruit(node head, int move_x, int move_y, board board);

// Função para mover a cobra e checar se come uma fruta
void move(node head, int move_x, int move_y, pos fruit, int *n_eaten, board board);

// Função para checar se a cobra colide com seu corpo
// Retorna 0 ou 1 para falso ou verdadeiro, respectivamente
int self_collision_check(node head, int move_x, int move_y, board board);

// Função para imprimir o tabuleiro
void print_board(board board);

// Função para liberar a memória alocada à cobra e ao tabuleiro
void free_game(node head, board board);