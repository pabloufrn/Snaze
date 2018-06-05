# Screen Manager

Workflow

-- criar action para widget


--- criar propriedades para widget
-- focavel
-- clicavel

// nem todos tem essas propriedade, mas a screen tem responsabilidade de lidar com elas

--- atualizar membros de state
-- Todo state tem acesso a janela
-- Todo state tem acesso ao gerenciador de estados 

--- remover o render
-- passar a janela no init (se exepcionalmente o state precisar guardar a janela será um caso especial)
-- colocar drawable

--- criar estado close
-- sem acesso window.close ele apenas reseta os estados

--- guardar o score e as vidas
-- e ativar isso nos gatilhos do main game state

--- gatilho do level up
-- bastante importante para deixar o jogo legal

--- criar a HUD
-- será uma passada desenhar a view da board
-- depois uma passada para desenhar a view da hud

--- Velocidade do jogo
-- o jogo vai ficando mais interessante

--- intelegencia artificial
-- hummm

--- Problemas previstos
-- A IA pode atrasar o tempo do jogo.
. fazer com que a IA trabalhe em paralelo
-- A IA pode não ter se decidido no tempo correto
. Criar decisão para evitar isso

--- player vs IA
-- programar recálculo do caminho na IA
-- A IA tem a vantagem

---- Final
--- colocar a cobra fora da board
-- o game vai ficar mais fluido
--- melhorar a bibioteca
-- a base já está crescendo bastante
