namespace Model {
    enum class Difficulty {
        easy,
        medium,
        hard
    };

    /**
     * Game state holds all models inside of a single class to allow for LUA to interact with them.
     */
    class GameState {
    private:
        /**
         * Default Constructor
         */
        GameState();
        Difficulty difficulty = Difficulty::easy;

    public:
        /**
         * Singleton pattern returns a single instance of the Game State.
         * @return Game State
         */
        static GameState& getInstance();

        /**
         * Used to clear all values inside of the state allowing it to be used again.
         */
        void clear();
        /**
         * Get the difficulty
         * @return enum class
         */
        Difficulty getDifficulty() const;

        /**
         * Set the difficulty used in the game
         * @param difficulty enum class
         */
        void setDifficulty(Difficulty difficulty);

        /**
         * casts the enum class for difficulty into an int value for lua.
         * @return int representation of the enum class
         */
        static int gameDifficulty();
    };
}


