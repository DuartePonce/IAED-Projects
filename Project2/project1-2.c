/* iaed-23 - ist1107489 - project2 */

#include "project2.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int paragem_function(paragens** par){
    /*
    * Funcao chamada quando p  
    * e escrito na linha de comandos
    */
	char string[BUFSIZ], str_lati[BUFSIZ], str_longi[BUFSIZ], str_name[BUFSIZ];
    char *token;
    paragens* p = *par;
    fgets(string, BUFSIZ, stdin);

   /*
    * verificacao do input a seguir ao comando p
    * impressao de todas as paragens da linked list de paragens
    */
	if(is_white_space(string)==TRUE || strcmp(string, BLANK_N)==FALSE){
        if(p != NULL){
            while(p->idx != NULL){
                printf("%s: %16.12f %16.12f %d\n", p->nome, p->latitude, p->longitude, p->num_car);
                p = p->idx;
            }
            printf("%s: %16.12f %16.12f %d\n", p->nome, p->latitude, 
                p->longitude, p->num_car);
        }
		return 0;
	}
    

	if(strchr(string,'"')){
		strtok(string, ASPAS);
		token = strtok(NULL, ASPAS);
		strcpy(str_name,token);
	}
	else{
		token = strtok(string, BLANK);
    	strcpy(str_name,token);
	}
	token = strtok(NULL, BLANK);
  
    

	if(token == NULL){
		print_paragem(par, str_name);
		return 0;
	}
	else{
		strcpy(str_lati, token);
		token = strtok(NULL, BLANK);
		strcpy(str_longi, token);       
		add_paragem(par, str_lati, str_longi, str_name);
	}

	return 0;
}
int is_white_space(char str[BUFSIZ]){
    /*funcao que verifica se depois do comando existe ou nao input*/
    int i;
    for(i=0;i<BUFSIZ;i++){
        if(str[i]=='\0'){
            return 1;
        }
        else if(!isspace(str[i])){
       
            return 0;
        }
    }
    return 1;
}
void add_paragem(paragens** par, char str_lati[BUFSIZ], char str_longi[BUFSIZ], char str_name[BUFSIZ]){
    /*funcao que cria e adiciona uma paragem a linked list de paragens
    alocando memoria para a estrutura e nome da paragem*/
    paragens* p = *par;
    paragens* nova_p = (paragens*) malloc(sizeof(paragens));

    if(nova_p == NULL){
        exit(1);
    }

    nova_p->nome = (char*) malloc(sizeof(char)*(strlen(str_name)+1));
    strcpy(nova_p->nome,str_name);
    nova_p->latitude = atof(str_lati);
    nova_p->longitude = atof(str_longi);
    nova_p->num_car = 0;
    nova_p->idx = NULL;

    if(*par == NULL){
        *par = nova_p;
    }
    else if(verificacao_par(par, str_name)==TRUE){
        while(p->idx != NULL){
            p = p->idx;
        }
        p->idx = nova_p;
    }
    else{
        free(nova_p);
    }
        
}
int verificacao_par(paragens** par, char nome[BUFSIZ]){
    /*funcao que verifica se a paragem com o nome dado de input existe ou nao*/
    paragens* p = *par;
    if(p != NULL){
        while(p != NULL){
            if(strcmp(p->nome, nome)==0){
                printf("%s: %s\n", nome, STOP_EXIST_ERROR);
                return 0;
            }
            p = p->idx;
        }
    }
    return 1;
}
void print_paragem(paragens** par, char str[BUFSIZ]){
    /*funcao que verifica e caso exista imprime a paragem dada no input*/
    paragens* p = *par;

    if(paragem_existe(par, str) == FALSE){
        printf("%s: %s\n", str, STOP_ERROR);
        return;
    }

    p = encontra_paragem(par, str);
    printf("%16.12f %16.12f\n", p->latitude, p->longitude);

}

