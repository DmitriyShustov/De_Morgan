#include "to_dot.h"

QString convert_tree_to_dot(tree* wood) {

    if (wood == nullptr) {
        return "";
    }

    //  добавить начало строки дот
    QString dot_string = "digraph { ";

    //  обойти дерево и добавить из него все label'ы и связи в строку дот
    dot_string = process_node_to_convert_dot(wood->top, dot_string);

    //  добавить конец строки дот
    dot_string.append("}");

    return dot_string;
}


QString add_label_to_dot_string(QString dot_string, int number_of_node, QString value) {

    dot_string.append(QString::number(number_of_node) + " [label=\"" + value + "\"]; ");

    return  dot_string;
}


QString add_edge_to_dot_string(QString dot_string, int number_of_current_node,  int number_of_next_node){

    dot_string.append(QString::number(number_of_current_node) + "->" + QString::number(number_of_next_node) + "; ");

    return dot_string;
}


QString process_node_to_convert_dot(tnode* node, QString dot_string) {
    // если текущий узел дерева пустой, то закончить алгоритм
    if (node == nullptr) {
        // вернуть строку в дот формате

        return dot_string;
    }

    // добавляем label к строке дот, исходя из текущего узла
    dot_string = add_label_to_dot_string(dot_string, node->number_of_node, node->value);

    // если есть левый потомок
    if (node->left != nullptr) {
        // добавить связь с левым потомком к строке дот
        dot_string = add_edge_to_dot_string(dot_string, node->number_of_node, node->left->number_of_node);

        // вызвать данную функцию для левого потомка
        dot_string = process_node_to_convert_dot(node->left, dot_string);
    }

    // если есть правый потомок
    if (node->right != nullptr) {
        // добавить связь с правым потомком к строке дот
        dot_string = add_edge_to_dot_string(dot_string, node->number_of_node, node->right->number_of_node);
        // вызвать данную функцию для правого потомка
        dot_string = process_node_to_convert_dot(node->right, dot_string);
    }
    // вернуть строку в дот формате

    return dot_string;
}
