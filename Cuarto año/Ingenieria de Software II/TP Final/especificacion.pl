:- dec_p_type(max_peso_da(int)).
max_peso_da(X) :- X >=0.


:- dec_type(sx,enum([hembra,macho])).
:- dec_type(sz,enum([chico,medio,grande])).

:- dec_type(pr,[nombre,raza,sx,sz]).

:- dec_type(ag,set([[fecha,hora],set(pr)])).

:- dec_p_type(sistInv(ag)).
sistInv(Agenda) :-
  ran(Agenda,R) & {} nin R & dec(R,set(set(pr))).
  
:- dec_p_type(sistInit(ag)).
sistInit(Agenda) :-
  Agenda = {}.
    
:- dec_p_type(agregarPerroSalidaOk(set(raza),int,ag,ag,pr,fecha,hora)).
agregarPerroSalidaOk(Razas_Peligrosas,Max_Peso,Agenda,Agenda_,P_i,F_i,H_i) :-
  dec([Y,Y2,C1,C2,C3],set(pr)) &
  [[F_i,H_i],Y] in Agenda & P_i nin Y &
  P_i=[P_i_N,P_i_R,P_i_S,P_i_SZ] & dec(P_i_N,nombre) & dec(P_i_R,raza) & dec(P_i_S,sx) & dec(P_i_SZ,sz) &
  (P_i_R nin Razas_Peligrosas or foreach(P in Y,P_R nin Razas_Peligrosas) & P=[P_N,P_R,P_S,P_SZ] & dec(P,pr) & dec(P_N,nombre) & dec(P_R,raza) & dec(P_S,sx) & dec(P_SZ,sz)) & 
  foreach(P in Y,P_i_S=P_S) &
  [[F_i,H_i],Y2] in Agenda_ &
  subset(C1,Y2) & foreach(P in C1,P_SZ=chico) &
  subset(C2,Y2) & foreach(P in C2,P_SZ=medio)  &
  subset(C3,Y2) & foreach(P in C3,P_SZ=grande) &
  size(C1,N1) & size(C2,N2) & size(C3,N3) & max_peso_da(Max_Peso) & dec([N1,N2,N3],int) &
  (N1 + N2*2 + N3*3) < Max_Peso &
  un(Y,{P_i},Y2) &
  oplus(Agenda,{[[F_i,H_i], Y2]},Agenda_).

:- dec_p_type(agregarPerroSalidaTurnoNuevoOk(int,ag,ag,pr,fecha,hora)).
agregarPerroSalidaTurnoNuevoOk(Max_Peso,Agenda,Agenda_,P_i,F_i,H_i) :-
  dec([Y,Y2,C1,C2,C3],set(pr)) & 
  dom(Agenda,D) & [F_i,H_i] nin D & dec(D,set([fecha,hora])) &
  [[F_i,H_i],Y2] in Agenda_ &
  Y2={P_i} &
  subset(C1,Y2) & foreach(P in C1,P_SZ=chico) & P=[P_N,P_R,P_S,P_SZ] & dec(P,pr) & dec(P_N,nombre) & dec(P_R,raza) & dec(P_S,sx) & dec(P_SZ,sz) &
  subset(C2,Y2) & foreach(P in C2,P_SZ=medio) &
  subset(C3,Y2) & foreach(P in C3,P_SZ=grande) &
  size(C1,N1) & size(C2,N2) & size(C3,N3) & max_peso_da(Max_Peso) & dec([N1,N2,N3],int) &
  (N1 + N2*2 + N3*3) < Max_Peso &
  oplus(Agenda,{[[F_i,H_i], {P_i}]},Agenda_).

:- dec_p_type(agregarPerroSalidaYaExiste(ag,ag,pr,fecha,hora)).
agregarPerroSalidaYaExiste(Agenda,Agenda_,P_i,F_i,H_i) :-
  dec(Y,set(pr)) &
  [[F_i,H_i],Y] in Agenda & P_i in Y &
  Agenda = Agenda_.

:- dec_p_type(agregarPerroSalidaConflictoSexo(ag,ag,pr,fecha,hora)).
agregarPerroSalidaConflictoSexo(Agenda,Agenda_,P_i,F_i,H_i) :-
  dec(Y,set(pr)) & P_i=[P_i_N,P_i_R,P_i_S,P_i_SZ] & dec(P,pr) & dec([P_N,P_i_N],nombre) & dec([P_R,P_i_R],raza) & dec([P_S,P_i_S],sx) & dec([P_SZ,P_i_SZ],sz) &
  [[F_i,H_i],Y] in Agenda & P_i nin Y &
  P in Y & P=[P_N,P_R,P_S,P_SZ] &
  P_i_S neq P_S &
  Agenda = Agenda_.

:- dec_p_type(agregarPerroSalidaConflictoRaza(set(raza),ag,ag,pr,fecha,hora)).
agregarPerroSalidaConflictoRaza(Razas_Peligrosas,Agenda,Agenda_,P_i,F_i,H_i) :-
  dec(Y,set(pr)) & P_i=[P_i_N,P_i_R,P_i_S,P_i_SZ] & dec(P,pr) & dec([P_N,P_i_N],nombre) & dec([P_R,P_i_R],raza) & dec([P_S,P_i_S],sx) & dec([P_SZ,P_i_SZ],sz) &
  [[F_i,H_i],Y] in Agenda & P_i nin Y &
  P_i_R in Razas_Peligrosas &
  P in Y & P_R in Razas_Peligrosas &
  Agenda = Agenda_.

