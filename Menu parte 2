#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<ctype.h>
#include<string.h>
#define MAXTAM 100

typedef struct dados
{
     char aluno[30];
     char prof[30];
     char rga[12];
     char data[30];
     char mae[30];
     char pai[30];
}dados;

typedef struct
{
	dados item[MAXTAM];
	int topo;
} pilha;

void pilha_inicia (pilha *p)
{
	p->topo = -1;
}

int pilha_vazia (pilha *p)
{
	if (p->topo == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int pilha_cheia (pilha *p)
{
	if (p->topo == MAXTAM-1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void pilha_insere (pilha *p, dados dado)
{
	if (pilha_cheia(p) == 1)
	{
		printf("ATENÇÃO: O numero de cadastros excedeu");
	}
	else
	{
		p->topo++;
		p->item[p->topo] = dado;
	}
}

void pilha_remove (pilha *p, int i)
{
	while (i < MAXTAM)
	{
		p->item[i-1] = p->item[i];
		i++;
	}
	p->topo--;
}

int apenas_numeros (char str[])
{
	int i;
	for(i = 0; i < strlen(str); i++)
	{
		if(str[i] < '0' || str[i] > '9') return 0;  
	}
	
	return 1;
}

int apenas_letras(char str[])
{
	int i;
	for(i = 0; i < strlen(str); i++)
    {
        if(!isalpha(str[i]))
        {
        	return 0;
		}  
    }
    return 1;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    dados cadastro;
    int i, op, opcadastro;
    char str[120];
    pilha p;
    pilha_inicia(&p);
	do
	{
    	printf("Digite nome: ");
    	scanf("%s", cadastro.aluno);
    	setbuf(stdin, NULL);
	}while(!apenas_letras(cadastro.aluno));
    do
    {
    	printf("Digite seu rga: ");
    	scanf("%s", cadastro.rga);
    	setbuf(stdin, NULL);
	}while(!apenas_numeros(cadastro.rga));
    printf("Informe sua data de Nascimento na ordem: Dia, Mês e Ano: ");
	do
	{
		scanf("%s", cadastro.data);
		setbuf(stdin, NULL);
    }while(!apenas_numeros(cadastro.data));    
    do
    {
    	printf("Digite o nome do Pai: ");
    	scanf("%s", cadastro.pai);
    	setbuf(stdin, NULL);
	}while(!apenas_letras(cadastro.pai));
	do
	{
		printf("Digite o nome da Mãe: ");
		scanf("%s", cadastro.mae);
		setbuf(stdin, NULL);
	}while(!apenas_letras(cadastro.mae));
	pilha_insere(&p, cadastro);
	/*
	case 2:
		do
		{
			printf("Digite seu nome");
			scanf("%s", cadastro.prof);
			setbuf(stdin, NULL);
		}while(!apenas_letras(cadastro.prof));	 	
}
*/
    return 0;
}
