#include <iostream>
#include <string>
#include "Tables/Table.h"
#include "Tables/Column.h"
#include "Tables/TableView.h"

int main() {
    tables::Table table1;

    table1.loadCSV("../../tests/data/winequality-red.csv", ';');

    tables::Table table2 = table1.copy(0, 11, 0, 0);
    std::cout << "Table2 width: " << table2.width() << "\n";

    std::vector<std::string> row1 = table1.getRow<std::string>(3, 0, 11);
    std::cout << "Row width: " << row1.size() << "\n";

    table2.addRow<std::string>(row1);
    table2.print();
    std::cout << "\n";

    table2.addRow<std::string>({"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"});
    table2.print();

    return 0;
}
