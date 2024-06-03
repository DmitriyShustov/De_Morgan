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
