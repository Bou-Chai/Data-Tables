#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <stdexcept>
#include "Table.h"

namespace tables {
    class TableView {
    public:
        // Constructs TableView object from table
        TableView(tables::Table& table) {
            setTableP(&table);
            setColumnStart(0);
            setColumnEnd(table.width());
            setRowStart(0);
            setRowEnd(table.height());
        }

        // TODO: Add boundary checks to constructor below
        // Constructs TableView object from table given boundaries
        TableView(tables::Table& table, int columnStart, int columnEnd, int rowStart, int rowEnd) {
            setTableP(&table);
            setColumnStart(columnStart);
            setColumnEnd(columnEnd);
            setRowStart(rowStart);
            setRowEnd(rowEnd);
        }

        // Constructs TableView object from another TableView given boundaries
        TableView(TableView& view, int columnStart, int columnEnd, int rowStart, int rowEnd) {
            setTableP(view.getTableP());

            // Calculate absolute column and row boundaries
            int absColumnStart = view.getColumnStart() + columnStart;
            int absColumnEnd = view.getColumnStart() + columnEnd;
            int absRowStart = view.getRowStart() + rowStart;
            int absRowEnd = view.getRowStart() + rowEnd;
            
            // Check if new range is valid
            view.checkColumnIndex(absColumnStart);
            view.checkColumnIndex(absColumnEnd - 1);
            view.checkRowIndex(absRowStart);
            view.checkRowIndex(absRowEnd - 1);

            // Set this view's absolute boundaries
            setColumnStart(absColumnStart);
            setColumnEnd(absColumnEnd);
            setRowStart(absRowStart);
            setRowEnd(absRowEnd);
        }

        template <typename T>
        T& at(int columnIndex, int rowIndex) {
            columnIndex += columnStart;
            rowIndex += rowStart;
            checkColumnIndex(columnIndex);
            checkRowIndex(rowIndex);

            return tableP->at<T>(columnIndex, rowIndex);
        }

        template <typename T>
        int getCount(int columnIndex, T element) {
            columnIndex += columnStart;
            checkColumnIndex(columnIndex);

            return tableP->getCount(columnIndex, element, rowStart, rowEnd);
        }

        // Throws std::out_of_range if column index is out of range of the view
        void checkColumnIndex(int columnIndex) {
            if (columnIndex < columnStart || columnIndex >= columnEnd) {
                std::cout << columnIndex << "|" << columnStart << "\n";
                throw std::out_of_range("Column index out of range");
            }
        }

        // Throws std::out_of_range if row index is out of range of the view
        void checkRowIndex(int rowIndex) {
            if (rowIndex < rowStart || rowIndex >= rowEnd) {
                throw std::out_of_range("Row index out of range");
            }
        }

        void print() {
            std::vector<ColumnBase*> columnVector = tableP->getColumnVector();
            std::unordered_map<std::string, ColumnBase*> columnMap = tableP->getColumnMap();
            for (int i = columnStart; i < columnEnd; i++) {
                std::unordered_map<std::string, ColumnBase*>::iterator it;
                for (it = columnMap.begin(); it != columnMap.end(); ++it) {
                    if (it->second == columnVector[i]) {
                        std::cout << it->first << ": ";
                        break;
                    }
                }

                if (it == columnMap.end()) {
                    std::cout << i << ": ";
                }

                columnVector[i]->print(rowStart, rowEnd);
            }
        }

        int getWidth() {
            return columnEnd - columnStart;
        }

        int getHeight() {
            return rowEnd - rowStart;
        }

        tables::Table* getTableP() {
            return tableP;
        }

        void setTableP(tables::Table* tableP) {
            this->tableP = tableP;
        }

        int getColumnStart() {
            return columnStart;
        }

        void setColumnStart(int columnStart) {
            this->columnStart = columnStart;
        }

        int getColumnEnd() {
            return columnEnd;
        }

        void setColumnEnd(int columnEnd) {
            this->columnEnd = columnEnd;
        }

        int getRowStart() {
            return rowStart;
        }

        void setRowStart(int rowStart) {
            this->rowStart = rowStart;
        }

        int getRowEnd() {
            return rowEnd;
        }

        void setRowEnd(int rowEnd) {
            this->rowEnd = rowEnd;
        } 

    private:
        tables::Table* tableP;
        int columnStart;
        int columnEnd;      // Not inclusive
        int rowStart;
        int rowEnd;         // Not inclusive
    };
}

#endif
