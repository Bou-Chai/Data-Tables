#include <iostream>
#include <string>
#include "Tables/Table.h"
#include "Tables/Column.h"
#include "Tables/TableView.h"

int main() {
    tables::Table table;

    table.loadCSV("../../tests/data/winequality-red.csv", ';');

    tables::TableView view1(table, 3, 8, 4, 14);
    view1.print();
    std::cout << view1.at<std::string>(1, 9) << "\n";

    tables::TableView view2(view1, 2, 4, 3, 9);
    view2.print();
    std::cout << view2.at<std::string>(1, 2) << "\n";

    return 0;
}