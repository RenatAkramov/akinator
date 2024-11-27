#include "Dump.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int GraphicDump(NODE_T* node)
{
    FILE* dump = fopen("Dump.dot", "w");

    if(dump == NULL)
    {
        printf("cannot open file\n");
        return -1;
    }

    fprintf(dump, "digraph G\n{\n rankdir = UD\nbgcolor = \"aquamarine3\"\n");

    Draw(node, dump);

    fprintf(dump, "}\n");

    fclose(dump);

    system("dot Dump.dot -Tpng -o Dump.png");

    return 0;
}

int Draw(NODE_T* node, FILE* dump)
{
    assert(dump);

    fprintf(dump, "\"%s\" [shape = Mrecord, style = \"filled\", fillcolor = \"darkslateblue\","
            " label = \"{%s | addr = %p | left = %p | right = %p | parent = %p}\"];\n",
                node->data, node->data, node, node->left, node->right, node->parent);

    if(node->left != NULL)
    {
        Draw(node->left,  dump);
        fprintf(dump, " edge[color = \"darkgreen\", label = \"yes\"];\n");
        fprintf(dump, "\"%s\" -> \"%s\";", node->data, node->left->data);
    }

    if(node->right != NULL)
    {
        Draw(node->right, dump);
        fprintf(dump, " edge[color = \"firebrick4\", label = \"no\"];\n");
        fprintf(dump, "\"%s\" -> \"%s\";\n", node->data, node->right->data);
    }

    return 0;
}