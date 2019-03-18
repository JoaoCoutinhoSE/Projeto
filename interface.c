// O CODIGO DESTE ARQUIVO DEVERA SER COPIADO PARA PROJETO.C POSTERIORMENTE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio2.h>

//cores conio
#define PRETO	0
#define AZUL	1
#define VERDE	2
#define CIANO	3
#define VERMELHO	4
#define ROSA	5
#define MARROM	6
#define CINZA	7

//caracteres da tabela ascii extendida em hexadecimal
//http://www.infoisis.eti.br/mqisi/tex/dos/pgtxdos001.htm
#define GRADE_SE	0xC9 //grade superior esquerda 
#define GRADE_SD	0xBB //grade superior direita
#define GRADE_IE	0xC8 //grade inferior esquerda
#define GRADE_ID	0xBC //grade inferior direita
#define GRADE_H		0xCD //grade horizontal
#define GRADE_V		0xBA //grave vertical
#define GRADE_CRUZ	0xCE //grade cruz

//tipo booleano
typedef unsigned char booleano; //define o tipo booleano como um inteiro de 8 bits
#define VERDADEIRO 1
#define FALSO 0

//struct que descreve um componente generico
typedef struct componente
{	
	booleano oculto; //caso seja verdadeiro, o componente não é desenhado
	
	//posicao e tamanho do componente
	int x;
	int y;
	int largura;
	int altura;
	
	//conteudo do componente
	char nome[50]; //nome do componente
	int cor_fundo;
	int cor_texto;
	char texto[50];
	
	//funcoes do componente (ponteiros-para-funcao)
	void (*desenhar)(struct componente*); //ponteiro para a funcao que desenha o componente
	void (*tecla_pressionada)(char); //ponteiro para a funcao de atividade quando uma tecla e pressionada
	
	//indices dos componentes associados no vetor de componentes
	int componente_esquerdo;
	int componente_direito;
	int componente_inferior;
	int componente_superior;
	int sub_componente; //para os sub-menus
}tipo_componente;

#define MAX_COMPONENTES 50
struct
{
	tipo_componente vetor[MAX_COMPONENTES];
	int topo;
	int selecionado; //indice do elemento selecionado pelas setas
}pilha_componentes;

// ----------- funcoes da interface -----------------

void iniciar_interface() //inicializa a interface de usuario
{
	pilha_componentes.topo = 0;
	pilha_componentes.selecionado = -1; //nenhum componente selecionado
}

void limpar_interface() //tira todos os componentes da interface
{
	pilha_componentes.topo = 0;
}

int adc_componente(tipo_componente comp) //adiciona componente a interface de usuario
{
	if(pilha_componentes.topo == MAX_COMPONENTES-1) //pilha cheia
	{
		printf("erro: pilha de componentes cheia");
		getchar();
		exit(1);
	}
		
	pilha_componentes.vetor[pilha_componentes.topo] = comp; //copia o comp para o vetor
	return pilha_componentes.topo++; //retorna o valor de todo antes do incremento
}

void rm_ultimo_componente() //remove o ultimo componente colocado na pilha
{
	if(pilha_componentes.topo == 0) return; //pilha vazia
		
	pilha_componentes.topo--;
}

void rm_componente(int indice) //remover componente especifico
{
	int i;
	if(pilha_componentes.topo == 0) return; //pilha vazia
		
	if(indice < 0 || indice > MAX_COMPONENTES-1) return; //indice invalido
	
	for(i = indice; i < pilha_componentes.topo; i++) //recuar uma posicao todos os componentes
	{
		   pilha_componentes.vetor[i] = pilha_componentes.vetor[i+1];	
	}	
	
	pilha_componentes.topo--;
}

void desenhar_interface()
{
	int i;
	for(i = 0; i < pilha_componentes.topo; i++)
	{
		if(pilha_componentes.vetor[i].oculto == FALSO) //se o componente não estiver oculto
		{
			//chama a funcao de desenhar de cada componente e passa ele mesmo como parametro por referencia
			pilha_componentes.vetor[i].desenhar(&pilha_componentes.vetor[i]);
		}
	}
}

void esperar_tecla()
{
	   char tecla = getch();
	   if(pilha_componentes.selecionado != -1) //o -1 indica que nenhum componente foi selecionado
	   {
	   		//chama a funcao do componente selecionado que trata o pressionamento de teclas 
	   		pilha_componentes.vetor[pilha_componentes.selecionado].tecla_pressionada(tecla);
	   }	
}

// ---- funcoes dos componentes -----

void desenhar_nome(tipo_componente *comp)
{	//esta funcao desenha um nome simples
	gotoxy(comp->x, comp->y);
	textcolor(comp->cor_texto);
	textbackground(comp->cor_fundo);
	printf("%s", comp->texto);
}

void desenhar_quadrado(tipo_componente *comp)
{	//esta funcao desenha um quadrado
	int x, y;
	textcolor(comp->cor_texto);
	textbackground(comp->cor_fundo);
	
	//preencher espaco
	for(x = comp->x; x <= comp->x + comp->largura; x++)
	{
		   for(y = comp->y; y <= comp->y + comp->altura; y++)
		   {
		   		gotoxy(x,y);
		   		printf(" ");
		   }	
	}
	
	//desenhar bordas
	for(x = comp->x; x <= comp->x + comp->largura; x++) //bordas horizontais
	{
		//borda de cima
		gotoxy(x, comp->y);
		printf("%c", GRADE_H);
		//borda de baixo 
		gotoxy(x, comp->y + comp->altura);
		printf("%c", GRADE_H);
	}
	
	for(y = comp->y; y <= comp->y + comp->altura; y++) //bordas verticais
	{
		//borda esquerda
		gotoxy(comp->x,y); 
		printf("%c", GRADE_V);
		//borda direita
		gotoxy(comp->x + comp->largura,y); 
		printf("%c", GRADE_V);
	}
	
	//desenhar cantos
	gotoxy(comp->x, comp->y); //superior esquerdo
	printf("%c", GRADE_SE);
	gotoxy(comp->x + comp->largura, comp->y); //superior direito
	printf("%c", GRADE_SD);
	gotoxy(comp->x, comp->y + comp->altura); //inferior esquerdo
	printf("%c", GRADE_IE);
	gotoxy(comp->x + comp->largura, comp->y + comp->altura); //inferior direito
	printf("%c", GRADE_ID);
}

int main()
{
	iniciar_interface();
	
	//criando quadrado
	tipo_componente quadrado;
	quadrado.oculto = FALSO;
	quadrado.x = 2;
	quadrado.y = 2;
	quadrado.largura = 15;
	quadrado.altura = 5;
	quadrado.cor_fundo = CINZA;
	quadrado.cor_texto = AZUL;
	quadrado.desenhar = desenhar_quadrado; //funcao que desenha o quadrado
	adc_componente(quadrado); //adicionando a pilha de componentes
	
	//criando nome
	tipo_componente nome;
	nome.oculto = FALSO;
	strcpy(nome.texto, "Jao Pedro");
	nome.x = 4;
	nome.y = 4;
	nome.cor_fundo = CINZA;
	nome.cor_texto = AZUL;
	nome.desenhar = desenhar_nome;
	adc_componente(nome); //adicionando a pilha de componentes
	
	desenhar_interface(); //desenhando todos os componentes

	getchar();
	
	return 0;
}