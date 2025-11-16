planta(rosa, exterior).
planta(cactus, interior).
planta(lirio, exterior).

necesita(rosa, agua).
necesita(cactus, poca_agua).
necesita(lirio, agua).

ubicacion_ideal(X, Y) :- planta(X, Y).

% a) ¿Que consulta puede darme alguna planta que necesite agua?
% necesita(X,agua).
% b) ¿Que consulta me da la ubicación ideal de un cactus?
% ubi_ideal(cactus,Y).
% c) Defina una regla exteriores(Lista) que de en una lista todas las
% plantas de exterior. %

exteriores(Lista) :- findall(X,ubicacion_ideal(X,exterior),Lista).
