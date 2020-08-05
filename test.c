/*
 * Test code for the 2-3-4 tree. This code maintains an alternative
 * representation of the data in the tree, in an array (using the
 * obvious and slow insert and delete functions). After each tree
 * operation, the verify() function is called, which ensures all
 * the tree properties are preserved:
 *  - node->child->parent always equals node
 *  - tree->root->parent always equals NULL
 *  - number of kids == 0 or number of elements + 1;
 *  - tree has the same depth everywhere
 *  - every node has at least one element
 *  - subtree element counts are accurate
 *  - any NULL kid pointer is accompanied by a zero count
 *  - in a sorted tree: ordering property between elements of a
 *    node and elements of its children is preserved
 * and also ensures the list represented by the tree is the same
 * list it should be. (This last check also doubly verifies the
 * ordering properties, because the `same list it should be' is by
 * definition correctly ordered. It also ensures all nodes are
 * distinct, because the enum functions would get caught in a loop
 * if not.)
 */

#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "tree234.h"

#define ARRAY_SIZE(x)   (sizeof(x) / sizeof(x[0]))
#define NSTR            ARRAY_SIZE(strings)

static int n_errors = 0;

void error(char *fmt, ...)
{
    va_list ap;
    printf("ERROR: ");
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    va_end(ap);
    printf("\n");
    fflush(stdout);
    n_errors++;
}

int randomnumber(unsigned *seed)
{
    *seed *= 1103515245;
    *seed += 12345;
    return ((*seed) / 65536) % 32768;
}

int mycmp(void *av, void *bv)
{
    char const *a = (char const *) av;
    char const *b = (char const *) bv;
    return strcmp(a, b);
}

char *strings[] = {
    "a", "ab", "absque", "coram", "de",
    "palam", "clam", "cum", "ex", "e",
    "sine", "tenus", "pro", "prae",
    "banana", "carrot", "cabbage", "broccoli", "onion", "zebra",
    "penguin", "blancmange", "pangolin", "whale", "hedgehog",
    "giraffe", "peanut", "bungee", "foo", "bar", "baz", "quux",
    "murfl", "spoo", "breen", "flarn", "octothorpe",
    "snail", "tiger", "elephant", "octopus", "warthog", "armadillo",
    "aardvark", "wyvern", "dragon", "elf", "dwarf", "orc", "goblin",
    "pixie", "basilisk", "warg", "ape", "lizard", "newt", "shopkeeper",
    "wand", "ring", "amulet"
};

int main(void)
{
    tree234 *tree;
    int i, pos;
    unsigned int seed;
    char *string;
    search234_state state;

    seed = time(NULL);
    tree = newtree234(mycmp);
    if (tree == NULL) {
        return -1;
    }

    for (i = 0; i < NSTR; ++i) {
        pos = ((unsigned)randomnumber(&seed)) % NSTR;
        if (add234(tree, strings[pos]) == NULL) {
            error("failed to insert node to tree, node[%d, %s]", i, strings[pos]);
        }
    }
    printf("tree-234 has %d item\n", count234(tree));
    puts("====    findrel234   ====");
    for (string = NULL; (string = findrel234(tree, string, NULL, REL234_GT)) != NULL;) {
        printf("findrel234 - string: %s\n", string);
    }
    puts("==== search tree-234 ====");
    for (search234_start(&state, tree); state.element != NULL; search234_step(&state, -1)) {
        i = state.index;
        string = state.element;
        printf("order: %3d, string: %s\n", i, string);
    }
    freetree234(tree);
    printf("errors count %d\n", n_errors);

    return (n_errors != 0);
}
