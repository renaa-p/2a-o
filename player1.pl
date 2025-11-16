:- module(player1,[ai_move/3]).
:- use_module(library(random)).

% Set AIs moves to random empty spaces or human input
ai_move(_, Board, Pos):-
    random_move(Board, Pos).

% Some simple input predicates
random_move([' ',' ',' ',' ',' ',' ',' ',' ',' '],5).
random_move(Board, Pos):-
    findall(Temp, (nth1(Temp, Board, ' ')), Moves),
    random_member(Pos, Moves),
    format('RNGesus ha elegido la casilla ~w~n', [Pos]),!.
