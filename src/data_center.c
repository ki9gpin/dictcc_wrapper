#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "data_center.h"

// vocab node struct
struct vn {
    vocab_data* vocab;
    struct vn* next;
};
typedef struct vn vocab_node;

// voclst node struct
struct ln {
    voclst_data* voclst;
    struct ln* next;
};
typedef struct ln voclst_node;

// vacab linked list
vocab_node *init_vnode = NULL;
vocab_node *final_vnode = NULL;

// vaclst linked list
voclst_node *init_lnode = NULL;
voclst_node *final_lnode = NULL;

// public methods - vocabs

bool vocab_add (const vocab_data *data) {

    // query existence
    if (vocab_exists(data->id)) return false;

    // create new data
    vocab_data* pvocab = (vocab_data*)malloc(sizeof(vocab_data));
    pvocab->nr = data->nr;
    pvocab->id = data->id;
    strcpy(pvocab->vl, data->vl);
    strcpy(pvocab->vr, data->vr);
    pvocab->is_marked = false;

    // create new node
    vocab_node* pnewnode = (vocab_node*)malloc(sizeof(vocab_node));
    pnewnode->next = NULL;
    pnewnode->vocab = pvocab;

    if (init_vnode == NULL) {
        init_vnode = pnewnode;
        final_vnode = init_vnode;
    } else {
        final_vnode->next = pnewnode;
        final_vnode = pnewnode;
    }
    return true;
}

vocab_data* vocab_for_nr (int nr) {
    vocab_node* node = init_vnode;
    while(node != NULL) {
        if (node->vocab->nr == nr) return node->vocab;
        node = node->next;
    }
    return NULL;;
}

void vocab_clean_up (void) {
    vocab_node* node = init_vnode;
    vocab_node* node_next = NULL;

    while (node != NULL) {
        node_next = node->next;
        free(node->vocab);
        free(node);
        node = node_next; 
    }
}

void vocab_print_all (void) {
    vocab_node* node = init_vnode;
    while (node != NULL) {
       printf("%d %d %s %s\n",\
            node->vocab->nr,\
            node->vocab->id,\
            node->vocab->vl,\
            node->vocab->vr);
        node = node->next;
    }
}

// public methods - voclists

bool voclst_add (const voclst_data *data) {

    // query existenc
    if (voclst_exists(data->id)) return false;

    // create new data
    voclst_data* pvoclst = (voclst_data*)malloc(sizeof(voclst_data));
    pvoclst->nr = data->nr;
    pvoclst->id = data->id;
    strcpy(pvoclst->name, data->name);
    pvoclst->is_marked = false;

    // create new node
    voclst_node* pnewnode = (voclst_node*)malloc(sizeof(voclst_node));
    pnewnode->next = NULL;
    pnewnode->voclst = pvoclst;

    if (init_lnode == NULL) {
        init_lnode = pnewnode;
        final_lnode = init_lnode;
    } else {
        final_lnode->next = pnewnode;
        final_lnode = pnewnode;
    }
    return true;
}

voclst_data* voclst_for_nr (int nr) {
    voclst_node* node = init_lnode;
    while(node != NULL) {
        if (node->voclst->nr == nr) return node->voclst;
        node = node->next;
    }
    return NULL;;
}

void voclst_clean_up (void) {
    voclst_node* node = init_lnode;
    voclst_node* node_next = NULL;

    while (node != NULL) {
        node_next = node->next;
        free(node->voclst);
        free(node);
        node = node_next; 
    }
}

void voclst_print_all (void) {
    voclst_node* node = init_lnode;
    while (node != NULL) {
       printf("%d %d %s\n",\
            node->voclst->nr,\
            node->voclst->id,\
            node->voclst->name);
        node = node->next;
    }
}

// private methods

bool vocab_exists (int id) {
    vocab_node *node = init_vnode;
    while (node != NULL) {
        if (node->vocab->id == id) return true;
        node = node->next;
    }
    return false;
}

bool voclst_exists (int id) {
    voclst_node *node = init_lnode;
    while (node != NULL) {
        if (node->voclst->id == id) return true;
        node = node->next;
    }
    return false;
}
