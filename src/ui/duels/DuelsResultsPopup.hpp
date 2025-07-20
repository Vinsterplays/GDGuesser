#pragma once

#include <Geode/Geode.hpp>
using namespace geode::prelude;

#include <managers/net/server.hpp>
#include <managers/net/client.hpp>

class DuelsResultsPopup : public geode::Popup<DuelResults> {
public:
    static DuelsResultsPopup* create(DuelResults results);
protected:
    bool setup(DuelResults results) override;
    void onClose(CCObject* sender) override;
};
