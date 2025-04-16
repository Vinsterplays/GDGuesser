#include "HookedCustomSongWidget.hpp"
#include <managers/GuessManager.hpp>

bool HookedCustomSongWidget::init(SongInfoObject *songInfo, CustomSongDelegate *songDelegate, bool showSongSelect, bool showPlayMusic, bool showDownload, bool isRobtopSong, bool unkBool, bool isMusicLibrary, int unk) {
    if (!CustomSongWidget::init(
        songInfo,
        songDelegate,
        showSongSelect,
        showPlayMusic,
        showDownload,
        isRobtopSong,
        unkBool,
        isMusicLibrary,
        unk
    )) return false;

    if (!GuessManager::get().currentLevel) return true;

    // m_songIDLabel->setString("SongID: ???????");
    // m_songLabel->setString("????????");
    // m_artistLabel->setString("????????");

    // m_moreBtn->setVisible(false);

    return true;
}

void HookedCustomSongWidget::loadSongInfoFinished(SongInfoObject* info) {
    CustomSongWidget::loadSongInfoFinished(info);
    
    // m_songIDLabel->setString("SongID: ???????");
    // m_songLabel->setString("????????");
    // m_artistLabel->setString("????????");

    // m_moreBtn->setVisible(false);
}
