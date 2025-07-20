#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class DuelsStartPopup : public geode::Popup<> {
protected:
    bool setup() override;
public:
    static DuelsStartPopup* create();
};