#include <iostream>
#include <string>
#include "Tables/Table.h"
#include "Tables/Column.h"

int main() {
    tables::Table table;
    tables::Column<std::string> col;
    col.add("a");
    col.add("yo");
    col.add("b");
    col.add("c");
    col.add("yo");
    col.add("e");

    table.addColumn<std::string>(col);
    std::string majorityElement = table.col<std::string>(0).findMostFrequent();
    
    std::cout << "Most frequent element: " << majorityElement << "\n";

    return 0;
}
