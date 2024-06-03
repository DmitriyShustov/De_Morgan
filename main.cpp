#include <QCoreApplication>
#include "tree.h"
#include "to_tree.h"

int main()
{
    QString str = "y x y  & ! forall ! ";
    QVector<error> array_of_errors;

    tree* tree_root = parse_tree(str, array_of_errors);

    for (int i = 0; i < array_of_errors.length(); ++i) {
        qDebug() << array_of_errors[i].error_message;
    }

    return 0;
}
