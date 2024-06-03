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

#endif // TREE_H
