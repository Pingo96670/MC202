#define MAX_CITY_LEN 15

// Int coordinates struct
typedef struct coordinates {
    int x;
    int y;
} coords;

// Float coordinates struct
typedef struct float_coordinates {
    float x;
    float y;
} float_coords;

// Node struct for quaternary tree
enum node_category {internal_node, free_leaf, occupied_leaf};
typedef struct node_type *node;
struct node_type {
    float_coords centre;
    node parent;
    enum node_category category;
    union {
        struct {node north_west; node north_east; node south_west; node south_east;};       // Internal node
        struct {char city_name[MAX_CITY_LEN]; coords city_coords;};         // Occupied leaf
    };
};


// Function to calculate distance between two points A and B
// Returns a float
float distance(int A_x, int A_y, int B_x, int B_y);

// Function to allocate memory to and initialize a free leaf node with given centre coordinates
// Returns the initialized node
node initialize_node(node node, float centre_x, float centre_y);

// Recursive function to free a quaternary tree
void free_tree(node root);

// Recursive function to insert a new city with given (x,y) coordinates
// Alters the tree directly
void insert_city(node root, char city_name[MAX_CITY_LEN], int x, int y, float_coords centre, node parent_node);

// Recursive function to search for a node in given (x,y) coordinates
// Returns the found node
node search_for_point(node node, int search_x, int search_y);

// Recursive function to print the names of all cities inside a given radius from a point
void search_in_region(node node, int circle_x, int circle_y, int radius);

// Function to check if a node can be collapsed
// Returns a value of 0 or 1 as boolean
int branch_collapse_check(node node);

// Recursive function to collapse a branch if possible
// Alters the tree directly
void collapse_branch(node node);

// Function to remove a city from the given (x,y) coordinates
// Alters the tree directly
void remove_from_point(node node_to_remove, int x, int y);