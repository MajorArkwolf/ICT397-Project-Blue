#pragma once
#include <vector>

using std::vector;

template<class T>
class GameStack {
  public:

    /**
     * Default constructor.
     */
    GameStack() = default;

    /**
     * Default destructor.
     */
    ~GameStack()                         = default;

    /**
     * Deleted copy constructor.
     * @param other
     */
    GameStack(const GameStack<T> &other) = delete;

    /**
     * Deleted move constructor.
     * @param other
     */
    GameStack(GameStack<T> &&other) = delete;

    /**
     * Deleted copy assignment.
     * @param other
     * @return
     */
    GameStack<T> &operator=(const GameStack<T>& other) = delete;

    /**
     * Deleted move assignment.
     * @param other
     * @return
     */
    GameStack<T> &operator=(GameStack<T>&& other) = delete;

    /**
     * Add a new state onto the stack.
     * @param newState the state to be added onto the stack.
     */
    void AddToStack(T newState) {
        gameStack.push_back(newState);
    }

    /**
     * Returns the top of the stacks state.
     * @return
     */
    T& getTop() {
        return gameStack.at(gameStack.size() - 1);
    }

    /**
     * Peeks below the current stack.
     * @param currentElement the element it wants to peek below.
     * @return the element below.
     */
    T& peekBelow(T currentElement) {
        size_t index = findElement(currentElement) - 1;
        if (index > 0) {
            return gameStack.at(index);
        } else {
            return nullptr;
        }
        
    }

  private:
    /// The stack itself.
    vector<T> gameStack;

    /*
     * Finds an element on the stack.
     */
    size_t findElement(T currentElement) {
        size_t index = 0;
        for (auto &i : gameStack) {
            ++index;
            if (currentElement == i) {
                break;
            }
        }
        return index;
    }
};
