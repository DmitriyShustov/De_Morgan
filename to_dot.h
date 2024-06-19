#pragma once

#ifndef TO_DOT_H
#define TO_DOT_H

#include "tree.h"

QString process_node_to_convert_dot(tnode* node, QString dot_string);

QString add_label_to_dot_string(QString dot_string, int number_of_node, QString value);

QString add_edge_to_dot_string(QString dot_string, int number_of_current_node,  int number_of_next_node);

QString convert_tree_to_dot(tree* wood);

#endif // TO_DOT_H
