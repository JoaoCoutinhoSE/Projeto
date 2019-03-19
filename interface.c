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

//teclas
#define SETA 			(char)224
#define SETA_CIMA 		(char)72
#define SETA_BAIXO 		(char)80
#define SETA_ESQUERDA 	(char)75
#define SETA_DIREITA 	(char)77
#define ENTER 			(char)13
#define ESC 			(char)39

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
	void (*selecionar)(); //ponteiro para a funcao que faz algo quando o componente é selecionado
	void (*deselecionar)();	//ponteiro para a funcao que faz algo quando o componente é deselecionado
	void (*tecla_pressionada)(char); //ponteiro para a funcao de atividade quando uma tecla e pressionada
	void (*atividade)(); //pointeiro para a funcao de atividade quando o ENTER é pressionado sobre o componente
	
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

void funcao_vazia(){} //uma funcao que serve exclusivamente para não fazer nada

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
	if(indice < 0 || indice > pilha_componentes.topo) return; //indice invalido
	
	for(i = indice; i < pilha_componentes.topo; i++) //recuar uma posicao todos os componentes
	{
		   pilha_componentes.vetor[i] = pilha_componentes.vetor[i+1];	
	}	
	
	pilha_componentes.topo--;
}

void desenhar_interface()
{
	int i;
	textbackground(PRETO);
	system("cls");
	for(i = 0; i < pilha_componentes.topo; i++)
	{
		if(pilha_componentes.vetor[i].oculto == FALSO) //se o componente não estiver oculto
		{
			//chama a funcao de desenhar de cada componente e passa ele mesmo como parametro por referencia
			pilha_componentes.vetor[i].desenhar(&pilha_componentes.vetor[i]);
		}
		
		if(pilha_componentes.selecionado == i)
		{
				int x = pilha_componentes.vetor[i].x;
				int y = pilha_componentes.vetor[i].y;
				//escrever um asterisco vermelho e cinza no canto do componente para mostrar que ele foi selecionado
				gotoxy(x,y);
				textbackground(VERMELHO);
				textcolor(CINZA);
				printf("*");
		}
	}
}



void esperar_tecla()
{
	   char tecla = getch();
	   if(pilha_componentes.selecionado != -1) //o -1 indica que nenhum componente foi selecionado
	   {
	   		//chama a funcao do componente selecionado que trata o pressionamento de teclas 
	   		int selec = pilha_componentes.selecionado;
	   		pilha_componentes.vetor[selec].tecla_pressionada(tecla);
	   }	
}

void selecionar_componente(int indice)
{
	if(indice < 0 || indice > pilha_componentes.topo) return; //indice invalido

	if(pilha_componentes.selecionado != -1) //se houver um componente a ser deselecionado
		pilha_componentes.vetor[pilha_componentes.selecionado].deselecionar();
	
	pilha_componentes.selecionado = indice;
	pilha_componentes.vetor[indice].selecionar();
	desenhar_interface(); //redesenhar interface
}

// ---- funcoes dos componentes -----

