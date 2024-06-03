#include "to_tree.h"

QVector<QString> convert_postfix_string_to_vector(QString string) {

    QStringList tmp_s = string.split(" ");
    QVector<QString> return_string;

    for (int i = 0; i < tmp_s.length(); ++i) {
        if (tmp_s[i] != "") {
            return_string.push_back(tmp_s[i]);
        }
    }

    return return_string;

    //    return string.split(" ", Qt::SkipEmptyParts);
}

bool check_parsed_posfix_string(QVector<QString> parsed_postfix_string, QVector<error> & array_of_errors) {
    // переменная, которая показывает, нашлась ли хотя бы одна ошибка в строке с польской записью
    bool is_parsed_string_correct = true;

    // проверка, соответствуют ли все элементы польской записи заданным требованиям
    for (int i = 0; i < parsed_postfix_string.length(); ++i) {
        // если встретилась ошибка в текущем рассматриваемом элементе строки, то указать это
        is_parsed_string_correct = (is_string_operation_or_variable(parsed_postfix_string[i], array_of_errors)) ? is_parsed_string_correct : false;
    }

    // проверка количества элементов в строке в польской записи (проверка количества узлов в дереве)
    is_parsed_string_correct = (check_parsed_postfix_string_length(parsed_postfix_string, array_of_errors)) ? is_parsed_string_correct : false;

    // проверка, содержит ли польская запись хотя бы одну поддерживаемую логическую операцию
    is_parsed_string_correct = (check_parsed_posfix_string_contain_operation(parsed_postfix_string, array_of_errors)) ? is_parsed_string_correct : false;

    return is_parsed_string_correct;
}

error create_error(type_of_error type, QString message) {
    error new_error;
    new_error.error_type = type;
    new_error.error_message = message;

    return new_error;
}

bool is_string_operation_or_variable(QString string, QVector<error> & array_of_errors) {
    // проверка, является ли лексема логическим нулем или логической единицей
    if (string == "0" or string == "1") {

        return true;
    }

    //проверка, является ли строка поддерживаемой операцией
    if (SUPPORTED_OPERATIONS.contains(string)) {

        return true;
    }


    return check_supported_variables_in_string(string, array_of_errors);
}

bool check_supported_variables_in_string(QString string, QVector<error> & array_of_errors) {
    bool return_value = true;

    if (!string.isLower()) {
        array_of_errors.append(create_error(NOT_SUPPORTED_VARIABLE, "Подпоследовательность " + string + " содержит не только строчные буквы"));

        return_value = false;
    }
    for (int i = 0; i < string.length(); ++i) {
        if ( (string.at(i).unicode() > 255) or (!string.at(i).isLetter())) {
            array_of_errors.append(create_error(NOT_SUPPORTED_VARIABLE, "Подпоследовательность " + string + " содержит неподдерживаемый символ: " + string.at(i)));

            return_value = false;
        }
    }

    return return_value;
}

bool check_parsed_postfix_string_length(QVector<QString> parsed_postfix_string, QVector<error> & array_of_errors) {
    if (parsed_postfix_string.length() > NODE_LIMIT_IN_TREE) {
        array_of_errors.append(create_error(TREE_HAS_TO_MANY_NODES, "Количество узлов в дереве превышено 100. Текущее количество узлов: " + QString::number(parsed_postfix_string.length())));

        return false;
    }

    return true;
}

bool check_parsed_posfix_string_contain_operation(QVector<QString> parsed_postfix_string, QVector<error> & array_of_errors) {
    bool is_contain_operation = false;

    // проверка, содержит ли польская запись хотя бы одну поддерживаемую логическую операцию
    for (int i = 0; i < parsed_postfix_string.length(); ++i) {
        if (is_string_operation(parsed_postfix_string[i])) {

            is_contain_operation = true;
        }
    }

    if (parsed_postfix_string.length() > 1 and is_contain_operation == false) {
        array_of_errors.append(create_error(NO_LOGICAL_OPEARTION, "Отсутствует логическая операция в выражении"));

        return is_contain_operation;
    }
    else {

        return true;
    }
}

bool is_string_operation(QString string) {

    return SUPPORTED_OPERATIONS.contains(string);
}

void proceed_unary_operation(QStack<tnode*> & stack, tnode* new_node, QVector<error> & array_of_errors) {

    if (stack.isEmpty()) {
        array_of_errors.append(create_error(OPERATION_HAS_TOO_FEW_OPERANDS, "Для логической операции ! должен быть указан 1 элемент"));

        return;
    }

    tnode* popped_element = stack.pop();

    new_node->left = popped_element;
    popped_element->prev = new_node;

    stack.push(new_node);
}

void proceed_binary_operation(QStack<tnode*> & stack, tnode* new_node, QVector<error> & array_of_errors) {
    if (stack.length() < 2) {
        array_of_errors.append(create_error(OPERATION_HAS_TOO_FEW_OPERANDS, "Для логической операции " + new_node->value + " должны быть указаны 2 элемента"));

        return;
    }

    tnode* first_poped_element = stack.pop();
    tnode* second_poped_element = stack.pop();

    if ( ((new_node->type == EXIST) or (new_node->type == FORALL)) and (second_poped_element->type != VAR) ) {
        array_of_errors.append(create_error(QUANTOR_HAS_NO_VARIABLE, "Для кватора " + new_node->value + " первым операндом должна быть указана только переменная"));

        return;
    }

    new_node->right = first_poped_element;
    first_poped_element->prev = new_node;

    new_node->left = second_poped_element;
    second_poped_element->prev = new_node;

    stack.push(new_node);
}
