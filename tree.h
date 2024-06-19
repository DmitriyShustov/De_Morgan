#pragma once

#ifndef TREE_H
#define TREE_H

#include <QString>
#include <QVector>

#define NODE_LIMIT_IN_TREE 100

QVector<QString> const SUPPORTED_OPERATIONS = {"|", "&", "!", ">", "=", "^", "exist", "forall"};

enum type_node {
    DIS, // дизъюнкция
    CON, // конъюнкция
    NOT, // отрицание
    FOLLOW, // следование
    EQU, // эквивалентность
    XOR, // исключающее “или” (xor)
    EXIST, // квантор существования
    FORALL, // квантор всеобщности
    VAR // обозначение переменной
};

struct tnode {
    enum type_node type; // тип узла
    QString value;  // поле данных
    int number_of_node; // номер узла
    struct tnode *prev = nullptr;  // родитель
    struct tnode *left = nullptr;  // левый потомок
    struct tnode *right = nullptr; // правый потомок
};

struct tree {
    tnode *top; // вершина дерева
    int counter_of_nodes = 0; // счетчик узлов для обозначения их номеров
};

enum transformation {
    NO_TRANSFORMATION, // преобразование не нужно
    DOUBLE_NEG_DELETE, // раскрытие двойного отрицания
    CON_OPENING, // раскрытие конъюнкции
    DIS_OPENING, // раскрытие дизъюнкции
    EXIST_OPENING, // раскрытие квантора существования
    FORALL_OPENING // раскрытие квантора всеобщности
};

// выделить память под tnode и заполнить поля структуры tnode указанными значениями
tnode* create_node(QString value, type_node type, int number_of_node);

type_node convert_string_to_type_node(QString string);

// добавить узел в дерево после текущего узла с указанием стороны(0 - влево, 1 - вправо)
void add_node(tree* parent, tnode* node, QString value, type_node type, int direction);

// удалить указанный узел из дерева
void delete_node(tree* parent, tnode* node);

//обход дерева и раскрытие скобок по всем рассматриваемым законам
void perform_logical_expression_transformations(tree* parent, tnode* node);

// определить, какой тип преобразования нужно сделать на текущем node'e
transformation determine_type_of_transformation(tnode* node);

// выполнить преобразование, исходя из типа операции
void perform_definite_transformation(tree* parent, tnode *node, transformation type);

// выполнить удаление двойного отрицая в дереве
void remove_double_negatives(tree* parent, tnode* node);

// выполнить раскрытие дизъюнкции или конъюнкциипо закону Де Мограна
void perform_dis_or_con_opening(tree* parent, tnode* node, transformation type);

// выполнить раскрытие квантора существования или квантора всеобщности
void perform_exist_or_forall_opening(tree* parent, tnode* node, transformation type);

#endif // TREE_H
