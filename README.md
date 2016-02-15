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

![SAS-28 painel](/images/sas28_panel.jpg)
![SAS-28 painel](/images/sas28_panel_natural.jpg)
<p align="center">**Figura 1: Layout do painel do SAS-28 com o uso do painel do Tuner Gradiente Model 9**</p>

As funcionalidades a seguir estão associadas ao botões/controles e displays presentes no painel do SAS-28, devendo, portanto, relacioná-las. Também não foi seguida nenhuma ordem física dos comandos/displays no painel.

1. **Botão “POWER”**
Um pouco óbvio, mas esse botão tem como função desligar/ligar o SAS-28, devendo ser previamente verificado se o equipamento está devidamente chaveado para 110 ou 220 volts em chave especifica presente no painel traseiro.  E uma simples chave do tipo pushbuttom com retenção e será usada a mesma do M9.

2. **Controle “SP/AMP SELECTOR”**
O SAS-28 foi especificado para operar com dois pares de caixas, sendo que cada par poderá ser comutado em uma das oito entradas de amplificadores disponíveis, distintamente.

Esse comando é um controle do tipo “rotary encoder” com “push buttom”, ou seja, ele pode ser girado infinitamente para direita, como para esquerda e ainda, ao ser pressionado, aciona um contato. Ao girar esse controle, é gerado um pulso em seus terminais (um abrir e fechar de chave), assim, há um pino central (ligado a GND ou VCC conforme projeto) e dois outros que receberão o primeiro pulso conforme sentido de rotação.

No caso do SAS-28, quando girado para esquerda, aparecerá no display de sete segmentos denominado  “SP/AMP SELECTOR” um valor sequencial de 1 a 8 e ainda o carácter “d”, sendo que cada valor de 1 a 8 corresponde a um dos amplificadores ligados ao SAS-28 e com associação direta para o par de caixas “SP 1″, com  exceção  da posição“d” (de Deactivate ou Desativar)  que será explicado ao final desta alínea.

Assim, ao ser girado, o display irá mudando o seu valor sequencialmente de 1 a 9 e “d”, cuja seleção ocorrerá com o pressionamento do push buttom, ou seja, se o push bottom for pressionado quando o display estiver indicando o numeral 5, essa ação chaveia o amplificador que se encontra ligado na entrada 5 ao par de caixas “SP 1″.

A comutação ocorre para ambos os canais do amplificador, esquerdo e direito e se ao selecionar um amplificador que já se encontra comutado para o outro par de caixas, automaticamente a comutação do par adjacente é desfeito e é executado a nova comutação.

Processo análogo ocorre se o comando for  girado para a direita, porém a associação ocorrerá com o par de caixas “SP 2″. Observa-se que independente da última seleção, a comutação sempre ocorrerá para os dois pares de caixas (SP1/SP2) conforme indicam os displays de sete segmentos (“SP/AMP SELECTOR”).

Se o push bottom for pressionado estando os pares de caixas selecionados para um mesmo amplificador, fará com que o par de caixas SP1 fique em paralelo com o par SP2 conectando-as no amplificador selecionado. Como o ambos pares de caixas passam a ter uma ligação do tipo paralelo, deve-se observar a impedância gerada nessa associação de modo que não esteja inferior ao suportado pelo amplificador.

No caso do pressionamento na letra “d”, fará com que a comutação seja desfeita para aquele par de caixas, ou seja, é um modo de desligar o par de caixas.

A comutação selecionada para os dois pares de caixas e amplificadores são sempre gravadas em memória não volátil de modo que ao religar o SAS-28, a última configuração em uso seja restabelecida.

3. **Botão “LOCK SEL”**

Esse botão do tipo on/off tem como objetivo bloquear o comando “SP/AMP SELECTOR”, evitando comutações indesejáveis. Foi só para aproveitar o botão físico do M9.

