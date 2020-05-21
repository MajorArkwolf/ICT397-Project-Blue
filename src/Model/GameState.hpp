namespace Model {
    /**
     * Game state holds all models inside of a single class to allow for LUA to interact with them.
     */
    class GameState {
    private:
        /**
         * Default Constructor
         */
        GameState();

    public:
        /**
         * Singleton pattern returns a single instance of the Game State.
         * @return Game State
         */
        static GameState getInstance();

        /**
         * Used to clear all values inside of the state allowing it to be used again.
         */
        void clear();
    };
}


