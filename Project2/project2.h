#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



/*Constantes criadas para facilitar a leitura do codigo*/
#define BLANK " \n\t"
#define ASPAS "\""
#define BLANK_N "\n"
#define TRUE 1
#define FALSE 0

/*macros que servem de erros*/
#define COST_ERROR "negative cost or duration."
#define LINK_ERROR "link cannot be associated with bus line."
#define STOP_ERROR "no such stop."
#define CARREIRA_ERROR "no such line."
#define SORT_ERROR "incorrect sort option."
#define STOP_EXIST_ERROR "stop already exists."

/*
 * Estrutura paragem que caracteriza uma paragem
 * o seu nome e respetiva longitude e latitude
*/

typedef struct paragens{
    char* nome;
    double latitude;
    double longitude;
    int num_car;
    struct paragens* idx;
} paragens;

/*estrutura que caracteriza uma parte de ligacao contendo
so o nome de uma paragem caso seja a primeira paragem da carreira
tera custo e duracao a 0 e a paragem seguinte tera sempre o custo e 
duracao sa ligacao composta por dois elemntos do array de 
ligacoes
*/
typedef struct ligacoes{
    char* nome;
    double custo_l;
    double duracao_l;
}ligacoes;


/*estrutura de carreira com array de ligacoes dinamico*/
typedef struct carreiras{

    char* nome;
    ligacoes* stops;
    int num_par;
    double custo_c;
    double duracao_c;
    int state;
    struct carreiras* idx;

} carreiras;






/*funcoes referentes ao segundo projeto*/
void apagar_function(carreiras** car, paragens** par);


void apagar_carreira(carreiras** car, paragens** par);


void apaga_paragem(carreiras** car, paragens** par);
void apagar_primeira_ligacao(carreiras* c);
void apagar_ligacao(carreiras* c, int i);
void apagar_ultima_ligacao(carreiras* c, int i);

/*funcoes referentes ao primeiro projeto*/
int paragem_function(paragens** par);
void print_paragem(paragens** par, char str[BUFSIZ]);
void add_paragem(paragens** par, char str_lati[BUFSIZ], char str_longi[BUFSIZ], char str[BUFSIZ]);
int is_white_space(char str[BUFSIZ]);
int verificacao_par(paragens** par, char str_name[BUFSIZ]);
paragens* encontra_paragem(paragens** par, char stop[BUFSIZ]);



void carreira_function(carreiras** car);
void c_n_argumentos(carreiras** car);
void cria_carreira(carreiras** car, char str_name[BUFSIZ]);
int carreira_existe(carreiras** car, char str[BUFSIZ]);
int verificacao_inverso(char str[BUFSIZ]);
void inverse_stops(carreiras** car, char str[BUFSIZ]);
void stops_normal(carreiras** car, char str[BUFSIZ]);
carreiras *encontra_carreira(carreiras** car, char str[BUFSIZ]);



void ligacao_function(carreiras** car, paragens** par);
void ligacao_aux(carreiras** car, paragens** par, char nome_ca[BUFSIZ], char stop1[BUFSIZ], char stop2[BUFSIZ], double custo, double duracao);
int paragem_existe(paragens** par, char str[BUFSIZ]);
int verificacao_link(carreiras** car, char nome[BUFSIZ], char stop1[BUFSIZ], char stop2[BUFSIZ]);
void add_ligacao(carreiras** car, paragens** par, char name[BUFSIZ], char stop1[BUFSIZ], char stop2[BUFSIZ], double custo, double duracao);
void primeira_lig(carreiras* k, paragens* p1, paragens* p2, char stop1[BUFSIZ], char stop2[BUFSIZ], double custo, double duracao);
void add_lig_esquerda(carreiras* k, paragens* p1, char stop1[BUFSIZ], double custo, double duracao);
void add_lig_circular(carreiras* k, char stop2[BUFSIZ], double custo, double duracao);
void add_lig_direita(carreiras* k, paragens* p2, char stop2[BUFSIZ], double custo, double duracao);



void intersecao_function(carreiras** car, paragens** par);
int pertence_carreira(carreiras* c, paragens* p);
void ordenacao(char *array[], int l, int r);
void limpar_array(char **array, int acc);


#endif
