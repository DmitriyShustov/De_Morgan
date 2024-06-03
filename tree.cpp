#include "tree.h"

tnode* create_node(QString value, type_node type, int number_of_node) {

    tnode* new_node = new tnode[1];

    new_node->value = value;
    new_node->type = type;
    new_node->number_of_node = number_of_node;

    return new_node;
}

// добавить узел в дерево после текущего узла с указанием стороны(0 - влево, 1 - вправо)
void add_node(tree* parent, tnode* node, QString value, type_node type, int direction) {
    // Если переданное в функцию дерево не существует
    if (parent == nullptr) {
        // qDebug() << "не создано parent";

        return;
    }

    // Если переданный в функцию узел не существует
    if (node == nullptr) {
        // qDebug() << "не существует указанный node";

        return;
    }

    // Создать новый узел с указанными параметрами
    tnode* new_node = create_node(value, type, parent->counter_of_nodes + 1);

    tnode* following_node;
    switch (direction) {
    case 0:
        following_node = node->left;

        node->left = new_node;
        new_node->prev = node;

        new_node->left = following_node;
        if (following_node != nullptr) {
            following_node->prev = new_node;
        }

        break;
    case 1:
        following_node = node->right;

        node->right = new_node;
        new_node->prev = node;

        new_node->left = following_node;
        if (following_node != nullptr) {
            following_node->prev = new_node;
        }

        break;
    default:
        // qDebug() << "параметр direction указан неверно";

        return;

    }

    parent->counter_of_nodes++;
}

// удалить указанный узел из дерева
void delete_node(tree* parent, tnode* node) {
    // Если переданное в функцию дерево не существует
    if (parent == nullptr) {
        // qDebug() << "не создано parent";

        return;
    }

    // Если переданный в функцию узел не существует
    if (node == nullptr) {
        // qDebug() << "не существует указанный node";

        return;
    }

    // Если у узла node существуют 2 предка
    if (node->right != nullptr) {
        // QString error = "невозможно удалить узел " + node->value + " так как он имеет двух потомков";
        // qDebug() << error;

        return;
    }

    // случай с удалением вершины дерева
    if (node->prev == nullptr) {

        if (node->left != nullptr) {
            node->left->prev = nullptr;
            parent->top = node->left;

        }
        return;
    }

    // Если узел node является левым потомком родительского узла
    if (node->prev->left == node) {
        // qDebug() << "удаляем левый узел";
        node->prev->left = node->left;

        if (node->left != nullptr) {
            node->left->prev = node->prev;
        }
    }

    // Если узел node является правым потомком родительского узла
    else if (node->prev->right == node) {
        // qDebug() << "удаляем правый узел";
        node->prev->right = node->left;

        if (node->left != nullptr) {
            node->left->prev = node->prev;
        }
    }

    // node = node->prev;
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
