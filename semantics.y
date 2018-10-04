%%

program:
    function
    | program function
    ;

var_declaration:
    type declarator_list
    ;

declarator_list:
    declarator
    | declarator declarator_list
    ;