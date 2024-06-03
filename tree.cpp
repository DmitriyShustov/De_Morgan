#include "tree.h"

tnode* create_node(QString value, type_node type, int number_of_node) {

    tnode* new_node = new tnode[1];

    new_node->value = value;
    new_node->type = type;
    new_node->number_of_node = number_of_node;

    return new_node;
}

type_node convert_string_to_type_node(QString string) {
    if (string == "|") {

        return DIS;
    }
    else if (string == "&") {

        return CON;
    }
    else if (string == "!") {

        return NOT;
    }
    else if (string == ">") {

        return FOLLOW;
    }
    else if (string == "=") {

        return EQU;
    }
    else if (string == "^") {

        return XOR;
    }
    else if (string == "exist") {

        return EXIST;
    }
    else if (string == "forall") {

        return FORALL;
    }
    else {

        return VAR;
    }
}
