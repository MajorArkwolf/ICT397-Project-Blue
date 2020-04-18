#pragma once

namespace BlueEngine {

    using ID = long unsigned int;

    class IDTracker {
    public:
        static IDTracker& getInstance();
        ID getID();
    private:
        IDTracker() = default;
        ID id = 0;
    };
}
