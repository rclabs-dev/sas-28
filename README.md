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

**a) Botão “POWER”**

Um pouco óbvio, mas esse botão tem como função desligar/ligar o SAS-28, devendo ser previamente verificado se o equipamento está devidamente chaveado para 110 ou 220 volts em chave especifica presente no painel traseiro.  E uma simples chave do tipo pushbuttom com retenção e será usada a mesma do M9.

**b) Controle “SP/AMP SELECTOR”**

O SAS-28 foi especificado para operar com dois pares de caixas, sendo que cada par poderá ser comutado em uma das oito entradas de amplificadores disponíveis, distintamente.

Esse comando é um controle do tipo “rotary encoder” com “push buttom”, ou seja, ele pode ser girado infinitamente para direita, como para esquerda e ainda, ao ser pressionado, aciona um contato. Ao girar esse controle, é gerado um pulso em seus terminais (um abrir e fechar de chave), assim, há um pino central (ligado a GND ou VCC conforme projeto) e dois outros que receberão o primeiro pulso conforme sentido de rotação.

No caso do SAS-28, quando girado para esquerda, aparecerá no display de sete segmentos denominado  “SP/AMP SELECTOR” um valor sequencial de 1 a 8 e ainda o carácter “d”, sendo que cada valor de 1 a 8 corresponde a um dos amplificadores ligados ao SAS-28 e com associação direta para o par de caixas “SP 1″, com  exceção  da posição“d” (de Deactivate ou Desativar)  que será explicado ao final desta alínea.

Assim, ao ser girado, o display irá mudando o seu valor sequencialmente de 1 a 9 e “d”, cuja seleção ocorrerá com o pressionamento do push buttom, ou seja, se o push bottom for pressionado quando o display estiver indicando o numeral 5, essa ação chaveia o amplificador que se encontra ligado na entrada 5 ao par de caixas “SP 1″.

A comutação ocorre para ambos os canais do amplificador, esquerdo e direito e se ao selecionar um amplificador que já se encontra comutado para o outro par de caixas, automaticamente a comutação do par adjacente é desfeito e é executado a nova comutação.

Processo análogo ocorre se o comando for  girado para a direita, porém a associação ocorrerá com o par de caixas “SP 2″. Observa-se que independente da última seleção, a comutação sempre ocorrerá para os dois pares de caixas (SP1/SP2) conforme indicam os displays de sete segmentos (“SP/AMP SELECTOR”).

Se o push bottom for pressionado estando os pares de caixas selecionados para um mesmo amplificador, fará com que o par de caixas SP1 fique em paralelo com o par SP2 conectando-as no amplificador selecionado. Como o ambos pares de caixas passam a ter uma ligação do tipo paralelo, deve-se observar a impedância gerada nessa associação de modo que não esteja inferior ao suportado pelo amplificador.

No caso do pressionamento na letra “d”, fará com que a comutação seja desfeita para aquele par de caixas, ou seja, é um modo de desligar o par de caixas.

A comutação selecionada para os dois pares de caixas e amplificadores são sempre gravadas em memória não volátil de modo que ao religar o SAS-28, a última configuração em uso seja restabelecida.

**c) Botão “LOCK SEL”**

Esse botão do tipo on/off tem como objetivo bloquear o comando “SP/AMP SELECTOR”, evitando comutações indesejáveis. Foi só para aproveitar o botão físico do M9.

**d) Controle “DISPLAY VIEW”**

Esse controle é composto de dois botões denominados “SP/AMP SEL” e “VU”. Quando um dos botões é pressionado, automaticamente o outro é liberado.

Foi contemplado no SAS-28 dois displays de 2 linhas e 16 caracteres (fundo preto com caracteres em vermelho), cada um se relacionando com as funções associadas a cada par de caixas.

Cada display possui duas funções, isto é, se pressionado o botão “SP/AMP SEL” será apresentado as informações da atual comutação entre amplificadores e os pares de caixas. O par de caixas “SP 1″ está para display da esquerda e “SP 2″ para o display da direita. Se pressionado o botão “VU”, ambos os display atuarão com um VU Meter, cada um para um par de caixas.

**e) Botão “DISPLAY”**

Esse botão do tipo on/off tem como função ligar/desligar todos os display do SAS-28. Poderá ser útil em audições noturnas em que o brilho das luzes pode incomodar. A exceção fica por conta do display esquerdo que terá o segmento do ponto acesso constantemente, sendo uma forma de informar que equipamento está ligado. Também foi para aproveitar o botão físico do M9.

**f) Controle “VU SENSITIVITY”**

Esse controle é composto de dois botões do tipo low/high denominados “SP PAIR1″ e “SP PAIR2″. Como os displays também terão a função de VU Meter, esse controle permite aumentar ou diminuir em dois níveis sua sensibilidade, onde na posição “LOW” o VU estará menos sensível, enquanto na posição “HIGH” mais sensível, sendo esse último caso adequado para baixos níveis de potência. Não foi pensando em valores de atenuação em dB ou até mesmo potência WRMS/Pico, mas apenas uma facilidade que poderá ser útil.

### A eletrônica do SAS-28

Concluído a explanação sucinta das funcionalidades do SAS-28, trataremos agora da parte eletrônica do SAS-28, que inclui o diagrama eletrônico, placas de circuito impresso e os componentes a serem utilizados.

