## **Active Speakers/Amplifiers Selector (SAS-28)**

### Introdução
O **Active Speakers/Amplifiers Selector** (SAS-28) é um projeto de um comutador ativo, que recebe saídas de caixas de som de até oito amplificadores de áudio estéreo para até dois pares de caixas, possibilitando que se tenha simultaneamente, conforme seleção, dois amplificadores comutados, cada um, com um par de caixas. Ainda, é possível associar os dois pares de caixas a um único amplificador.

A concepção do projeto permite expansão tanto do número de amplificadores, como no número de caixas. Essa configuração inicial se deu em decorrência de uma demanda particular, onde se tinha disponíveis dois pares de caixas e pelo menos oito amplificadores. Como desejava nas audições, hora ouvir um dos amplificadores, ora outro, o comutador me pareceu a solução mais prática para não ter  que ficar desligando/religando fiações.

Projetar um comutador para atender a esse objetivo é simples e relativamente barato se sua arquitetura for do tipo passiva, isto é, usando apenas chaves de comutação, interligação de fios e bornes. O mais complicado nos dias de hoje é encontrar chaves rotativas, cujos contatos, suportem as altas correntes das saídas de caixas dos amplificadores.

Uma segunda solução seria continuar usando chaves rotativas, estas para baixa corrente, porém, apenas para comutar relés e estes sim, suportariam as altas correntes da comutação/uso. Também é uma solução simples, barata e fácil de construir.

A terceira solução que veio a tona, consiste de uma arquitetura de maior complexidade, de custo superior em relação as soluções anteriores e com algumas perfumarias. Apesar de possuir alto custo em relação a sua funcionalidade, essa terceira solução, cujo projeto será esboçado a seguir, teve como principal motivação, o aprendizado no manuseio dos componentes a serem utilizados no projeto. Basicamente, os requisitos do projeto são:

- Ser 100% ativo (para o termo ativo propriamente, o mais correto seria usar semicondutores na comutação, mas não é o caso aqui);
- Utilizar relés para compor a matriz de comutação de amplificadores/caixas e que suportem potências de até 100 WRMS;
- Utilizar lógica de controle usando micro controlador (arduino mega);
Possuir indicadores visuais da operações  e/ou estado, incluindo VU Meter;
Utilizar chassis, painel, fonte e chaves do **Tuner Gradiente Model 9** (produto de fabricação brasileiro da década de 80) para acomodar os componentes e controles do comutador.

### Funcionalidades do SAS-28
Nesta seção serão apresentadas as principais funcionalidades do SAS-28, sempre as associando aos comandos do painel de controle (ou vice-versa), o quais serão usados integralmente os já existentes no chassis do tuner supracitado. A figura 1 (clique na imagem para ver a versão em alta resolução) a seguir representa um esboço de layout que reflete o painel físico do tuner gradiente M9, cuja serigrafia e área do dial foram modificadas visando o novo produto e que será base da explanação que se segue. O arquivo “fonte” no formato do Adobe Photoshop (cada item é um layer) e Corel Draw (muito usado como arte para serigrafia) para quem desejar se aventurar no projeto, portanto, refazer a serigrafia aproveitando o painel do M9, poderá baixa-lo AQUI.

[![SAS-28 painel](/images/sas28_panel.jpg)]((/images/sas28_panel.jpg))
![SAS-28 painel](/images/sas28_panel.jpg)
![SAS-28 painel](/images/sas28_panel_natural.jpg)
<center>**Figura 1: Layout do painel do SAS-28 com o uso do painel do Tuner Gradiente Model 9**</center>

As funcionalidades a seguir estão associadas ao botões/controles e displays presentes no painel do SAS-28, devendo, portanto, relacioná-las. Também não foi seguida nenhuma ordem física dos comandos/displays no painel.

