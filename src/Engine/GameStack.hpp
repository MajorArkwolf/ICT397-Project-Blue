#pragma once
#include <vector>

using std::vector;

template<class T>
class GameStack {
  public:
    GameStack() = default;
    ~GameStack()                         = default;
    GameStack(const GameStack<T> &other) = delete;
    GameStack<T> &operator=(GameStack<T> other) = delete;

    void AddToStack(T newState) {
        gameStack.push_back(newState);
    }

    T getTop() {
        return gameStack.at(gameStack.size() - 1);
    }

    T peekBelow(T currentElement) {
        size_t index = findElement(currentElement) - 1;
        if (index > 0) {
            return gameStack.at(index);
        } else {
            return nullptr;
        }
        
    }

  private:
    vector<T> gameStack;

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
