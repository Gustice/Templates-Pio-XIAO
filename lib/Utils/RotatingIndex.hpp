/**
 * @file RotatingIndex.hpp
 * @author Gustice
 * @brief Classes for typical index manipulation
 */

#pragma once

/**
 * @brief Index with automatic revolution back to start position
 * @details Useful for Buffer-Pointer, or similar tasks
 * 
 * @tparam T Numeric type
 */
template <typename T = int>
class RotatingIndex {
  public:
    /// @brief Value at witch the index rotates back to beginning
    const T MaxIndex;
    
    /**
     * @brief Constructor for rotating index
     * @brief output index will be set to 0 if incremented value reaches Maximum
     * @param max Maximum index for overflow-condition
     */
    RotatingIndex(T max) : MaxIndex(max) {
        _index = 0;
    }

    /**
     * @brief Get the current index and increment index afterwards
     * @return T current index
     */
    T GetIndexAndIncrement() {
        auto retVal = _index;
        _index++;
        if (_index >= MaxIndex) {
            _index = 0;
        }
        return retVal;
    };

    /**
     * @brief Get the current index without incrementing the index
     * @return T current index
     */
    T GetIndex() const {
        return _index;
    }

    /**
     * @brief Increments index and retuns if index has been reset
     */
    bool IncrementAndCheckIfRevolves() {
        _index++;
        if (_index >= MaxIndex) {
            _index = 0;
            return true;
        }
        return false;
    }

    /**
     * @brief Reset Index to 0
     */
    void ResetIndex() {
        _index = 0;
    }

  private:
    /// Current Index
    T _index;
};
