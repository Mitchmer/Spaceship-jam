#pragma once
#include <raylib.h>

class Destructible
{
protected:
    bool is_breaking{false};
public:
    virtual void on_destruction() = 0;
};