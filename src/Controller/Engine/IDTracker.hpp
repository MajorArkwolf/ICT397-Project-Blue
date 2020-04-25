#pragma once

namespace BlueEngine {
    /// ID is used as an identifier of objects.
    using ID = long unsigned int;

    /**
     * Tracks ID's from objects within the game engine.
     */
    class IDTracker {
    public:
        /**
         * Singleton class uses modern C++ singleton pattern.
         * @return the instance to ID tracker.
         */
        static IDTracker& getInstance();
        /**
         * Returns a unique ID value
         * @return Unique ID value.
         */
        ID getID();
    private:
        /**
         * Privatised constructor since class is a singleton.
         */
        IDTracker() = default;
        /// The last ID distributed.
        ID id = 0;
    };
}
