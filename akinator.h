#ifndef AKINATOR_
#define AKINATOR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

enum answer
{
    YES             = 1,
    NO              = 2,
    MAX_STRING_SIZE = 50,
    MAX_LEN_DEREVO  = 200,
};

struct NODE_T
{
    char    data[MAX_STRING_SIZE];
    NODE_T* left;
    NODE_T* right;
    NODE_T* parent;
    int left_or_right;
};

struct DEFINITION_T
{
    NODE_T* addr[MAX_LEN_DEREVO];
    int node_count = 0;
};

int Guess(NODE_T* node);

NODE_T* read_tree(NODE_T* parent, FILE* file);

NODE_T* create_node(NODE_T* parent, char* txt);

void print_defenition(NODE_T* node, DEFINITION_T* defenition);

int search_word(NODE_T* node, char word[MAX_STRING_SIZE], DEFINITION_T* defenition);

void different_definition(NODE_T* root);

int draw_tree(NODE_T* parent);

void printf_txt(NODE_T* node);

#endif