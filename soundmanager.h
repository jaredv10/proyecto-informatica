#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
//#include <QSoundEffect>

class SoundManager : public QObject {
    Q_OBJECT

public:
    enum Sound { Hit, Score };

    SoundManager(QObject *parent = nullptr);
    void playSound(Sound sound);

private:
    //QSoundEffect hitSound;
    //QSoundEffect scoreSound;
};

#endif // SOUNDMANAGER_H
