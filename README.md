#Descrição do interface.c
Ultima atualização: 17/03/19, Filipe
Este código utiliza ponteiro-para-função, também conhecido como callback. Pesquise sobre isso.

##struct componente
Esta classe-struct contém todas as informações de um componente genérico, como um quadrado, um botão, um menu, etc.
Várias structs podem ser criadas a partir desta classe-struct ou do tipo tipo_componente.

##pilha_componentes
Esta struct é estática. Ela é criada na memória assim que é declarada, não há outras iguais a ela. Ela contém os dados da pilha de componentes da interface de usuário: o vetor, indice do topo e o indice do componente selecionado. Todos os componentes a serem desenhados devem ser inseridos nesta pilha.

##void iniciar_interface()
Esta função inicializa a interface. Ela deve ser chamada no inicio do programa.

##void limpar_interface()
Esta função retira todos os componentes da pilha de componentes. Ela deve ser chamada antes de construir uma nova tela. 

##int adc_componente(tipo_componente comp)
Esta função insere um novo componente na pilha de componentes e retorna o indice deste componente no vetor da pilha. O componente NÃO deve ser passado por referência.

##void rm_ultimo_componente()
Esta função retira o ultimo componente inserido na pilha de componentes.

##void rm_componente(int indice)
Esta função retira um componente especifico da pilha de componentes. O componente é especificado pelo indice.

##void desenhar_interface()
Esta função desenha todos os componentes na pilha de componentes. Ela faz isso chamando as funções de desenho dos respectivos componentes através do callback desenhar, presente no tipo_componente;

##void esperar_tecla()
Esta função chama, internamente, o getchar. Em seguida, depois que o usuário pressionar alguma tecla, ela chama a função de pressionamento de tecla do componente selecionado, através do callback tecla_pressionada

# Funções que desenham componentes

##void desenhar_nome(tipo_componente *comp)
Esta função desenha um texto simples e colorido. Ela é chamada pela função desenhar_interface(), e recebe o respectivo componente por referencia no parametro comp.

##void desenhar_quadrado(tipo_componente *comp)
Esta função desenha um quadrado colorido.