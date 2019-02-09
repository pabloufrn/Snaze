
# Snaze Game
![](https://raw.githubusercontent.com/pabloufrn/Snaze/master/extra/preview.png)
Essa é uma implementação do clássico jogo da cobrinha com uma IA para resolver o caminho e pegar as maçãs, 
a implementação foi feita em C++ com a biblioteca SFML para a parte gráfica. O projeto foi feito em dupla, sendo eu
o responsável pela parte gráfica - no entanto acabei fazendo a própria versão em paralelo (mais informações no repositório).

# Desafios 
Estou escrevendo isso bem depois da implementação, mas lembro-me de ter usado o código do Conway's Life game - que também se encontra em meu github, porém eu não tinha feito máquina de estado no outro projeto, assim o desafio principal ser faze-la. Algumas leitura e vídeos me ajudaram a entender como são feitas as transições e o armazenamento de dados do jogo, sendo que para essa versão eu optei por armazenar apenas o level atual - também não fiz uma estrutura para os dados (isso seria o padrão), pois eu sempre uso uma coisa apenas depois de entender a real necessidade. Além disso, agora eu estava lidando com algo que poderia não caber na tela, uma das opções era 'espremer' os gráficos e a outro era mover a camera pelo cenário, eu optei pela segunda.  
Algumas coisas não ficaram resolvidas, como por exemplo: Como o movimento da cobrinha era sempre de bloco em bloco sem frames entre a transição, o movimento da camêra ficou muito brusca. O mesmo problema que ocorria com jogos antigos; e  
O jogo carrega os mapas sempre que a partida é iniciada, melhorar essa implentação com alguma alternativa coêrente seria o melhor.  
Todos esses problemas podem ser corrigidos em uma versão futura.  

# Como usar
Depois de compilado ou baixado, você pode com `./snaze` ou clicando duas 
vezes no arquivo;