O circuito eletrônico do SAS-28 é composto dos seguintes módulos:

**a) Fonte de alimentação**

O tuner Gradiente Model 9, cujo chassis, painel e outros itens serão usados para acomodar o SAS-28 possui uma fonte com regulador série de 13 VCC. Essa tensão é ideal para a alimentação do módulo de comutação por conta dos relés, cujas bobinas são para 12 VCC, como para o arduino (módulo de controle) que também tem como recomendação ser alimentado entre 7 e 15 volts. Em verdade o arduino funciona com 5 VCC, cujo regulador encontra se na própria placa. Os 5 volts providos pelo arduino serão utilizados também para alimentar os displays.

A fonte do M9 fica na PCI 240 que a mesma placa que acomoda todas as chaves do produto, portanto, será 100% aproveitada, mas claro apenas a fonte e a parte do circuito impresso de ligação das chaves, onde as trilhas serão rompidas do restante dos circuito que compõe essa placa.

**b) Módulo de comutação**

O módulo de comutação é a parte do SAS-28 que recebe as saídas de caixas dos oito amplificadores (AMPxL/AMPxR) e os comuta entre os dois pares de caixas acústicas (SPxL/SPxR). O download do diagrama elétrico/eletrônico deste módulo poderá ser baixado no formato PDF clicando AQUI, ou se preferir no formato do software Diptrace clicando AQUI.

Conforme circuito, o módulo de comutação é composto basicamente por relés, onde foram usados 32 (U1 a U32) cuja bobina é para 12 VCC e contatos com capacidade para suportar até 7 amperes. Nesse caso, a capacidade de corrente dos contatos estar diretamente associado à potência dos amplificadores. Considerou-se que um relé hermético de 7A poderá suportar amplificadores até 100 watts RMS, que é o propósito desse projeto. Na prática suporta até potências maiores, mas a vida útil fica reduzida. Relés que suportem maior corrente podem ser usados, permitindo assim, o uso de amplificadores com potências superiores ao supracitado.

Dos 32 relés utilizados, são usados dois para cada canal de amplificador. Ambos os relés permitem uma via dupla de comutação até os dois pares de caixas, distintamente, sem riscos de mais de um amplificador aplicar sinal no mesmo par de caixas (responsabilidade do módulo de controle). Ainda, os relés são comutados aos pares, ou seja, o comando que comuta o relé do canal esquerdo é o mesmo que comuta do canal direito de um respectivo amplificador. Assim, foram necessários apenas 16 comandos de relés, os quais são provenientes do módulo de controle (arduino mega).

As saídas do módulo de controle (arduino) são de baixa potência, sendo necessário o uso de drivers (R1/Q1 a R16/Q16) e como os relés são energizados em pares, apenas um diodo contra tensão/corrente reversa foi usado visando a proteção dos drivers. Em relação a outras proteções, tal como fusíveis, componentes acopladores contra indutâncias parasitas e mitigadores de faiscamento nos contatos dos relés não foram previstos, porém, possível de serem adicionados.

Para acomodar os componentes deste módulo, uma placa de circuito impresso dupla face foi desenvolvida, onde as conexões dos bornes de amplificadores/caixas instalados no painel traseiro do M9 chegam por fios de bitola de 1,5mm até a placa, cujas conexões usam terminais FASTON. Já os sinais de controle dos relés chegam através de um conector tipo HEADER (J1). Assim, observa-se que todas as conexões com a placa de comutação traz praticidade para o processo de conexão/desconexão, item esse, importante no caso de manutenção.

O layout do circuito impresso lado cobreado e dos componentes no formato PDF e em Diptrace podem ser baixados AQUI.

**c) Módulo de Controle**

O módulo de controle do SAS-28 tem como base um microcontrolador ora provido pela placa Arduino mega (não é propósito deste documento abordar detalhes do arduino, devendo para tal, consultar o site do produto clicando AQUI).

No SAS-28 o arduino é responsável por interfacear o Rotary Encoder, ler o estado dos botões “LOCK SEL”, “DISPLAY VIEW / VU” e “DISPLAY”; controlar  ambos os displays LCD e de sete segmentos; acionar todos os relés envolvidos no processo de comutação do áudio entre amplificadores de 1 à 8 e os dois pares de caixas de som (SP1/SP2) através de suas entradas/saídas digitais.

Duas entradas analógicas são responsáveis pelo VU Meter que recebe tensões que variam de 0 a 5 VCC e que correspondem ao sinal de áudio proveniente do Módulo VU Meter.

A tabela abaixo representa o mapeamento dos pinos utilizados no arduino para atender o interfaceamento acima citado.

Pino | Modo | Função
--- | --- | ---
*Still* | `renders` | **nicely**
1 | 2 | 3

O diagrama eletrônico que envolve os displays, Rotary Encoder e arduino podem ser visto no formato PDF AQUI, ou no formato do software Diptrace AQUI. Não foi produzido nenhuma placa de circuito impresso, sendo a montagem feita sobre placas pré furadas, isto é, daquelas parecidas com protoboard.

A listagem 1 a seguir apresenta o código do “firmware” que fará o controle do SAS-28. Como o código está comentado quanto a suas funcionalidades, foi dispensado quaisquer comentários neste texto. Caso queira baixa-lo, clique AQUI.
