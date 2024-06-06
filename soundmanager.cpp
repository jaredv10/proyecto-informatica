#include "soundmanager.h"

SoundManager::SoundManager(QObject *parent) : QObject(parent) {
    //hitSound.setSource(QUrl::fromLocalFile(":/sounds/hit.wav"));
    //scoreSound.setSource(QUrl::fromLocalFile(":/sounds/score.wav"));
}

//void SoundManager::playSound(Sound sound) {
//    switch (sound) {
//        case Hit:
//            hitSound.play();
//            break;
//        case Score:
//            scoreSound.play();
//            break;
//    }
//}
