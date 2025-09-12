//
// Created by Kirill Dulov on 9/11/25.
//

#include "string_utils.h"

std::vector<int> FindString(const std::string& text, const std::string& text_to_find) {
    std::vector<int> positions;
    size_t pos = text.find(text_to_find, 0);
    if (text_to_find == "") { return positions; }
    while (pos != std::string::npos) {
        positions.push_back(pos);
        pos = text.find(text_to_find, pos + (text_to_find.empty() ? 1 : 1));
    }
    return positions;
}