void carreira_function(carreiras** car){
    /*
    Funcao chamada quando c  
    e escrito na linha de comandos
    */
    char string[BUFSIZ], inverso[BUFSIZ], nome[BUFSIZ];
    char *token;
    /*printf("2\n");*/
    fgets(string, BUFSIZ, stdin);
    /*Verificacao se o input a seguir ao comando existe ou nao*/
    if(is_white_space(string)!=0){
        
        c_n_argumentos(car);
        return;
    }
    token = strtok(string, BLANK);
    strcpy(nome,token);
    /*
     * verificacao se a carreira existe ou nao
     * primeira opacao cria um carreira nova
     * segunda opcao lista por odem de criacao
     * ou ao contrario
    */
    if(carreira_existe(car, nome) == 0){
        cria_carreira(car, nome);
        return;
    } else{

        token = strtok(NULL, BLANK);
        if(token != NULL){   
            strcpy(inverso,token);
            /*verificacaodo inverso*/
            if(verificacao_inverso(inverso) == TRUE){
                inverse_stops(car, nome);
            }
            else{
                printf("%s\n", SORT_ERROR);
            }
        }
        else{
            stops_normal(car, nome);
        }    
    }
}
void c_n_argumentos(carreiras** car){
    /*
     * Funcao que que da printf de todas as carreiras criadas e sua respetiva informacao
     * imprimindo o nome da carreira, o nome da paragem de origem e de destino, 
     * o numero total de paragens da carreira, custo e duracao
    */
    carreiras* c = *car;
    
    while(c != NULL){
        if(c->state==1){
            printf("%s %s %s %d %.2f %.2f\n", c->nome, c->stops[0].nome, 
            c->stops[c->num_par-1].nome, c->num_par, c->custo_c,
            c->duracao_c);
        }
        else{
            printf("%s %d %.2f %.2f\n", c->nome, c->num_par, c->custo_c,
            c->duracao_c);
        }
        c = c->idx;
    }
}
void cria_carreira(carreiras** car, char nome[BUFSIZ]){
    /*funcao que cria uma carreira nova e
    aloca a memoria necessaria na linked list
    para a estrutura e nome da carreira*/
    carreiras* c =  *car;
    carreiras* nova_carreira = (carreiras*) malloc(sizeof(carreiras));
    if(nova_carreira == NULL){
        exit(1);
    }
    nova_carreira->nome = (char*) malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(nova_carreira->nome,nome);
    nova_carreira->stops = NULL;
    nova_carreira->num_par = 0;
    nova_carreira->custo_c = 0;
    nova_carreira->duracao_c = 0;
    nova_carreira->state = 0;
    nova_carreira->idx = NULL;

    if(*car == NULL){
        *car = nova_carreira;
        return;
    } else{
        while(c->idx != NULL){
            c = c->idx;
        }
        c->idx = nova_carreira;
    }
}
int carreira_existe(carreiras** car, char nome[BUFSIZ]){
    /*funcao que verifica se existe ou uma carreira com o nome como input*/
    carreiras* c = *car;
    if(c == NULL){
        return 0;
    } else {
        while(c != NULL){
            if(strcmp(nome, c->nome)==0){
                return 1;
            }
            c = c-> idx;
        }
    }
    return 0;
}
int verificacao_inverso(char str[BUFSIZ]){
    /*
     * verificacao se o input a seguir ao nome da carreira
     * e uma abreviatura de inverso
    */
    if((strcmp("inverso",str)==0||strcmp("invers",str)==0||
        strcmp("inver",str)==0||strcmp("inve",str)==0||strcmp("inv",str)==0)){
        return 1;
    }
    return 0;
}
void stops_normal(carreiras** car, char nome[BUFSIZ]){
    /*impressao das paragens da carreira por odem de criacao*/
    int i;
    carreiras* c = encontra_carreira(car, nome);
    if(c->num_par != 0){
        for(i=0; i < (c->num_par)-1; i++){
            printf("%s, ", c->stops[i].nome);
        }
        printf("%s\n", c->stops[(c->num_par)-1].nome);
        
    }
    
}
void inverse_stops(carreiras** car, char str[BUFSIZ]){
    /*Impressao das paragens por ordem inversa*/
    int i;
    carreiras* c = encontra_carreira(car, str);
    if(c->num_par != 0){
        for(i = (c->num_par)-1; i > 0; i--){
            printf("%s, ", c->stops[i].nome);
        }
        printf("%s\n", c->stops[0].nome);
    }
}
carreiras* encontra_carreira(carreiras** car, char nome[BUFSIZ]){
    /*Procura o endereco numa linked list de uma carreira*/
    carreiras* c = *car;
    while(c != NULL){
        if(strcmp(nome, c->nome)==0){
            return c;
        }
        c = c->idx;
    }
    return NULL;
}   


