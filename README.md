# Trabalho 3 - Luís Henrique Chesani
## Sua missão em RU invaders é derrotar os tios do RU e avançar o máximo possível para resgatar seus companheiros cachorros que foram pegos pelo RU.

## Como jogar

### Comandos
  - Movimento: 'A' move para a esquerda e 'D' move para a direita.
  - Espaço ' ' atira com a arma atual.
  - '2' Alterna para a arma especial.
  - '1' Altera para a arma base.
  - F3 liga/desliga o modo de debug, que exibe o fps atual e a velocidade relativa atual.
 
 ### Gameplay
  - Você começa com 3 vidas, são exibidas no canto superior direito.
  - Periodicamente, nascem inimigos que andam em sua direção, eles ficam cada vez mais fortes e atiram em você.
  - Ao levar dano por contato ou projétil de um inimigo, você leva 1 de dano.
  - Ao encostar em uma parede, leva 1 de dano e retorna ao centro da tela.
  - Ao levar dano, você ganha um pequeno tempo de ivulnerabilidade.
  - Periodicamente, caem caixas com armas especiais, pegue elas para juntar a arma.
  - A pontuação é exibida no centro superior da tela, sendo incrementada por tempo vivo, assim como por inimigos abatidos, inimigos mais fortes geram mais pontos.

### Armas Especiais
Ao ativar uma arma especial, você tem determinado tempo de uso, a barra exibida no canto superior esquerdo demonstra esse tempo.
Ao voltar para a arma base, você perde a arma especial.
As armas especiais são:

- Glock : Possui dano aumentado em relação a arma base, assim como atira muito mais rápido.
- Cajado e chapéu de mago: Lança uma poderosa magia de disparo único que aniquila todos ao seu alcance (metade superior da tela).
- Espada: Dispara uma onda de choque que causa um dano enorme aos inimigos atingidos.


## Descrição Técnica

### Paredes
- São estruturas geradas por curvas de Bezier cúbicas com 4 pontos de controle.
- São gorduchas pois na hora de plotar plotei (x+i, y+i).
- São renderizadas aos poucos, e na mesma velocidade deleta os pontos foras de visão.
- Hitbox baseada em retas entre os pontos de controle.

### Hitbox
- Como no caso das paredes, todas as colisões são baseadas em retas.
- É tomada como base o cálculo de intersecção de retas não-infinitas.
- Possui muitos For's aninhados, mas o desempenho ficou bem melhor do que o esperado.

### Arquivos gerais
- Classe de frames do professor, velocidade relativa é 1/fps.
- Classe abstrata para armas, projeteis, caixas e entidades, com suas derivações.
- Game manager que bom, gerencia o jogo.
- Classe BMP do professor, criei uma função para plotar o .bmp.
- Utils contém algumas estruturas e funções úteis, como a intersecção de retas, retas e uma simplificação da playAudio.



### Requisitos

#### Básicos
- Desenha um cenário com pelo menos 10x a altura. (infinito > 10x altura).
- Curvas de Bezier utilizadas.
- Nave pode disparar contra inimigos e vice-versa.
- Tem um placar de pontuação no centro superior da tela.
- Velocidades e cooldowns respeitam o fps.
- Feito em windows.

#### Extras
- Rajadas com efeitos especiais bonitos (Glock, Magia, Espada).
- Inimigos que se movem com base em IA (meio amplo isso aqui, mas acho que andar na direção do player parece inteligente '-').
- Os inimigos tem munições que são atiradas na direção do player.
- Power Ups para disparos especiais (3).
- Uso de Bmps.
- Uso de sons.
- Aspecto visual.
- Inimigos mais fortes conforme o tempo.
- Utilização de curvas de Bezier também em um projétil.
- Definição de hitbox genéricas que podem ser atribuidas a qualquer formato.
- (Otimização vale bônus ?), acho que fiz um bom trabalho nisso.
