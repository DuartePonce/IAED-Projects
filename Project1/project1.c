/* iaed-23 - ist1107489 - project1 */
#include "project1.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Arrays das estruturas com o seu respetivo tamanho maximo*/
carreira carreiras[MAX_CA];
paragem paragens[MAX_PA];

/*indices globais das arrays*/
int index_carreira = 0, index_paragem = 0;

/*Funcoes auxiliares para o comando p*/
int p_function();
void print_paragem(char str[MAX_NAME_PA]);
void add_paragem(char str_lati[BUFSIZ], char str_longi[BUFSIZ], char str[MAX_NAME_PA]);
int is_white_space(char str[BUFSIZ]);
int verificacao_par(char str_name[MAX_NAME_PA]);

/*Funcoes auxiliares para o comando c*/
void c_function();
void c_n_argumentos();
void cria_carreira(char str_name[MAX_NAME_CA]);
int carreira_existe(char str[MAX_NAME_CA]);
int verificacao_inverso(char str[MAX_NAME_PA]);
void inverse_stops(char str[MAX_NAME_CA]);
void stops_normal(char str[MAX_NAME_CA]);

/*Funcoes auxiliares para o comando l*/
void l_function();
int paragem_existe(char str[MAX_NAME_PA]);
int verificacao_link(char nome[MAX_NAME_CA], char stop1[MAX_NAME_PA], char stop2[MAX_NAME_PA]);
int encontra_paragem(char stop[MAX_NAME_PA]);
int encontra_carreira(char name[MAX_NAME_CA]);
void add_ligacao(char name[MAX_NAME_CA], char stop1[MAX_NAME_PA], char stop2[MAX_NAME_PA], double custo, double duracao);
void ligacao_aux(char nome_ca[MAX_NAME_CA], char stop1[MAX_NAME_PA], char stop2[MAX_NAME_PA], double custo, double duracao);

/*Funcoes auxiliares para o comando i*/
void i_function();
void ordenacao(char *array[], int l, int r);
int pertence_carreira(int i, int j);

