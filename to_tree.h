#ifndef TO_TREE_H
#define TO_TREE_H

#include "tree.h"

enum type_of_error {
    NOT_SUPPORTED_VARIABLE,  // неподдерживаемые символы в переменных
    NOT_SUPPORTED_OPERATION, // неподдерживаемая операция
    OPERATION_HAS_TOO_FEW_OPERANDS, // нехватка операндов у логической операции
    OPERATION_HAS_TOO_MANY_OPERANDS, // избыток операндов у логической операции
    NO_LOGICAL_OPEARTION, // отсутствие логической операции в выражении
    TREE_HAS_TO_MANY_NODES, // переизбыток (более 100) узлов в дереве
    QUANTOR_HAS_NO_VARIABLE // первым операндом квантора не является переменная
};

typedef struct error {
    QString error_message= ""; // сообщение об ошибке
    type_of_error error_type; // указание типа ошибки
} error;

tree* parse_tree(QString postfix_string, QVector<error> & array_of_errors);

QVector<QString> convert_postfix_string_to_vector(QString string);

bool check_parsed_posfix_string(QVector<QString> parsed_postfix_string, QVector<error> & array_of_errors);

error create_error(type_of_error type, QString message);

bool is_string_operation_or_variable(QString string, QVector<error> & array_of_errors);

bool check_supported_variables_in_string(QString string, QVector<error> & array_of_errors);

bool check_parsed_postfix_string_length(QVector<QString> parsed_postfix_string, QVector<error> & array_of_errors);

bool check_parsed_posfix_string_contain_operation(QVector<QString> parsed_postfix_string, QVector<error> & array_of_errors);

bool is_string_operation(QString string);

void proceed_unary_operation(QStack<tnode*> & stack, tnode* new_node, QVector<error> & array_of_errors);

void proceed_binary_operation(QStack<tnode*> & stack, tnode* new_node, QVector<error> & array_of_errors);


#endif // TO_TREE_H
