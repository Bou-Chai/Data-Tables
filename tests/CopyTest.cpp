#include <iostream>
#include <string>
#include "Tables/Table.h"
#include "Tables/Column.h"
#include "Tables/TableView.h"

int main() {
    tables::Table table1;

    table1.loadCSV("../../tests/data/winequality-red.csv", ';');
    tables::Table table2 = table1.copy(0, 11, 0, 0);
    table2.print();
    std::cout << "\n";
    table2.add<std::string>("citric acid", "7");
    table2.print();

    return 0;
}