/*
 * funcao main onde recebo os comandos e 
 * redireciono para as funcoes de cada um
*/
int main(){
    int state = 0;
    char ch ;

    while (state != 1){
        ch = getchar();
        switch (ch) {
        case 'q':
            state = 1;
            break;
        case 'c':
            c_function();
            break;
        case 'p':
            p_function();
            break;
        case 'l':
            l_function();
            break;
        case 'i':
            i_function();
            break;
        }
    }
    return 0;
}
/*
Funcao chamada quando c  
e escrito na linha de comandos
*/
void c_function(){
    char string[BUFSIZ], str_inverso[BUFSIZ], str_name[MAX_NAME_CA];
    char *token;
    fgets(string, BUFSIZ, stdin);

    /*Verificacao se o input a seguir ao comando existe ou nao*/
    if(is_white_space(string)!=0){
        c_n_argumentos();
        return;
    }
    token = strtok(string, BLANK);
    strcpy(str_name,token);
    /*
     * verificacao se a carreira existe ou nao
     * primeira opacao cria um carreira nova
     * segunda opcao lista por odem de criacao
     * ou ao contrario
    */
    if(carreira_existe(str_name) == 0){
        cria_carreira(str_name);
        return;
    }
    token = strtok(NULL, BLANK);
    if(carreira_existe(str_name) == 0){
        cria_carreira(str_name);
    }
    else{
        if(token != NULL){   
            strcpy(str_inverso,token);
            /*verificacaodo inverso*/
            if(verificacao_inverso(str_inverso) == TRUE){
                inverse_stops(str_name);
            }
            else{
                printf("incorrect sort option.\n");
            }
        }
        else if(carreiras[encontra_carreira(str_name)].num_stops!=0){
            stops_normal(str_name);
        }    
    }
}
void c_n_argumentos(){
    /*
     * Funcao que que da printf de todas as carreiras criadas e sua respetiva informacao
     * imprimindo o nome da carreira, o nome da paragem de origem e de destino, 
     * o numero total de paragens da carreira, custo e duracao
    */
    int i;
    for(i=0;i!=index_carreira;i++){
        if(carreiras[i].state==1){
            printf("%s %s %s %d %.2f %.2f\n", carreiras[i].name, carreiras[i].stops[0].name, 
            carreiras[i].stops[carreiras[i].num_stops-1].name, carreiras[i].num_stops, carreiras[i].custo_c,
            carreiras[i].duracao_c);
        }
        else{
            printf("%s %d %.2f %.2f\n", carreiras[i].name, carreiras[i].num_stops, carreiras[i].custo_c,
            carreiras[i].duracao_c);
        }
    }
}
void cria_carreira(char str[MAX_NAME_CA]){
    /*funcao que cria uma carreira nova*/
    strcpy(carreiras[index_carreira].name, str);
    carreiras[index_carreira].num_stops=0;
    carreiras[index_carreira].custo_c=0;
    carreiras[index_carreira].duracao_c=0;
    carreiras[index_carreira].state=0;
    index_carreira+=1;
}
int carreira_existe(char str[MAX_NAME_CA]){
    /*funcao que verifica se existe ou uma carreira com o nome como input*/
    int i;
    for(i=0;i!=index_carreira;i++){
        if(strcmp(str, carreiras[i].name)==0){
            return 1;
        }
    }
    return 0;
}
int verificacao_inverso(char str[MAX_NAME_PA]){
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
void stops_normal(char str[MAX_NAME_CA]){
    /*impressao das paragens da carreira por odem de criacao*/
    int i, j;
    for(i=0; i<=index_carreira; i++){
        if(strcmp(str, carreiras[i].name)==0){
            for(j=0; j<carreiras[i].num_stops-1; j++){
                printf("%s, ", carreiras[i].stops[j].name);
            }
            printf("%s\n", carreiras[i].stops[carreiras[i].num_stops-1].name);
            break;
        }
    }
    
}
void inverse_stops(char str[MAX_NAME_CA]){
    /*Impressao das paragens por ordem inversa*/
    int i, j;
    for(i=0; i<=index_carreira; i++){
        if(strcmp(str, carreiras[i].name)==0){
            for(j=carreiras[i].num_stops-1; j>0; j--){
                printf("%s, ", carreiras[i].stops[j].name);
            }
            printf("%s\n", carreiras[i].stops[0].name);
            break;
        }
    }
}
/*
 * Funcao chamada quando p  
 * e escrito na linha de comandos
*/
int p_function(){
	char string[BUFSIZ], str_lati[BUFSIZ], str_longi[BUFSIZ], str_name[MAX_NAME_PA];
    int i;
    char *token;
    fgets(string, BUFSIZ, stdin);
    /*
     * verificacao do input a seguir ao comando p
     * impressao de todas as paragens do array de paragens
    */
	if(is_white_space(string)==TRUE || strcmp(string, BLANK_N)==FALSE){
		for(i=0; i<index_paragem; i++){
            printf("%s: %16.12f %16.12f %d\n", paragens[i].name, paragens[i].latitude, 
            paragens[i].longitude, paragens[i].numero_car);
        }
		return 0;
	}
    /*verificacao da existencia de aspas*/
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
    /*impressao da paragem com o nome listado noo input*/
	if(token==NULL){
		print_paragem(str_name);
		return 0;
	}
    /*criacao de paragem*/
	else{
		strcpy(str_lati, token);
		token = strtok(NULL, BLANK);
		strcpy(str_longi, token);
		add_paragem(str_lati, str_longi, str_name);
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
void add_paragem(char str_lati[BUFSIZ], char str_longi[BUFSIZ], char str_name[MAX_NAME_PA]){
    /*funcao que cria e adiciona uma paragem ao array de paragens*/
    if(verificacao_par(str_name)==TRUE){
        strcpy(paragens[index_paragem].name,str_name);
        paragens[index_paragem].latitude = atof(str_lati);
        paragens[index_paragem].longitude = atof(str_longi);
        paragens[index_paragem].numero_car = 0;
        index_paragem+=1;
    }
}
int verificacao_par(char str_name[MAX_NAME_PA]){
    /*funcao que verifica se a paragem com o nome dado de input existe ou nao*/
    int i;
    for(i=0; i!=index_paragem; i++){
        if(strcmp(paragens[i].name, str_name)==0){
            printf("%s: stop already exists.\n", str_name);
            return 0;
        }
    }
    return 1;
}
void print_paragem(char str[MAX_NAME_PA]){
    int i, state = 0;
    /*funcao que verifica e caso exista imprime a paragem dada no input*/
    for(i=0; i!=index_paragem; i++){
        if(strcmp(paragens[i].name, str)==0){
            printf("%16.12f %16.12f\n", paragens[i].latitude, paragens[i].longitude);
            state = TRUE;
            break;
        }
    }
    if(state == FALSE){
        printf("%s: no such stop.\n", str);
    }
}
/*
 Funcao chamada quando l 
 e escrito na linha de comandos
 */
void l_function(){
    /*
     * Esta funcao tem como objetivo tratar e organizar o input dado no stdin 
     * e depois envia-lo para a sua auxiliar
    */
	char *token;
    char nome_ca[MAX_NAME_CA], stop1[MAX_NAME_PA], stop2[MAX_NAME_PA];
    char string[BUFSIZ];
	int len=0,state=0;
    double custo, duracao;
    fgets(string, BUFSIZ, stdin);

    token=strtok(string,BLANK);
    strcpy(nome_ca, token);
    len = strlen(nome_ca)+2;
	/*Verificacao se a carreira existe ou nao*/
    if(carreira_existe(nome_ca)==FALSE){
        printf("%s: no such line.\n", nome_ca);
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
    ligacao_aux(nome_ca, stop1, stop2, custo, duracao);
}
void ligacao_aux(char nome_ca[MAX_NAME_CA], char stop1[MAX_NAME_PA], char stop2[MAX_NAME_PA], double custo, double duracao){
    /*Verificacao se as duas paragens dadas existem*/
    if(paragem_existe(stop1)==TRUE&&paragem_existe(stop2)==TRUE){
        /*verificacao se as e possivel establecer a ligacao*/
		if(verificacao_link(nome_ca, stop1, stop2)==1){
            /*Verificacao se e possivel o custo e duracao sao maiores ou iguais a 0*/
			if(custo>=0 && duracao>=0){
                /*funcao que adiciona a ligacao*/
				add_ligacao(nome_ca, stop1, stop2, custo, duracao);
			}
			else{
				printf("negative cost or duration.\n");
			}
		}
		else{
			printf("link cannot be associated with bus line.\n");
		}
	}
	else if(paragem_existe(stop1)==FALSE){
       printf("%s: no such stop.\n", stop1);
	}
	else{
		printf("%s: no such stop.\n", stop2);
	}
}
int paragem_existe(char str[MAX_NAME_PA]){
    /*funcao que verifica se a paragem existe*/
    int i;
    for(i=0;i!=index_paragem;i++){
        if(strcmp(str, paragens[i].name)==0){
            return 1;
        }
    }
    return 0;
}
int verificacao_link(char nome[MAX_NAME_CA], char stop1[MAX_NAME_PA], char stop2[MAX_NAME_PA]){
    /*Verificacao se a ligacao e possivel establecer*/
    int i;
    for(i=0;i!=index_carreira;i++){
        if(strcmp(nome, carreiras[i].name)==0){
            if(strcmp(stop1, carreiras[i].stops[carreiras[i].num_stops-1].name)==0 || 
               strcmp(stop2, carreiras[i].stops[0].name)==0 || 
               carreiras[i].state==0){
                return 1;
            }
        }
    }
    return 0;
}
void add_ligacao(char name[MAX_NAME_CA], char stop1[MAX_NAME_PA], char stop2[MAX_NAME_PA], double custo, double duracao){
    /*Funcao que cria a ligacao*/
    int i, k, p1, p2;
    /*procura dos indices da carreira e paragens do input para a ligacao*/
    k = encontra_carreira(name);
    p1 = encontra_paragem(stop1);
    p2 = encontra_paragem(stop2);
    /*condicao para se adicionar uma nova paragem de origem*/
    if(strcmp(carreiras[k].stops[0].name, paragens[p2].name)==0 &&
       strcmp(carreiras[k].stops[carreiras[k].num_stops-1].name, paragens[p1].name)!=0){    
        for (i = carreiras[k].num_stops; i > 0; i--){
            carreiras[k].stops[i] = carreiras[k].stops[i-1];   
        }
        carreiras[k].stops[0] = paragens[p1];
        carreiras[k].num_stops++;
        paragens[p1].numero_car +=1;
    }
    /*condicao para adicionar e criar uma carreira circular*/
    else if(strcmp(carreiras[k].stops[0].name, paragens[p2].name)==0){
        carreiras[k].stops[carreiras[k].num_stops] = paragens[p2];
        carreiras[k].num_stops+=1;
    }           
    /*condicao da criacao da primeira ligacao*/
    else if(carreiras[k].state == FALSE){
        carreiras[k].stops[0] = paragens[p1];
        paragens[p1].numero_car +=1;
        carreiras[k].stops[1] = paragens[p2];
        paragens[p2].numero_car +=1;
        carreiras[k].state = 1;
        carreiras[k].num_stops+=2;
    }
    /*condicao que adiciona uma paragem a direita*/
    else{
        carreiras[k].stops[carreiras[k].num_stops] = paragens[p2];
        paragens[p2].numero_car +=1;
        carreiras[k].num_stops+=1;
    }
    carreiras[k].custo_c += custo;
    carreiras[k].duracao_c += duracao;
}
int encontra_paragem(char stop[MAX_NAME_PA]){
    /*Procura o indice de uma paragem*/
    int i, k=0;
    for(i=0;i!=index_paragem;i++){
        if(strcmp(stop, paragens[i].name)==0){
            k=i;
            break;
        }
    }
    return k;
}
int encontra_carreira(char name[MAX_NAME_CA]){
    /*Procura o indice de uma carreira*/
    int i, k=0;
    for(i=0;i!=index_carreira;i++){
        if(strcmp(name, carreiras[i].name)==0){
            k=i;
            break;
        }
    }
    return k;
}
/*
 Funcao chamada quando i 
 e escrito na linha de comandos
 */
void i_function(){
    /*
     * funcao que itera todas as paragens uma a uma e verifica para cada uma 
     * quantas carreiras passam por essa paragem guardando os nomes das carreiras 
     * e imprime as em ordem alfabetica
    */
    int i, j, acc=0;
    char *array[MAX_CA];

    for(i=0;i<index_paragem;i++){
        for(j=0;j<index_carreira;j++){
            if(pertence_carreira(i, j)==TRUE){
                array[acc]=carreiras[j].name;
                acc+=1;          
            }
        }
        if(acc>1){
            ordenacao(array, 0, acc-1);
            printf("%s %d: ", paragens[i].name, acc);
            for(j=0;j<acc-1;j++){
                printf("%s ", array[j]);
            }   
            printf("%s\n", array[acc-1]);
        }
        memset(array, 0, acc*sizeof(char *));
        acc=0;
        
    }       
}
int pertence_carreira(int i, int j){
    /*verificacao se a paragem pertence a carreira*/
    int k;
    for(k=0;k<carreiras[j].num_stops;k++){
        if(strcmp(carreiras[j].stops[k].name, paragens[i].name)==0){
            return 1;
        }
    }
    return 0;
}
void ordenacao(char *array[], int l, int r){
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
