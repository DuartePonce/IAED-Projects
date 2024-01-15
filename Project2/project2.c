/* iaed-23 - ist1107489 - project2 */

/*
Duarte Ponce 107489
projeto que cria, lista e apaga
carreiras, paragens e ligacoes
*/
#include "project2.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main(){
    /*inicializacao das linked lists de carreiras e paragens*/
    paragens* paragem = NULL;
    carreiras* carreira = NULL;
    int state = 0;
    char ch;

    while (state != 1){
        ch = getchar();
        switch (ch) {
        case 'q':
            apagar_function(&carreira, &paragem);
            state = 1;
            break;
        case 'p':
            paragem_function(&paragem);
            break;
        case 'c':
            carreira_function(&carreira);
            break;
        case 'l':
            ligacao_function(&carreira, &paragem);
            break;
        case 'i':
            intersecao_function(&carreira, &paragem);
            break;
        case 'a':
            apagar_function(&carreira, &paragem);
            break;
        case 'r':
            apagar_carreira(&carreira, &paragem);
            break;
        case 'e':
            apaga_paragem(&carreira, &paragem);
            break;
        }

    }
    return 0;
}

void apagar_function(carreiras** car, paragens** par){
    /*
    esta funcao recebe as linked lists e vai percorrer 
    ambas e apagar toda a memoria alocada e informcao 
    criada ate entao
    */
    carreiras* c = *car;
    carreiras* prox_c;
    paragens* p = *par;
    paragens* prox_p;
    int i;

    while(c != NULL){
        /*ciclo que limpa a linked list de carreiras*/
        prox_c = c->idx;
        for(i = 0; i != c->num_par; i++){
            free(c->stops[i].nome);
        }
        free(c->stops);
        free(c->nome);
        free(c);
        c = prox_c;
    }
    *car = NULL;

    while(p != NULL){
        /*ciclo que limpa a linked list de paragens*/
        prox_p = p->idx;
        free(p->nome);
        free(p);
        p = prox_p;
    }
    *par = NULL;
}

void apagar_carreira(carreiras** car, paragens** par){
    /*funcao que apaga uma paragem e toda a informcao referente a ela*/
    char nome[BUFSIZ], str[BUFSIZ], *token;
    carreiras* k, *c = *car, *antes_c = NULL; 
    paragens* p = *par;
    paragens** processed;
    int i, j = 0, l = 0, state = 0;

    fgets(str, BUFSIZ, stdin);
    token = strtok(str,BLANK);
    if(token == NULL){
        return;
    }
    strcpy(nome, token);

    while(c != NULL && strcmp(nome, c->nome) != 0){
        antes_c = c;
        c = c->idx;
    }

    if (c == NULL || carreira_existe(car, nome) == FALSE) {
        printf("%s: %s\n", nome, CARREIRA_ERROR);
        return;
    }

    k = encontra_carreira(car, nome);
    processed = malloc(sizeof(paragens*) * k->num_par);

    /*ciclo que vai apagar na estrutura de paragens a componente 
    do numero de vezes que a carreira a ser apagada passa nas paragens*/
    if(k->num_par != 0){
        for(i = 0; i != k->num_par; i++){
         

            p = encontra_paragem(par, k->stops[i].nome);

            for(j = 0; j < l; j++){
                if(processed[j] == p){
                    state = 1;
                    break;
                }
            }


            if(state == FALSE){
                p->num_car--;
                processed[l] = p;
                l++;
            }
            free(k->stops[i].nome);
        }
    }
    free(processed);
    free(k->stops);
    free(k->nome);

    if (antes_c != NULL){
        antes_c->idx = c->idx;
    } else{
        *car = c->idx;
    }
 
    free(k);
}   

void apaga_paragem(carreiras** car, paragens** par){
    /*funcao que apaga uma paragem recebida*/
    char nome[BUFSIZ], str[BUFSIZ], *token;
    carreiras *c = *car; 
    paragens* p = *par, *s, *antes_p = NULL;
    int i;


    fgets(str, BUFSIZ, stdin);
    if(strchr(str,  '"')){
        strtok(str, ASPAS);
        token = strtok(NULL, ASPAS);
        strcpy(nome, token);
    } else{
        token = strtok(str,BLANK);
        strcpy(nome, token);
    }


    if (p == NULL || paragem_existe(par, nome) == FALSE) {
        printf("%s: %s\n", nome, STOP_ERROR);
        return;
    }

    s = encontra_paragem(par, nome);
    i = 0;
    while(c != NULL && s->num_car > 0){
       
        for(i = 0; i < c->num_par; i++){

            if(strcmp(nome, c->stops[i].nome) == 0 && i == (c->num_par -1)){
                apagar_ultima_ligacao(c, i);
                i--;
            }

            else if(strcmp(nome, c->stops[i].nome) == 0 && i == 0){
                apagar_primeira_ligacao(c);
                i--;
            }

            else if(strcmp(nome, c->stops[i].nome) == 0){
                apagar_ligacao(c, i);
                i--;

            }
        }
        
        c = c->idx;
    }

    while(p != NULL && strcmp(nome, p->nome) != 0){
        antes_p = p;
        p = p->idx;
    }

    if (antes_p == NULL){
        *par = p->idx;
       
    } else{
        antes_p->idx = p->idx;
    }

    free(s->nome);
    free(s);
}

void apagar_primeira_ligacao(carreiras* c){
    /*funcao que apaga a primeira ligacao*/
    int j;
    c->custo_c -= c->stops[1].custo_l;
    c->duracao_c -= c->stops[1].duracao_l;
    c->stops[1].custo_l = 0;
    c->stops[1].duracao_l = 0;

    free(c->stops[0].nome);
    
    for(j = 0; j < c->num_par - 1; j++){
        c->stops[j] = c->stops[j + 1];
    }
    c->num_par--;

    c->stops = (ligacoes*) realloc(c->stops, sizeof(ligacoes) * (c->num_par));
    
    if(c->num_par == 0){
        c->state = 0;
    }
}

void apagar_ultima_ligacao(carreiras* c, int i){
    /*funcao que apaga a ultima ligacao*/
    c->custo_c -= c->stops[i].custo_l;
    c->duracao_c -= c->stops[i].duracao_l;
    free(c->stops[i].nome);
    c->num_par--;
    c->stops = (ligacoes*) realloc(c->stops, sizeof(ligacoes) * (c->num_par));
    if(c->num_par == 0){
        c->state = 0;
    }
}

void apagar_ligacao(carreiras* c, int i){
    /*funcao que apaga todas as ligacoes 
    exceto a primeira ou a ultima*/
    int j;
    c->stops[i+1].custo_l += c->stops[i].custo_l;
    c->stops[i+1].duracao_l += c->stops[i].duracao_l;
        

    free(c->stops[i].nome);

    for(j = i; j < c->num_par - 1; j++){
        c->stops[j] = c->stops[j + 1];
    }
    c->num_par--;
    c->stops = (ligacoes*) realloc(c->stops, sizeof(ligacoes) * (c->num_par));
    if(c->num_par == 0){
        c->state = 0;
    }
}