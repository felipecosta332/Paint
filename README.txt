O que foi feito (o básico e as funcionalidades extras implementadas)?
Todas as primitivas gráficas exigidas, cônicas, redimensionamento, gráficos de polinômios e trigonometria, 
disco sólido e opaco, e filtro de escala de cinza.

O que não foi feito (caso não tenha sido possível implementar alguma funcionalidade)?
Interface gráfica, rotação de imagem, inversão de imagem, compressão e descompressão.

O que seria feito diferentemente (quando aprendemos à medida que vamos implementando, por vezes vemos que
podíamos ter implementado algo de forma diferente. Assim, esse tópico é para vocês refletirem sobre o que 
vocês aprenderam durante o processo que, se fossem fazer o mesmo projeto novamente, fariam diferente)?
Seria mais interessante não fazer a interface gráfica pela curva de aprendizado gigante e focar em
outras funcionalidades mais práticas e fáceis de implementar. Além de dedicar mais tempo ao projeto.

Como compilar o projeto, deixando explícito se foi utilizada alguma biblioteca externa que precise ser 
instalada, que versão e quais parâmetros extras são necessários para o compilador.?
Acesse a pasta src e compile com o seguinte comando:
gcc -o main main.c fileio.c draw.c vector.c text.c -lm
Em seguida execute o main normalmente:
./main

Em caso de duplas:
Identificação dos autores;
PAULO FELIPE COSTA DE PONTES
ENZO LOPES D'ANJOUR DE SOUZA

Contribuição de cada integrante no desenvolvimento do projeto (quem fez oquê).
PAULO: Funções de desenho, entrada e saída, manipulação de matrizes.
ENZO: Esboço de interface gráfica e versionamento.