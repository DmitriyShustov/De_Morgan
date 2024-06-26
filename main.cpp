#include <QCoreApplication>
#include "tree.h"
#include "to_tree.h"
#include "to_dot.h"
#include "QtDebug"
#include "QFile"
#include "QTextStream"

#include <iostream>

int main(int argc, char* argv[])
{
    // argc = 3;
    // argv[1] = "E:\\de_morgan_input.txt";
    // argv[2] = "E:";
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    QFile file(argv[1]);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "The file could not be opened for reading\n" << std::endl;

        return 0;
    }

    QTextStream in(&file);
    QString input_string = in.readLine();

    file.close();

    QVector<error> array_of_errors;

    tree* tree_root = parse_tree(input_string, array_of_errors);

    for (int i = 0; i < array_of_errors.length(); ++i) {
        std::cout << array_of_errors[i].error_message.toStdString() << std::endl;
    }

    if (array_of_errors.length() == 0) {
        QFile original_file(QString::fromUtf8(argv[2]) + QString("\\original_tree.txt"));
        if (!original_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            std::cout << "The file " << QString::fromUtf8(argv[2]).toStdString() << " could not be opened for writing\n" << std::endl;

            return 0;
        }

        QTextStream out(&original_file);
        out << convert_tree_to_dot(tree_root);

        original_file.close();

        perform_logical_expression_transformations(tree_root, tree_root->top);

        QFile transformed_file(QString::fromUtf8(argv[2]) + QString("\\transformed_tree.txt"));
        if (!transformed_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            std::cout << "The file " << QString::fromUtf8(argv[2]).toStdString() << " could not be opened for writing\n" << std::endl;

            return 0;
        }

        QTextStream out1(&transformed_file);
        out1 << convert_tree_to_dot(tree_root);

        transformed_file.close();
    }

    getchar();

    return 0;
}
