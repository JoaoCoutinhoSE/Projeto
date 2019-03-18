// O CODIGO DESTE ARQUIVO DEVERA SER COPIADO PARA PROJETO.C POSTERIORMENTE

#include<stdio.h>
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
	//componente selecionado pelo cursor
	booleano selecionado;
	
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
	
	//funcoes do componente
	void (*desenhar)(struct componente*); //referencia para a funcao que desenha o componente
	void (*tecla_pressionada)(char); //referencia para a funcao de atividade quando uma tecla e pressionada
	
	//indices dos componentes associados no vetor de componentes
	int componente_esquerdo;
	int componente_direito;
	int componente_inferior;
	int componente_superior;
}tipo_componente;

#define MAX_COMPONENTES 50
struct
{
	tipo_componente vetor[MAX_COMPONENTES];
	int topo;
}pilha_componentes;

void iniciar_interface() //inicializa a interface de usuario
{
	pilha_componentes.topo = 0;
}

void limpar_interface() //tira todos os componentes da interface
{
	pilha_componentes.topo = 0;
}

void adc_componente(tipo_componente comp) //adiciona componente a interface de usuario
{
	if(pilha_componentes.topo == MAX_COMPONENTES-1) return; //pilha cheia
		
	pilha_componentes.vetor[pilha_componentes.topo] = comp; //copia o comp para o vetor
	pilha_componentes.topo++;
}

void rm_ultimo_componente() //remove o ultimo componente colocado na pilha
{
	pilha_componentes.topo--;
}

void rm_componente(int indice) //remover componente especifico
{
	int i;
	if(indice < 0 || indice > MAX_COMPONENTES-1) return; //indice invalido
	
	for(i = indice; i < MAX_COMPONENTES; i++) //recuar uma posicao todos os componentes
	{
		   pilha_componentes.vetor[i] = pilha_componentes.vetor[i+1];	
	}	
	
	pilha_componentes.topo--;
	
	/*
	exemplo:
		vetor
		indice: 1 2 3 4 5
	componente: A B C D E
		 
	para remover o componente de indice 3, faço:
		rm_componente(3);
	e acontece o seguinte:
	
	1° - o elemento 4 é copiado para o indice 3
             i:3    [i]   (i+1)
		indice: 1 2 [3]    (4) 5
	componente: A B [D] <- (D) E
	
	2° - o elemento 5 é copiado para o indice 5
             i:4      [i]   (i+1)
		indice: 1 2 3 [4]    (5)
	componente: A B D [E] <- (E)
	
	3° - o topo é decrementado
	topo--;
		indice: 1 2 3 4
	componente: A B D E
	*/
}

void desenhar_interface()
{
	int i;
	for(i = 0; i < pilha_componentes.topo; i++)
	{
		//chama a funcao de desenhar de cada componente e passa ele mesmo como parametro por referencia
		pilha_componentes.vetor[i].desenhar(&pilha_componentes.vetor[i]);
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

int main()
{
	iniciar_interface();
	
	//criando primeiro nome
	tipo_componente nome;
	strcpy(nome.texto, "Filipe");
	nome.x = 10;
	nome.y = 10;
	nome.cor_fundo = CINZA;
	nome.cor_texto = AZUL;
	nome.desenhar = desenhar_nome;
	adc_componente(nome); //adicionando a pilha de componentes
	
	//criando segundo nome
	tipo_componente nome2;
	strcpy(nome2.texto, "Chagas");
	nome2.x = 15;
	nome2.y = 20;
	nome2.cor_fundo = VERMELHO;
	nome2.cor_texto = CINZA;
	nome2.desenhar = desenhar_nome;
	adc_componente(nome2); //adicionando a pilha de componentes
	
	desenhar_interface(); //desenhando todos os componentes

	getchar();
	
	return 0;
}