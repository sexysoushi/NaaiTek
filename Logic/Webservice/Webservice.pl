%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Libraries and compiles
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% prolog server
:- use_module(library(http/thread_httpd)).
:- use_module(library(http/http_dispatch)).
:- use_module(library(http/http_parameters)).

% supporting json
:- use_module(library(http/json)).
:- use_module(library(http/json_convert)).
:- use_module(library(http/http_json)).

% needed compiles
:- compile('../LoadFiles.pl').



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Declaration of API calls
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% test request
:- http_handler(root(give_me_json), give_me_json, []).          

% request for depth search on graph
:- http_handler(root(depth_search), depth_search, []).

% request for breath search on graph
:- http_handler(root(breadth_search), breadth_search, []).

% request for branch and bound search on graph
:- http_handler(root(branch_and_bound), branch_and_bound, []).

% request for create connection
:- http_handler(root(create_connection), create_connection, []).

% request for remove connection
:- http_handler(root(remove_connection), remove_connection, []).

% request for update connection strenght
:- http_handler(root(update_connection_strenght), update_connection_strenght, []).

% request for add connection tag
:- http_handler(root(add_connection_tag), add_connection_tag, []).

% request for remove connection tag
:- http_handler(root(remove_connection_tag), remove_connection_tag, []).

% request for get nodes
:- http_handler(root(get_nodes), get_nodes, []).

% request for get paths
:- http_handler(root(get_paths), get_paths, []).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Implementaion
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% initiates server at given port
server(Port) :-                                         
        http_server(http_dispatch, [port(Port)]).


% creating a json object
:- json_object path(path:list, status:atom).
:- json_object message(details:atom, status:atom).
:- json_object nodes(nodes:list, status:atom).

:- json_object allpaths(paths:list, status:atom).
:- json_object paths(user1:atom, user2:atom, connection:number, tags:list).

%test handler
%handle(Request) :-
        %http_read_json(Request, JSONIn),
        %json_to_prolog(JSONIn, PrologIn),
        %<compute>(PrologIn, PrologOut),                % application body
        %prolog_to_json(PrologOut, JSONOut),
        %prolog_to_json(circle(coord(3, 5)), JSON_Object),
        %reply_json(JSON_Object).


% test request
give_me_json(_Request) :-
                %http_parameters(_Request, [name(Module, [])]),                                 
        prolog_to_json(path(['Vicky', 'Ana', 'Joao', 'Andre', 'Diogo', 'Francisco', 'JoseCid'], 'ok'), JSON_Object),
        reply_json(JSON_Object).


% depth search
depth_search(_Request) :-
                http_parameters(_Request, [personA(PersonA, []), personB(PersonB, [])]),        
                (depth_search(PersonA, PersonB, List),
                prolog_to_json(path(List, 'ok'), JSON_Object);
                prolog_to_json(message('path not found', 'error'), JSON_Object)),
        reply_json(JSON_Object).

% breath search
breadth_search(_Request) :-
                http_parameters(_Request, [personA(PersonA, []), personB(PersonB, [])]),
                (breadth_search(PersonA, PersonB, List),
                prolog_to_json(path(List, 'ok'), JSON_Object);
                prolog_to_json(message('path not found', 'error'), JSON_Object)), 
        reply_json(JSON_Object).

% branch and bound
branch_and_bound(_Request) :-
                http_parameters(_Request, [personA(PersonA, []), personB(PersonB, [])]),
               (branch_and_bound(PersonA, PersonB, List),
                prolog_to_json(path(List, 'ok'), JSON_Object);
                prolog_to_json(message('path not found', 'error'), JSON_Object)), 
        reply_json(JSON_Object).

%create connection
create_connection(_Request) :-
                http_parameters(_Request, [personA(PersonA, []), personB(PersonB, []), strenght(Strenght, [])]),
               (createConnection(PersonA, PersonB, Strenght),
                prolog_to_json(message('connection created', 'ok'), JSON_Object);
                prolog_to_json(message('connection not created', 'error'), JSON_Object)), 
        reply_json(JSON_Object).

%remove connection
remove_connection(_Request) :-
                http_parameters(_Request, [personA(PersonA, []), personB(PersonB, [])]),
               (removeConnection(PersonA, PersonB),
                prolog_to_json(message('connection removed', 'ok'), JSON_Object);
                prolog_to_json(message('connection not removed or not exists', 'error'), JSON_Object)), 
        reply_json(JSON_Object).

%update connection strenght
update_connection_strenght(_Request) :-
                http_parameters(_Request, [personA(PersonA, []), personB(PersonB, []), strenght(Strenght, [])]),
               (editConnectionByStrenght(PersonA, PersonB, Strenght),
                prolog_to_json(message('connection edited', 'ok'), JSON_Object);
                prolog_to_json(message('connection not edited or not exists', 'error'), JSON_Object)), 
        reply_json(JSON_Object).

%add connection tag
add_connection_tag(_Request) :-
                http_parameters(_Request, [personA(PersonA, []), personB(PersonB, []), tag(Tag, [])]),
               (editConnectionByAddTag(PersonA, PersonB, Tag),
                prolog_to_json(message('connection edited', 'ok'), JSON_Object);
                prolog_to_json(message('connection not edited or not exists', 'error'), JSON_Object)), 
        reply_json(JSON_Object).

%remove connection tag
remove_connection_tag(_Request) :-
                http_parameters(_Request, [personA(PersonA, []), personB(PersonB, []), tag(Tag, [])]),
               (editConnectionByRemoveTag(PersonA, PersonB, Tag),
                prolog_to_json(message('connection edited', 'ok'), JSON_Object);
                prolog_to_json(message('connection not edited or not exists', 'error'), JSON_Object)), 
        reply_json(JSON_Object).

%get user nodes
get_nodes(_Request) :-  http_parameters(_Request, [user(User, [])]),
                listAllNodes(User, List),
                prolog_to_json(nodes(List, 'ok'), JSON_Object),
                reply_json(JSON_Object).

%get user paths
get_paths(_Request) :-  http_parameters(_Request, [user(User, [])]),
                listAllPaths(User, List),
                create_json_paths(List, ListJson),
                prolog_to_json(allpaths(ListJson, 'ok'), JSON_Object),
                reply_json(JSON_Object).

create_json_paths([],[]).

create_json_paths([(U1, U2, S, L)|T], [Json_ret|Lj]):-prolog_to_json(paths(U1,U2,S,L), Json_ret),
    create_json_paths(T, Lj).
