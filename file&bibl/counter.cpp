#include "counter.h"

void Counter::up() { ++value; };
void Counter::dwn() { --value; };
int Counter::getValue() const { return value; };