void desenhar_texto(tipo_componente *comp)
{	//esta funcao desenha um texto simples
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

// ------ componentes interativos ----------

// ---- botão ----
void desenhar_botao(tipo_componente *comp)
{
	desenhar_quadrado(comp);
	gotoxy(comp->x+1, comp->y+1);
	printf("%s", comp->texto);
}

void selecionar_botao()
{
}

void deselecionar_botao()
{
}

void receber_tecla(char tecla)
{
	int selec = pilha_componentes.selecionado; //pega o indicio do componente selecionado
	int superior =  pilha_componentes.vetor[selec].componente_superior;
	int inferior = pilha_componentes.vetor[selec].componente_inferior;
	int esquerdo = pilha_componentes.vetor[selec].componente_esquerdo;
	int direito = pilha_componentes.vetor[selec].componente_direito;
	int sub = pilha_componentes.vetor[selec].sub_componente;
	
	if(tecla == SETA) //se uma seta foi pressionada
	{
		char seta = getch(); //captura o codigo da seta especifica
		switch(seta)
		{
			case SETA_CIMA:
			{	
				if(superior != -1)
				   	selecionar_componente(superior);
   	   	   	   	   
				break;
			}
			
			case SETA_BAIXO:
			{		
				if(inferior != -1)
				   	selecionar_componente(inferior);
				break;
			}
			
			case SETA_ESQUERDA:
			{	
				if(esquerdo != -1)
				   	selecionar_componente(esquerdo);
				break;
			}
			
			case SETA_DIREITA:
			{
				if(direito != -1)
				   	selecionar_componente(direito);	
				break;
			}
			
		default:
			break;
		}
	}
	else if(tecla = ENTER) //se a tecla pressionada for enter
	{
		pilha_componentes.vetor[selec].atividade();	
	}
}

void inicializar_texto(tipo_componente *comp, char texto[], int x, int y)
{	//define um texto padrao
	comp->oculto = FALSO;
	comp->x = x;
	comp->y = y;
	comp->cor_fundo = PRETO;
	comp->cor_texto = CIANO;
	strcpy(comp->nome, "texto");
	strcpy(comp->texto, texto);
	
	comp->desenhar = desenhar_texto;
	
	//este componente não deve ser selecionado
	comp->selecionar = funcao_vazia;
	comp->deselecionar = funcao_vazia;
	comp->tecla_pressionada = funcao_vazia;
	comp->atividade = funcao_vazia; //nao faz nada por padrao
	
	//nenhum componente associado as setas
	comp->componente_esquerdo = -1;
	comp->componente_direito = -1;
	comp->componente_superior = -1;
	comp->componente_inferior = -1;
	comp->sub_componente = -1;
}

void inicializar_quadrado(tipo_componente *comp, int x, int y, int largura, int altura)
{//define um quadrado padrao
	comp->oculto = FALSO;
	comp->x = x;
	comp->y = y;
	comp->largura = largura;
	comp->altura = altura;
	comp->cor_fundo = PRETO;
	comp->cor_texto = CIANO;
	strcpy(comp->nome, "quadrado");
	
	comp->desenhar = desenhar_quadrado;
	
	//este componente não deve ser selecionado
	comp->selecionar = funcao_vazia;
	comp->deselecionar = funcao_vazia;
	comp->tecla_pressionada = funcao_vazia;
	comp->atividade = funcao_vazia; //nao faz nada por padrao
	
	//nenhum componente associado as setas
	comp->componente_esquerdo = -1;
	comp->componente_direito = -1;
	comp->componente_superior = -1;
	comp->componente_inferior = -1;
	comp->sub_componente = -1;
}

void inicializar_botao(tipo_componente *comp, char texto[], int x, int y) 
{//define um componente como um botao pradrao
	comp->oculto = FALSO;
	comp->x = x;
	comp->y = y;
	comp->largura = strlen(texto)+1;
	comp->altura = 2;
	comp->cor_fundo = PRETO;
	comp->cor_texto = CIANO;
	strcpy(comp->nome, "botao");
	strcpy(comp->texto, texto);
	
	comp->desenhar = desenhar_botao;
	comp->selecionar = selecionar_botao;
	comp->deselecionar = deselecionar_botao;
	comp->tecla_pressionada = receber_tecla;
	comp->atividade = funcao_vazia; //nao faz nada por padrao
	
	//nenhum componente associado as setas
	comp->componente_esquerdo = -1;
	comp->componente_direito = -1;
	comp->componente_superior = -1;
	comp->componente_inferior = -1;
	comp->sub_componente = -1;
}


// ----------------------- PARTE DE TESTES -------------------------

void dizer_ola()
{
	tipo_componente quadrado;
	inicializar_quadrado(&quadrado, 2, 2, 19, 19);
	quadrado.cor_fundo = CINZA;
	quadrado.cor_texto = AZUL;
	adc_componente(quadrado);
	
	tipo_componente txt;
	inicializar_texto(&txt, "Ola, tudo bem?", 5, 5);
	txt.cor_fundo = CINZA;
	txt.cor_texto = AZUL;
	adc_componente(txt);

	desenhar_interface();
	
	while(getch() != ENTER);
	
	//remove os dois ultimos componentes inseridos na interface
	rm_ultimo_componente();
	rm_ultimo_componente();
	
	desenhar_interface(); //redesenha interface
}

void dizer_oi()
{
	tipo_componente quadrado;
	inicializar_quadrado(&quadrado, 2, 2, 19, 19);
	quadrado.cor_fundo = CINZA;
	quadrado.cor_texto = AZUL;
	adc_componente(quadrado);
	
	tipo_componente txt;
	inicializar_texto(&txt, "Oi, tudo bem?", 5, 5);
	txt.cor_fundo = CINZA;
	txt.cor_texto = AZUL;
	adc_componente(txt);

	desenhar_interface();
	
	while(getch() != ENTER);
	
	//remove os dois ultimos componentes inseridos na interface
	rm_ultimo_componente();
	rm_ultimo_componente();
	
	desenhar_interface(); //redesenha interface
}

void dizer_thau()
{
	tipo_componente quadrado;
	inicializar_quadrado(&quadrado, 2, 2, 19, 19);
	quadrado.cor_fundo = CINZA;
	quadrado.cor_texto = AZUL;
	adc_componente(quadrado);
	
	tipo_componente txt;
	inicializar_texto(&txt, "Thau, ate mais", 5, 5);
	txt.cor_fundo = CINZA;
	txt.cor_texto = AZUL;
	adc_componente(txt);

	desenhar_interface();
	
	while(getch() != ENTER);
	
	//remove os dois ultimos componentes inseridos na interface
	rm_ultimo_componente();
	rm_ultimo_componente();
	
	desenhar_interface(); //redesenha interface
}

void dizer_adeus()
{
	tipo_componente quadrado;
	inicializar_quadrado(&quadrado, 2, 2, 19, 19);
	quadrado.cor_fundo = CINZA;
	quadrado.cor_texto = AZUL;
	adc_componente(quadrado);
	
	tipo_componente txt;
	inicializar_texto(&txt, "Adeus :'(", 5, 5);
	txt.cor_fundo = CINZA;
	txt.cor_texto = AZUL;
	adc_componente(txt);

	desenhar_interface();
	
	while(getch() != ENTER);
	
	//remove os dois ultimos componentes inseridos na interface
	rm_ultimo_componente();
	rm_ultimo_componente();
	
	desenhar_interface(); //redesenha interface
}

int main()
{
	iniciar_interface();
	
	//criando quadrado
	tipo_componente bot1;
	inicializar_botao(&bot1, "Dizer ola", 3, 3);
	bot1.atividade = dizer_ola;
	int bot1_i = adc_componente(bot1);
	
	tipo_componente bot2;
	inicializar_botao(&bot2, "Dizer oi", 16, 3);
	bot2.atividade = dizer_oi;
	int bot2_i = adc_componente(bot2);
	
	tipo_componente bot3;
	inicializar_botao(&bot3, "Dizer thau", 3, 7);
	bot3.atividade = dizer_thau;
	int bot3_i = adc_componente(bot3);
	
	tipo_componente bot4;
	inicializar_botao(&bot4, "Dizer adeus", 16, 7);
	bot4.atividade = dizer_adeus;
	int bot4_i = adc_componente(bot4);
	
	//associando os componentes no vetor pelas setas
	//bot1
	pilha_componentes.vetor[bot1_i].componente_direito = bot2_i;
	pilha_componentes.vetor[bot1_i].componente_inferior = bot3_i;
	
	//bot2
	pilha_componentes.vetor[bot2_i].componente_esquerdo = bot1_i;
	pilha_componentes.vetor[bot2_i].componente_inferior = bot4_i;
	
	//bot3
	pilha_componentes.vetor[bot3_i].componente_direito = bot4_i;
	pilha_componentes.vetor[bot3_i].componente_superior = bot1_i;
	
	//bot4
	pilha_componentes.vetor[bot4_i].componente_esquerdo = bot3_i;
	pilha_componentes.vetor[bot4_i].componente_superior = bot2_i;
	
	desenhar_interface(); //desenhando todos os componentes
	selecionar_componente(bot1_i);
	while(1) esperar_tecla();
	
	return 0;
}