#include "team.h"
#include "teamlist.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    TeamList *tl = tl_create();

    //Abrir o arquivo no modo de leitura
    FILE *arquivo = fopen("teams.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo teams.csv\n");
        tl_free(tl);
        return 1;
    }

    int id;
    char nome[100]; //Buffer temporário para guardar o nome lido

    //Lê linha por linha até o fim do arquivo (EOF)
    while (fscanf(arquivo, "%d,%99[^\n]", &id, nome) == 2) {
        //Fabrica o time com as informações extraídas da linha
        Team *t = team_create(id, nome);
        
        //Engata o time no final do nosso trem
        tl_append(tl, t);
    }
    
    //Fecha o arquivo, pois já carregamos tudo para a memória
    fclose(arquivo);

    //Imprime o cabeçalho da tabela exatamente como no exemplo
    printf("%-3s %-16s %-3s %-3s %-3s %-3s %-3s %-3s %-3s\n", 
           "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");

    //Caminha pela lista extraindo as informações de cada time
    int quantidade = tl_size(tl);
    for (int i = 0; i < quantidade; i++) {
        Team *t = tl_get(tl, i);

        //Coleta as estatísticas usando as funções de acesso (getters)
        int id_time = team_id(t);
        const char *nome_time = team_name(t);
        int v = team_wins(t);
        int e = team_draws(t);
        int d = team_losses(t);
        int gm = team_goals_scored(t);
        int gs = team_goals_conceded(t);

        //Calcula Saldo e Pontos Ganhos
        int saldo = gm - gs;
        int pontos = (v * 3) + (e * 1);

        //Imprime a linha do time com o mesmo alinhamento do cabeçalho
        printf("%-3d %-16s %-3d %-3d %-3d %-3d %-3d %-3d %-3d\n", 
               id_time, nome_time, v, e, d, gm, gs, saldo, pontos);
    }

    //Destrói o trem para liberar a memória
    tl_free(tl);
    
    return 0;
}