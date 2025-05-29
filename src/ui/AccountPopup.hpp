#pragma once

#include <Geode/Geode.hpp>
using namespace geode::prelude;

class AccountPopup : public geode::Popup<int> {
protected:
    bool setup(int accountID);
public:
    static AccountPopup* create(int accountID);
};
