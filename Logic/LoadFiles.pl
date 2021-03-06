% 
% Loads all files necessary for Logic module
%

% loads tag Semantics definitions
:- compile('TagSemantics.pl').

% loads knowledge base
:- compile('KnowledgeBase.pl').

% loads basic basic predicates
:- compile('BasicPredicates.pl').

% loads graph search algorittms
:- compile('GraphSearchAlgorithms.pl').

% loads word base
:- compile('WordBase.pl').

% loads the hangman Logic
:- compile('h-off.pl').
