#include "teamlist.h"
#include <stdlib.h>

// Implementação do TAD TeamList com LISTA DUPLAMENTE ENCADEADA.

typedef struct node Node;

struct node
{
    Team *team;//O dado guardado neste nó
    Node *next;//Ponteiro para o próximo nó
    Node *prev;//Ponteiro para o nó anterior
};


struct teamlist {
    Node *head;//Primeiro nó da lista
    Node *tail;//Último nó da lista
    int size;  //Quantidade atual de elementos
};

TeamList *tl_create(void) {
    //Aloca exatamente o tamanho necessário para a caixa da lista
    TeamList *tl = malloc(sizeof(struct teamlist));
    
    if (tl == NULL) {
        return NULL;
    }

    //Define o estado inicial da lista vazia
    tl->head = NULL;
    tl->tail = NULL;
    tl->size = 0;

    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    // Cria a caixinha na memória
    Node *novo_no = malloc(sizeof(struct node));

    // Se faltar memória no PC, aborta
    if (novo_no == NULL) return; 

    // Guarda o time lá dentro
    novo_no->team = t;

    // Aponta as setas para o vazio
    novo_no->next = NULL;
    novo_no->prev = NULL;

    if (tl->size == 0) {
    tl->head = novo_no;
    tl->tail = novo_no;
    }
    else {
        // 1. A atual última carruagem aponta para a frente
        tl->tail->next = novo_no;

        // 2. O novo nó aponta para trás
        novo_no->prev = tl->tail;

        // 3. A estação atualiza o painel
        tl->tail = novo_no;
    }

    // Independentemente de a lista estar vazia ou não, o tamanho aumenta
    tl->size++;
}

int tl_size(TeamList *tl) {
    if (tl == NULL) return 0;
    
    return tl->size;
}

Team *tl_get(TeamList *tl, int i) {
    if (tl == NULL || i < 0 || i >= tl->size) {
        return NULL;
    }

    Node *temp = tl->head;
    for (int j = 0; j < i; j++) {
        temp = temp->next;
    }

    return temp->team;
}

void tl_free(TeamList *tl) {
    if (tl == NULL) return;

    Node *temp = tl->head;
    
    for (int j = 0; j < tl->size; j++) {
        Node *proximo = temp->next;
        
        free(temp);                 
        
        temp = proximo;
    }

    free(tl);
}