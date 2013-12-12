%Predicate to test if personA is connected with personB

isConnected(PersonA,PersonB):-connects(PersonA,PersonB,_);connects(PersonB,PersonA,_).

%Predicate to test if PersonA is colleague of PersonB

isColleague(PersonA,PersonB):-connects(PersonA,PersonB,1);connects(PersonB,PersonA,1).

%Predicate to test if PersonA is friend of personB

isFriend(PersonA,PersonB):-connects(PersonA,PersonB,2);connects(PersonB,PersonA,2).

%Predicate to test if PersonA is family of PersonB

isFamily(PersonA,PersonB):-connects(PersonA,PersonB,3);connects(PersonB,PersonA,3).
