#ifndef MAIN_H
#define MAIN_H

/*Tamanho maximo de cada tipo de estrutura*/
#define MAX_CA 200
#define MAX_PA 10000
#define MAX_LI 30000

/*tamanho maximo de nomes de carreiras e paragens*/
#define MAX_NAME_CA 50
#define MAX_NAME_PA 20

/*Constantes criadas para facilitar a leitura do codigo*/
#define BLANK " \n\t"
#define ASPAS "\""
#define BLANK_N "\n"
#define TRUE 1
#define FALSE 0

/*
 * Estrutura paragem que caracteriza uma paragem
 * o seu nome e respetiva longitude e latitude
 */
typedef struct {

    char name[MAX_NAME_CA + 1];
    double latitude;
    double longitude;
    int numero_car;

} paragem;

/*
 * Estrutura carreira que caracteriza o seu nome
 * paragem inical e final
 */
typedef struct {

    char name[MAX_NAME_PA + 1];
    paragem stops[MAX_CA];
    int num_stops;
    double custo_c;
    double duracao_c;
    /*existencia de ligacao*/
    int state;

} carreira;


#endif