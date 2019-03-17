#include<stdio.h>
#include<string.h>
#include<conio2.h>
void tela()
{
textbackground(31);
textcolor(19);
gotoxy(1,1);
printf("%c", 201);//canto superior esquerdo
gotoxy(80,26);
printf("%c", 204);//canto inferior direito
int c;
int botao;
for(c = 2; c < 80; c++)//linhas superiores e inferiores na horizontal
{
	gotoxy(c,3);
	printf("%c", 205);
	gotoxy(c,1);
	printf("%c", 205);
	gotoxy(c,26);
	printf("%c", 205);
	gotoxy(c,24);
	printf("%c", 205);
}
gotoxy(1,24);
printf("%c", 204);//Junção esquerda
gotoxy(80,1);
printf("%c", 187);
int l;
for(l=2;l<26;l++)//linhas laterais na vertical
{
	gotoxy(1,l);
	printf("%c",186);
	gotoxy(80,l);
	printf("%c",186);
}
gotoxy(80,24);
printf("%c",185);
gotoxy(80,1);
printf("%c",187);
gotoxy(1,26);
printf("%c",200);
gotoxy(1,3);
printf("%c", 204);
gotoxy(80,3);
printf("%c", 185);
//opções do usuario
gotoxy(4,2);
printf("Cadastro\t\Listar     Buscar     Atualizar     Sair");
do
{
	gotoxy(4,2);
	
}while();
 }
 void telamenu()
 {
 	int botao;
 	int l;
 	int c;
 	for(l=4;l<12;l++)
 	{
 		//criação da tela de login
 		textbackground(31);
 		textcolor(19);
 		gotoxy(45,7);
 		printf("%c",201);
 		gotoxy(75,7);
 		printf("%c", 187);
 		gotoxy(46,8);
 		printf("        Tela de Menu");
 		for(l= 8; l<22; l++)
 		{
 			gotoxy(45, l);
 			printf("%c", 186);
 			gotoxy(75, l);
 			printf("%c", 186);
		}
		gotoxy(45,9);
		printf("%c",204);
		gotoxy(75,9);
		printf("%c",185);
		gotoxy(45,20);
		printf("%c",204);
		gotoxy(75,20);
		printf("%c",185);
		gotoxy(45,22);
		printf("%c",200);
		gotoxy(75,22);
		printf("%c",188);
		for(c=46; c<75; c++)
		{
			gotoxy(c,7);
			printf("%c",205);
			gotoxy(c,9);
			printf("%c",205);
			gotoxy(c,20);
			printf("%c",205);
			gotoxy(c,22);
			printf("%c",205);
			gotoxy(c,25);
			printf("%c", 205);		
			}
 	    }
 	    for(l = 47; l< 70; l++)
 	    {
 	    	gotoxy(l, 13);
 	    	printf("%c", 196);
 	    	gotoxy(l, 17);
 	    	printf("%c", 196);
		 }
 	    gotoxy(47,11);
 	    printf("Usuario:");
 	    gotoxy(47,15);
 	    printf("Senha:");
 	    gotoxy(46,21);
 	    printf("  <A>1 Acesso <C> Cadastro   ");
 	     for(l=22; l<26; l++)
	    {
	 	gotoxy(45, l);
		printf("%c", 186);
		gotoxy(75, l);
		printf("%c", 186); 
	    }
	    gotoxy(48,23);
	    textcolor(36);
	    textbackground(14);
	    printf("E");
	    textcolor(19);
	    textbackground(31);
	    printf("ntrar");
	    gotoxy(65,23);
	    textcolor(36);
	    textbackground(14);
	    printf("S");
	    textcolor(19);
	    textbackground(31);
	    printf("air");
	    botao = getch();
	    if (botao == 97 || botao == 99)
	   {
	 	system("cls");
	 	MenuCadastro();
	   }
	   if(botao == 115)
	   {
	   	exit(0);
	   } 
	 }
void MenuCadastro()
{
	int l;
	int c;
	gotoxy(34,4);
	textcolor(19);
	textbackground(31);
	printf("%c", 201);
	gotoxy(34,26);
	printf("%c",200);
	gotoxy(77,4);
	printf("%c",187);
	gotoxy(77,26);
	printf("%c",188);
	gotoxy(35,5);
	printf("a");//aqui faz o cadastro do usuario. Lembrete: começar a integrar no programa principal daqui
	for (l = 35; l <77; l++)
	{
		gotoxy(l, 6);
		printf("%c", 196);
		gotoxy(l, 8);
		printf("%c", 196);
		gotoxy(l, 10);
		printf("%c", 196);
		gotoxy(l, 12);
		printf("%c", 196);
		gotoxy(l, 14);
		printf("%c", 196);
		gotoxy(l, 16);
		printf("%c", 196);
		gotoxy(l, 18);
		printf("%c", 196);
		gotoxy(l, 20);
		printf("%c", 196);
		gotoxy(l, 22);
		printf("%c", 196);
		gotoxy(l, 24);
		printf("%c", 196);
	}
	for(l=35; l < 77; l++)
	{
		gotoxy(l, 4);
		printf("%c",205);
		gotoxy(l, 26);
		printf("%c",205);
	}
	for(c=5; c< 26; c++)
	{
		gotoxy(34, c);
		printf("%c",186);
		gotoxy(77, c);
		printf("%c",186);
	}
	gotoxy(10,10);
}
void submenu(int csub, int parametros)
{
	int l;
	int c;
	int mx;
	int my;
	textbackground(0);
	for(l= 0, mx=11,my=parametros+1; l<=my; l++)// Laço de repetição que coloca parametros no submenu
	{
		gotoxy(csub, l+4);
		for(c = 0; c<=mx; c++)
		{
			if(l==0&&c==0)
			{
				printf("%c",218);
			}
			else if(l==my&&c==0)
			    printf("%c",192);
			else if(l==0&&c==mx)
			    printf("%c",191);
			else if(l==my&&c==mx)
			    printf("%c",217);
			else if(l==0||l==my)
			    printf("%c",196);
			else if(c==0||c==mx)
			    printf("%c",179);
			else
				printf(" ");		
		}//ta com bug que o getch não esta indo para onde deveria ir
	}
	char botao;
	int parametros2;
	do
	{
		gotoxy(csub+1,5);
		printf("Aluno");
		if(parametros>=2)
		{
			gotoxy(csub+1,6);
			printf("Professor");
		}
		if(parametros>=3)
		{
			gotoxy(csub+1,7);
			printf("Materia");
		}
		if(parametros==4)
		{
			gotoxy(csub+1,8);
			printf("Turma");
		}
		botao = getch();
		if (botao == 80 &&parametros2<parametros)
		{
			parametros2++;
		}
		if (botao == 72 &&parametros2>1)
		{
			parametros2--;
		}
	}while(botao!=13&&botao!=27);
	textbackground(31);
	for(l = 0, mx=11,my=parametros+1; l<=my; l++)
	{
		gotoxy(csub,l+4);
		for(c=0;c<=mx;c++)
		{
			printf(" ");
		}
	}
}
 int main(void)
 {
	 /*
 	MenuCadastro();
 	system("pause");
 	system("cls");
 	*/
 	telamenu();
	system("pause");//retirar quando for scan	
 	system("cls");
 	tela();
 	submenu(4,4);        //escolha de parametro
 	gotoxy(25,25);
 	system("pause");
 	return 0;
  } 
