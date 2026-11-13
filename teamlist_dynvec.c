#include "teamlist.h"
#include <stdlib.h>

// Implementação do TAD TeamList com VETOR DINÂMICO.

struct teamlist {
    Team **teams;      // Vetor de ponteiros para Team (Team*)
    int capacity;      // Capacidade alocada atualmente
    int size;          // Número de elementos armazenados
};

// TODO: defina aqui os campos de "struct teamlist" -- a mesma ideia do
// TeamVec do EP 09: um vetor de Team* que dobra de capacidade com realloc
// struct teamlist {
//     ...
// };
TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(struct teamlist));
    
    if (tl == NULL) return NULL;

    tl->capacity = 4;
    tl->size = 0;
    
    tl->teams = malloc(tl->capacity * sizeof(Team *));

    if (tl->teams == NULL) {
        free(tl);
        return NULL;
    }

    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    if (tl->size == tl->capacity) {

        tl->capacity = tl->capacity * 2;
        
        tl->teams = realloc(tl->teams, tl->capacity * sizeof(Team *));
    }
    
    tl->teams[tl->size] = t;

    tl->size++;
}

int tl_size(TeamList *tl) {
    if (tl == NULL) return 0;
    return tl->size;
}

Team *tl_get(TeamList *tl, int i) {
    //Verifica se o índice pedido é válido (maior ou igual a 0 e menor que o tamanho atual)
    if (tl == NULL || i < 0 || i >= tl->size) {
        return NULL;
    }
    return tl->teams[i];
}

void tl_free(TeamList *tl) {
    if (tl == NULL) return;
    
    //Liberta cada time guardado chamando a função do team.c
    for (int i = 0; i < tl->size; i++) {
        team_free(tl->teams[i]);
    }
    
    //Liberta o vetor dinâmico interno
    free(tl->teams);
    
    //Liberta a caixa principal do TAD TeamVec
    free(tl);
}
