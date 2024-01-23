#pragma once
#include <Location.h>
#include <memory>
#include <vector>

struct BfsCellData {
    bool _disabled;
    int _distance;
    Location _index;
    std::shared_ptr<BfsCellData> _parent;
    std::vector <std::shared_ptr<BfsCellData>> _neighbors;

    BfsCellData() = default;

    BfsCellData(bool disabled, int distance, Location index) : _disabled(disabled),_distance(distance),_index(index) {}

};