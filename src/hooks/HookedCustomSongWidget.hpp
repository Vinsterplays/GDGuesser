#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CustomSongWidget.hpp>

using namespace geode::prelude;

class $modify(HookedCustomSongWidget, CustomSongWidget) {
    $override
    bool init(SongInfoObject *songInfo, CustomSongDelegate *songDelegate, bool showSongSelect, bool showPlayMusic, bool showDownload, bool isRobtopSong, bool unkBool, bool isMusicLibrary, int unk);

    $override
    void loadSongInfoFinished(SongInfoObject*);
};