void ligacao_function(carreiras** car, paragens** par){
    /*
     * Esta funcao tem como objetivo tratar e organizar o input dado no stdin 
     * e depois envia-lo para a sua auxiliar
     */
	char *token;
    char nome_ca[BUFSIZ], stop1[BUFSIZ], stop2[BUFSIZ];
    char string[BUFSIZ];
	int len=0,state=0;
    double custo, duracao;
    fgets(string, BUFSIZ, stdin);

    
    token=strtok(string,BLANK);
    strcpy(nome_ca, token);
    len = strlen(nome_ca)+2;

	/*Verificacao se a carreira existe ou nao*/
    if(carreira_existe(car, nome_ca)==FALSE){
        printf("%s: %s\n", nome_ca, CARREIRA_ERROR);
        return;
    }
    /*verificacao da existencia de aspas na primeira paragem do input*/
	if(string[len]=='"'){  
        token=strtok(NULL,ASPAS);
        strcpy(stop1, token);
        len += strlen(token)+3;
        state=TRUE;
	}
	else{
		token=strtok(NULL,BLANK);
        strcpy(stop1, token);
        len += strlen(token)+1;
        state=FALSE;
	}
    /*verificacao da existencia de aspas na segunda paragem do input*/   
	if(string[len]=='"'){
        if(state==1){
            strtok(NULL,ASPAS);
        }  
        token=strtok(NULL,ASPAS);
        strcpy(stop2, token);
	}
	else{
		token=strtok(NULL,BLANK);
        strcpy(stop2, token); 
	}
	token=strtok(NULL,BLANK);
	custo = atof(token);
	token=strtok(NULL,BLANK);
	duracao=atof(token);
    ligacao_aux(car, par, nome_ca, stop1, stop2, custo, duracao);
}
void ligacao_aux(carreiras** car, paragens** par, char nome_ca[BUFSIZ], char stop1[BUFSIZ], char stop2[BUFSIZ], double custo, double duracao){
    /*Verificacao se as duas paragens dadas existem*/
    if(paragem_existe(par, stop1) == TRUE && paragem_existe(par, stop2) == TRUE){
        /*verificacao se as e possivel establecer a ligacao*/
		if(verificacao_link(car, nome_ca, stop1, stop2) == TRUE){
            /*Verificacao se e possivel o custo e duracao sao maiores ou iguais a 0*/
			if(custo >= 0 && duracao >= 0){
                /*funcao que adiciona a ligacao*/
				add_ligacao(car, par, nome_ca, stop1, stop2, custo, duracao);
			}
			else{
				printf("%s\n", COST_ERROR);
			}
		}
		else{
			printf("%s\n", LINK_ERROR);
		}
	}
	else if(paragem_existe(par, stop1) == FALSE){
       printf("%s: %s\n", stop1, STOP_ERROR);
	}
	else{
		printf("%s: %s\n", stop2, STOP_ERROR);
	}
}
int paragem_existe(paragens** par, char nome[BUFSIZ]){
    /*funcao que verifica se a paragem existe*/
    paragens* p = *par;
    while(p != NULL){
        if(strcmp(nome, p->nome)==0){
            return 1;
        }
        p = p->idx;
    }
    return 0;
}
int verificacao_link(carreiras** car, char nome[BUFSIZ], char stop1[BUFSIZ], char stop2[BUFSIZ]){
    /*Verificacao se a ligacao e possivel establecer*/
    carreiras* c = *car;
    while(c != NULL){
        if(strcmp(nome, c->nome)==0){
            if(c->state==0 || 
               strcmp(stop1, c->stops[(c->num_par)-1].nome)==0 || 
               strcmp(stop2, c->stops[0].nome)==0){
                return 1;
            }
        }
        c = c->idx;
    }
    return 0;
}
void add_ligacao(carreiras** car, paragens** par, char name[BUFSIZ], char stop1[BUFSIZ], char stop2[BUFSIZ], double custo, double duracao){
    /*Funcao que cria a ligacao*/
    carreiras* k = encontra_carreira(car, name); 
    paragens *p1 = encontra_paragem(par, stop1), *p2 = encontra_paragem(par, stop2);

    if(p1 == NULL || p2 == NULL || k == NULL){
        return;
    }

    /*condicao para se adicionar uma nova paragem de origem*/
    if(k->state == FALSE){
        primeira_lig(k, p1, p2, stop1, stop2, custo, duracao);
    }
   
    else if(strcmp(k->stops[0].nome, p2->nome)==0 &&
    strcmp(k->stops[k->num_par-1].nome, p1->nome)!=0){  
        add_lig_esquerda(k, p1, stop1, custo, duracao);
    }

    /*condicao para adicionar e criar uma carreira circular*/
    else if(strcmp(k->stops[0].nome, p2->nome)==0){
        add_lig_circular(k, stop2, custo, duracao);
    }           

    else{
        add_lig_direita(k, p2, stop2, custo, duracao);
    }

    k->custo_c += custo;
    k->duracao_c += duracao;
}
paragens* encontra_paragem(paragens** par, char stop[BUFSIZ]){
    /*Procura o endereço de uma paragem*/
    paragens* p = *par;
    while(p != NULL){
        if(strcmp(stop, p->nome)==0){
            return p;
        }
        p = p->idx;
    }
    return NULL;
}
void primeira_lig(carreiras* k, paragens* p1, paragens* p2, char stop1[BUFSIZ], char stop2[BUFSIZ], double custo, double duracao){
    /*funcao que cria a primeira ligacao de uma carreira*/
    k->stops = (ligacoes*) malloc(sizeof(ligacoes)*2);
    k->stops[0].nome = (char*) malloc(sizeof(char)*(strlen(stop1)+1));
    strcpy(k->stops[0].nome, stop1);
    k->stops[0].custo_l = 0;
    k->stops[0].duracao_l = 0;

    k->stops[1].nome = (char*) malloc(sizeof(char)*(strlen(stop2)+1));
    strcpy(k->stops[1].nome, stop2);
    k->stops[1].custo_l = custo;
    k->stops[1].duracao_l = duracao;


    p1->num_car +=1;
    if(strcmp(p1->nome, p2->nome) != 0){
        p2->num_car +=1;
    }

    k->state = 1;
    k->num_par+=2;
}
void add_lig_esquerda(carreiras* k, paragens* p1, char stop1[BUFSIZ], double custo, double duracao){
    /*funcao que adiciona uma ligacao ao inicio do array de ligacoes*/
    int i;
    k->stops = realloc(k->stops, sizeof(ligacoes) * (k->num_par + 1));

    for (i = k->num_par; i > 0; i--){
        k->stops[i] = k->stops[i-1];   
    }

    if(pertence_carreira(k, p1) == FALSE){
        p1->num_car ++;
    }
    
    k->stops[0].nome = (char*) malloc(sizeof(char)*(strlen(stop1)+1));     
    strcpy(k->stops[0].nome, stop1);
    k->stops[0].custo_l = 0;
    k->stops[0].duracao_l = 0;

    k->stops[1].custo_l += custo;
    k->stops[1].duracao_l += duracao;

    k->num_par++;
    
}
void add_lig_circular(carreiras* k, char stop2[BUFSIZ], double custo, double duracao){
    /*FUncao que cria uma carreira com comeco e termino na mesma paragem*/
    k->stops = realloc(k->stops, sizeof(ligacoes) * (k->num_par + 1));
    k->stops[k->num_par].nome = (char*) malloc(sizeof(char)*(strlen(stop2)+1)); 

    strcpy(k->stops[k->num_par].nome, stop2);
    k->stops[k->num_par].custo_l = custo;
    k->stops[k->num_par].duracao_l = duracao;

    k->num_par++;
}
void add_lig_direita(carreiras* k, paragens* p2, char stop2[BUFSIZ], double custo, double duracao){
    /*funcao que adiciona uma ligacao ao fim do array*/
    k->stops = realloc(k->stops, sizeof(ligacoes) * (k->num_par + 1));

    if(pertence_carreira(k, p2) == FALSE){
        p2->num_car ++;
    }

    k->stops[k->num_par].nome = (char*) malloc(sizeof(char)*(strlen(stop2)+1)); 
    strcpy(k->stops[k->num_par].nome, stop2);
    k->stops[k->num_par].custo_l = custo;
    k->stops[k->num_par].duracao_l = duracao;

    k->num_par++;
}