:- dec_p_type(agregarPerroSalidaMuyPesado(int,ag,ag,pr,fecha,hora)).
agregarPerroSalidaMuyPesado(Max_Peso,Agenda,Agenda_,P_i,F_i,H_i) :-
  dec([Y,Y2,C1,C2,C3],set(pr)) &
  [[F_i,H_i],Y] in Agenda & P_i nin Y &
  un(Y,{P_i},Y2) &
  P=[P_N,P_R,P_S,P_SZ] & dec(P,pr) & dec(P_N,nombre) & dec(P_R,raza) & dec(P_S,sx) & dec(P_SZ,sz) &
  subset(C1,Y2) & foreach(P in C1,P_SZ=chico) &
  subset(C2,Y2) & foreach(P in C2,P_SZ=medio) &
  subset(C3,Y2) & foreach(P in C3,P_SZ=grande) &
  size(C1,N1) & size(C2,N2) & size(C3,N3) & max_peso_da(Max_Peso) & dec([N1,N2,N3],int) &
  (N1 + N2*2 + N3*3) >= Max_Peso &
  Agenda = Agenda_.

:- dec_p_type(agregarPerroSalida(set(raza),int,ag,ag,pr,fecha,hora)).
agregarPerroSalida(Razas_Peligrosas,Max_Peso,Agenda,Agenda_,P_i,F_i,H_i) :-
  agregarPerroSalidaOk(Razas_Peligrosas,Max_Peso,Agenda,Agenda_,P_i,F_i,H_i) 
  or
  agregarPerroSalidaTurnoNuevoOk(Max_Peso,Agenda,Agenda_,P_i,F_i,H_i)
  or
  agregarPerroSalidaYaExiste(Agenda,Agenda_,P_i,F_i,H_i) 
  or
  agregarPerroSalidaConflictoRaza(Razas_Peligrosas,Agenda,Agenda_,P_i,F_i,H_i) 
  or
  agregarPerroSalidaConflictoSexo(Agenda,Agenda_,P_i,F_i,H_i) 
  or
  agregarPerroSalidaMuyPesado(Max_Peso,Agenda,Agenda_,P_i,F_i,H_i).

:- dec_p_type(quitarPerroSalidaOk(ag,ag,pr,fecha,hora)).
quitarPerroSalidaOk(Agenda,Agenda_,P_i,F_i,H_i) :-
  dec([Y,Y2],set(pr)) &
  [[F_i,H_i],Y] in Agenda & P_i in Y & %& pfun(Agenda) 
  Y neq {P_i} &
  diff(Y,{P_i},Y2) &
  oplus(Agenda,{[[F_i,H_i], Y2]},Agenda_).


:- dec_p_type(quitarPerroSalidaYTurnoOk(ag,ag,pr,fecha,hora)).
quitarPerroSalidaYTurnoOk(Agenda,Agenda_,P_i,F_i,H_i) :-
  dec(Y,set(pr)) &
  [[F_i,H_i],Y] in Agenda & P_i in Y & %& pfun(Agenda) 
  Y = {P_i} &
  dares({[F_i,H_i]},Agenda,Agenda_).

:- dec_p_type(turnoNoExiste(ag,ag,fecha,hora)).
turnoNoExiste(Agenda,Agenda_,F_i,H_i) :-
  dec(D,set([fecha,hora])) & 
  dom(Agenda,D) & [F_i,H_i] nin D & %& pfun(Agenda) 
  Agenda = Agenda_.

:- dec_p_type(quitarPerroSalidaNoExistePerro(ag,ag,pr,fecha,hora)).
quitarPerroSalidaNoExistePerro(Agenda,Agenda_,P_i,F_i,H_i) :-
  dec(Y,set(pr)) &
  [[F_i,H_i],Y] in Agenda & %& pfun(Agenda) 
  P_i nin Y &
  Agenda = Agenda_.

:- dec_p_type(quitarPerroSalida(ag,ag,pr,fecha,hora)).
quitarPerroSalida(Agenda,Agenda_,P_i,F_i,H_i) :-
  quitarPerroSalidaOk(Agenda,Agenda_,P_i,F_i,H_i)
  or
  quitarPerroSalidaYTurnoOk(Agenda,Agenda_,P_i,F_i,H_i)
  or
  turnoNoExiste(Agenda,Agenda_,F_i,H_i)
  or
  quitarPerroSalidaNoExistePerro(Agenda,Agenda_,P_i,F_i,H_i).

:- dec_p_type(perrosAPasearOk(ag,fecha,hora,set(pr))).
perrosAPasearOk(Agenda,F_i,H_i,Prs_o) :-
  [[F_i,H_i],Prs_o] in Agenda. %& pfun(Agenda).

:- dec_p_type(perrosAPasear(ag,fecha,hora,set(pr))).
perrosAPasear(Agenda,F_i,H_i,Prs_o) :-
  perrosAPasearOk(Agenda,F_i,H_i,Prs_o)
  or
  turnoNoExiste(Agenda,Agenda,F_i,H_i).