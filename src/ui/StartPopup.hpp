#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class StartPopup : public geode::Popup<> {
protected:
    bool setup() override;
public:
    static StartPopup* create();
};
