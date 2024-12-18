#include "akinator.h"
#include "dump.h"

int main()
{
    FILE* file = fopen("akinator.txt","r");
    if (file == NULL)
    {
        printf("File error!\n");
        return -1;
    }
    NODE_T* root = read_tree(NULL, file);
    fclose(file);
    printf("%x\n", root);

    GraphicDump(root);
    printf("Enter \n 1 if you want play akinator \n 2 if you want definition \n 3 if you want different\n");

    char start_code;
    scanf("%c", &start_code);
    if (start_code == '1')
    {
        Guesss;    
    }
    else if (start_code == '2')
    {
        DEFINITION;
    }
    else if (start_code == '3')
    {
        different;
    }

    GraphicDump(root);

    FILE* file_ptr = fopen("akinator.txt", "w");
    printf_txt(root, file_ptr);

    GraphicDump(root);

    fclose(file_ptr);

    tree_destroy(root);
}


NODE_T* create_node(NODE_T* parent, char* txt)
{
    NODE_T* node = (NODE_T*) calloc(1, sizeof(NODE_T));

    strcpy(node->data, txt);
    node->parent = parent;
    node->left   = NULL;
    node->right  = NULL;

    return node;
}

NODE_T* read_tree(NODE_T* parent, FILE* file)
{
    int symbol = fgetc(file);

    if (file == NULL)
    {
        printf("File error!\n");
        return NULL;
    }

    if (symbol == '{')
    {
        char node_name[MAX_STRING_SIZE] = {};

        fscanf(file, "\"%[^\"]\"", node_name);

        NODE_T* node = create_node(parent, node_name);

        symbol = fgetc(file);

        if (symbol == '}')
        {
            while (symbol != '{' && symbol != EOF) symbol = fgetc(file);
            fseek(file, -1, SEEK_CUR);

            return node;
        }

        while (symbol != '{' && symbol != EOF) symbol = fgetc(file);
        fseek(file, -1, SEEK_CUR);
    
        node->left  = read_tree(node, file);
        node->right = read_tree(node, file);

        return node;
    }

    return NULL;

}

int Guess(NODE_T* node)
{
    if (!node)
    {
        fprintf(stderr, "Error: null-pointer cannot be used as a node!\n");
        return -1;
    }

    printf("%s ?\n", node->data);

    char answer[MAX_STRING_SIZE] = {};

    scanf("%s", answer);

    if (strcmp(answer, "yes") == 0)
    {
        if (node->left == NULL)
        {
            printf("eeeee!\n\n");
            return 0;
        }

        return Guess(node->left);
    }

    if (strcmp(answer, "no") == 0)
    {
        if (node->right == NULL)
        {
            new_node_tree(node);
            return 0;
        }
        return Guess(node->right);
    }

    printf("Wrong answer: %s!\n", answer);
    return Guess(node);
}

int search_word(NODE_T* node, char word[MAX_STRING_SIZE], DEFINITION_T* definition)
{
    if (node == NULL)
    {
        return 1;
    }
    if (strcmp(node->data, word) == 0 && node->left == NULL && node->right == NULL)
    {
        definition->addr[definition->node_count] = node;
        definition->node_count++;
        //printf("in if");
        return 0;
    }
    else if (strcmp(node->data, word) != 0 && node->left == NULL && node->right == NULL)
    {
        return 1;
    }

    
    if (search_word(node->left, word, definition) == 0)
    {
       
        definition->addr[definition->node_count] = node;
        definition->node_count++;
        return 0;
    }
    if (search_word(node->right, word, definition) == 0)
    {
        definition->addr[definition->node_count] = node;
        definition->node_count++;
        return 0;
    }

    return 1;

}

void print_defenition(NODE_T* node, DEFINITION_T* definition)
{
    printf("WORD:\n");
    char word[MAX_STRING_SIZE];
    scanf("%s", &word);

    definition->node_count = 0;
    int result = search_word(node, word, definition);


    if (result != 0)
    {
        printf("this word no in the akinator\n");
    };

    for (int i = definition->node_count - 1; i > 0; i--)
    {
       
        if (i != 0 && definition->addr[i]->right == definition->addr[i - 1])
        {
            printf("no ");
        }   
        printf("%s ", definition->addr[i]->data);
    }
    printf("%d\n", definition->node_count);
}

void different_definition(NODE_T* root)
{
    DEFINITION_T* definition_one = (DEFINITION_T*) calloc(1, sizeof(DEFINITION_T));
    DEFINITION_T* definition_two = (DEFINITION_T*) calloc(1, sizeof(DEFINITION_T));

    printf("WORD_ONE:\n");
    char word_one[MAX_STRING_SIZE];
    scanf("%s", &word_one);

    printf("WORD_TWO:\n");
    char word_two[MAX_STRING_SIZE];
    scanf("%s", &word_two);

    search_word(root, word_one, definition_one);
    search_word(root, word_two, definition_two);

    int i_one = definition_one->node_count - 1;
    int i_two = definition_two->node_count - 1;


    printf("Same: ");


    while (definition_one->addr[i_one - 1] == definition_two->addr[i_two - 1])
    {
        printf("%s ",definition_one->addr[i_one]->data);  
        i_one--;
        i_two--;
    }

    if (i_one == 0 || i_two == 0)
    {
        printf("\nYou entered same words!");
    }
    else
    {
        printf("\nDifferent: %s", definition_one->addr[i_one]->data);
    }
} 

int new_node_tree(NODE_T* parent)
{
    printf("Please enter question\n");
    char question[MAX_STRING_SIZE] = {};
    scanf("%s", &question);
    parent->parent->right = create_node(parent, question);

    char answer[MAX_STRING_SIZE] = {};
    printf("Enter your answer\n");
    scanf("%s", &answer);

    if (strcmp(question, answer) == 0) return 0;
    parent->parent->right->left = create_node(parent->parent->left->left, answer);

    parent->parent->right->right = parent;
    
    return 1;
}

void printf_txt(NODE_T* node, FILE* rewrite)
{
    if(node == NULL)
    {
        return;
    }

    fprintf(rewrite, "{\"%s\"", node->data);

    printf_txt(node->left, rewrite);
    printf_txt(node->right, rewrite);

    fprintf(rewrite, "}");
}

void tree_destroy(NODE_T* node)
{
    tree_destroy(node->left);
    tree_destroy(node->right);
    free(node);
}