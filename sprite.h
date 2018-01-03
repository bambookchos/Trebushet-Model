#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <string>
class Sprite : public QObject
{
    Q_OBJECT
public:
    explicit Sprite(QObject *parent = 0);
    QPixmap *spriteImage[31];   // В данный объект QPixamp будет помещён спрайт
};

#endif // SPRITE_H
