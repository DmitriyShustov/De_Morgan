#include <QCoreApplication>
#include "tree.h"
#include "to_tree.h"
#include "QtDebug"

#include <iostream>

QString error_to_str(const error& e) {
    std::stringstream a;
    a << e.error_type << ":" << e.error_message.toStdString();
    QString result(a.str().c_str());
    return result;
}

int main()
{
    std::cout << error_to_str({"123", OPERATION_HAS_TOO_FEW_OPERANDS}).toStdString() << std::endl;
    return 0;

    QString str = "y x y  & ! forall ! ";
    QVector<error> array_of_errors;

    tree* tree_root = parse_tree(str, array_of_errors);

    for (int i = 0; i < array_of_errors.length(); ++i) {
        qDebug() << array_of_errors[i].error_message;
    }

    return 0;
}
