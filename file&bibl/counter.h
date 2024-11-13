#pragma once

class Counter {
private:
    int value;
public:
    Counter(int Value = 1) : value(Value) {}

    void up();
    void dwn();

    int getValue() const;
};