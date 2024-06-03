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
