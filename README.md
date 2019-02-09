# Snaze
![](https://raw.githubusercontent.com/pabloufrn/Snaze/master/extra/preview.png)
### Sobre o projeto
Esse programa foi desenvolvido baseado em um trabalho de Linguagem de programação do Instituto Metrópole Digital, o algoritmo original
pode ser encontrado em https://github.com/henriquedavidufrn/snaze.
### Limitações
- O projeto carrega um arquivo mapcycle.txt que contém os nomes dos mapas e carrega o arquivo de mapa ao iniciar o level. O problema disso
é que esses arquivos são carregados todo vez que o jogador clicar no botão iniciar o jogo, uma correção disso será revisada em breve.
- O projeto está incompleto e será refeito.
### Melhorias planejadas
- [ ] Melhorar carregamento do mapas.
- [ ] Usar Hamiltonian path quando a IA detectar um destino "perigoso".
- [ ] Melhorar manuteabilidade do código do código.
- [ ] Criar um back-end totalmente indenpedente da interface de usuário. Assim o código poderia ser reutilizado até mesmo em outras
plataformas.
- [ ] Melhorar gráficos e colocar sons (inclusive o modo que o jogo se apresenta para o usuário).
- [ ] Criar o modo player vs IA.
- [ ] Criar servidor e cliente do jogo.
### Como compilar
Para compilar, eu recomendo usar o `cmake`. use o comando 
`cmake -G"Unix Makefiles" .`, depois use o comando `make`.