void intersecao_function(carreiras** car, paragens** par){
    /*
     * funcao que itera todas as paragens uma a uma e verifica para cada uma 
     * quantas carreiras passam por essa paragem guardando os nomes das carreiras 
     * e imprime as em ordem alfabetica
    */
    int j, acc=0;
    char **array = NULL;
    carreiras* c = *car;
    paragens* p = *par;

    while(p != NULL){
        array = (char**) malloc(p->num_car * sizeof(char *));
        while(c != NULL){

            if(pertence_carreira(c, p)==TRUE){
                
                array[acc] = (char*) malloc(sizeof(char) * (strlen(c->nome) + 1));
                strcpy(array[acc], c->nome);

                acc+=1;          
            }
            c = c->idx;
        }
        if(acc>1){
            ordenacao(array, 0, acc-1);
            printf("%s %d: ", p->nome, acc);

            for(j=0;j<acc-1;j++){
                printf("%s ", array[j]);
            }   
            printf("%s\n", array[acc-1]);
        }
        
        if (array != NULL) {
            limpar_array(array, acc);
        }
        acc=0;
        c = *car;
        p = p->idx;
    }       
}
int pertence_carreira(carreiras* c, paragens* p){
    /*verificacao se a paragem pertence a carreira*/
    int k;
    for(k = 0; k < c->num_par; k++){
        if(strcmp(c->stops[k].nome, p->nome) == 0){
            return 1;
        }
    }
    return 0;
}
void limpar_array(char **array, int acc){
    /*funcao que limpa o array de strings da intersecao*/
    int i;
    for(i = 0; i < acc; i++){
        free(array[i]);
    }
    free(array);
}
void ordenacao(char **array, int l, int r){
    /*algoritmo de ordenacao*/
    int i = l, j = r;
    char *tmp;
    char *pivot = array[(l+r)/2];
    while(i<=j){
        while(strcmp(array[i], pivot)<0){
            i++;
        }
        while(strcmp(array[j], pivot)>0){
            j--;
        }
        if(i<=j){
            tmp = array[i];
            array[i]=array[j];
            array[j]=tmp;
            i++;
            j--;
        }
    }
    if(l<j){
        ordenacao(array, l, j);
    }
    if(l<r){
        ordenacao(array, i, r);
    }
}
