:- module(player1,[ai_move/3]).
% Conecta el nombre 'ai_move' (que se exporta) con tu código 'movimiento_ia'
ai_move(Jugador, Tablero, Posicion) :-
    movimiento_ia(Jugador, Tablero, Posicion).

% nuestra estrategia para ganar es:
% Se reordenan las reglas para verificar primero las jugadas de
% mayor impacto y mas rapidas de calcular, como tomar el centro.

movimiento_ia(Jugador, Tablero, Posicion) :- movimiento_critico(Jugador, Tablero, Jugador, Posicion), !.
movimiento_ia(Jugador, Tablero, Posicion) :-
    cambiar_jugador(Jugador, Oponente),
    movimiento_critico(Oponente, Tablero, Jugador, Posicion), !.
movimiento_ia(_, Tablero, Posicion) :- tomar_centro(Tablero, Posicion), !.
movimiento_ia(Jugador, Tablero, Posicion) :- crear_trampa(Jugador, Tablero, Posicion), !.
movimiento_ia(_, Tablero, Posicion) :- tomar_esquina_vacia(Tablero, Posicion), !.
movimiento_ia(_, Tablero, Posicion) :- tomar_lado_vacio(Tablero, Posicion), !.
movimiento_ia(_, Tablero, Posicion) :- tomar_primera_casilla_vacia(Tablero, Posicion).

% logica de los movimientos

% 1 & 2. logica para ganar/bloquear
movimiento_critico(JugadorObjetivo, Tablero, _, Movimiento) :-
    combinacion_ganadora(Linea),
    revisar_linea(JugadorObjetivo, Tablero, Linea, Movimiento).

revisar_linea(J, Tablero, [Pos1, Pos2, Pos3], Pos1) :- nth1(Pos2, Tablero, J), nth1(Pos3, Tablero, J), nth1(Pos1, Tablero, ' ').
revisar_linea(J, Tablero, [Pos1, Pos2, Pos3], Pos2) :- nth1(Pos1, Tablero, J), nth1(Pos3, Tablero, J), nth1(Pos2, Tablero, ' ').
revisar_linea(J, Tablero, [Pos1, Pos2, Pos3], Pos3) :- nth1(Pos1, Tablero, J), nth1(Pos2, Tablero, J), nth1(Pos3, Tablero, ' ').

% 3. Tomar el centro
tomar_centro([_, _, _, _, ' ', _, _, _, _], 5).

% 4. Crear una trampa
% busca tomar esquinas opuestas si el centro es del oponente.
crear_trampa(J, [' ', _, _, _, Op, _, _, _, ' '], 1) :- cambiar_jugador(J, Op).
crear_trampa(J, [_, _, ' ', _, Op, _, ' ', _, _], 3) :- cambiar_jugador(J, Op).

% 5. Tomar una esquina vacia
tomar_esquina_vacia([' ', _, _, _, _, _, _, _, _], 1).
tomar_esquina_vacia([_, _, ' ', _, _, _, _, _, _], 3).
tomar_esquina_vacia([_, _, _, _, _, _, ' ', _, _], 7).
tomar_esquina_vacia([_, _, _, _, _, _, _, _, ' '], 9).

% 6. Tomar un lado vacio
tomar_lado_vacio([_, ' ', _, _, _, _, _, _, _], 2).
tomar_lado_vacio([_, _, _, ' ', _, _, _, _, _], 4).
tomar_lado_vacio([_, _, _, _, _, ' ', _, _, _], 6).
tomar_lado_vacio([_, _, _, _, _, _, _, ' ', _], 8).

% 7. Tomar la primera casilla vacia
% busca la primera posicion (Posicion) en el tablero (Tablero) que
% contenga un espacio (' ').
tomar_primera_casilla_vacia(Tablero, Posicion) :-
    nth1(Posicion, Tablero, ' ').

% predicados
combinacion_ganadora([1, 2, 3]). combinacion_ganadora([4, 5, 6]). combinacion_ganadora([7, 8, 9]).
combinacion_ganadora([1, 4, 7]). combinacion_ganadora([2, 5, 8]). combinacion_ganadora([3, 6, 9]).
combinacion_ganadora([1, 5, 9]). combinacion_ganadora([3, 5, 7]).

cambiar_jugador(x, o).
cambiar_jugador(o, x).
