#include <QCoreApplication>
#include "tree.h"
#include "to_tree.h"
#include "to_dot.h"
#include "QtDebug"
#include "QFile"
#include "QTextStream"
#include "string"

#include <iostream>

int main(int argc, char* argv[])
{
    argc = 3;
    argv[1] = "E:\\de_morgan_input.txt";
    argv[2] = "E:";
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    QFile file(argv[1]);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "Не удалось открыть файл для чтения" << std::endl;

        return 0;
    }

    QTextStream in(&file);
    QString input_string = in.readLine();

    file.close();

    // QString str = "x y ! forall";
    QVector<error> array_of_errors;

    tree* tree_root = parse_tree(input_string, array_of_errors);

    for (int i = 0; i < array_of_errors.length(); ++i) {
        qDebug() << array_of_errors[i].error_message;
    }

    if (array_of_errors.length() == 0) {
        QFile original_file(QString::fromUtf8(argv[2]) + QString("\\original_tree.txt"));
        if (!original_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Не удалось открыть файл для записи";

            return 0;
        }

        QTextStream out(&original_file);
        out << convert_tree_to_dot(tree_root) << "\n";

        original_file.close();

        perform_logical_expression_transformations(tree_root, tree_root->top);

        QFile transformed_file(QString::fromUtf8(argv[2]) + QString("\\transformed_tree.txt"));
        if (!transformed_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Не удалось открыть файл для записи";

            return 0;
        }

        QTextStream out1(&transformed_file);
        out1 << convert_tree_to_dot(tree_root) << "\n";

        transformed_file.close();
    }

    return 0;
}
