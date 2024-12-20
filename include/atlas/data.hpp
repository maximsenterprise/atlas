/*
* data.h
* As part of the Atlas project
* Created by Maxims Enterprise in 2024
* --------------------------------------
* Description: Data structures for atlas
* Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_DATA_H
#define ATLAS_DATA_H

#include <functional>

template <typename T>
class FunctionQueue {
public:
    void add_function(std::function<T()> function) {
        functions.push_back(function);
    }

    void remove_function(std::function<T()> function) {
        functions.erase(
            std::remove(functions.begin(), functions.end(), function),
            functions.end()
        );
    }

    void run() {
        for (auto& function : functions) {
            function();
        }
    }

    void clear() {
        functions.clear();
    }

private:
    std::vector<std::function<T()>> functions;
};

#endif //ATLAS_DATA_H
