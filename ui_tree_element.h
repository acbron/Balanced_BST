#ifndef UI_TREE_ELEMENT_H
#define UI_TREE_ELEMENT_H

#include <QString>
#include <QPainter>

enum Color {
    Red, Black, NoColor
};

class Shape {
public:
    Shape() {}
    virtual ~Shape() {}

public:
    virtual void paint(QPainter &) = 0;
};

class Point : public Shape {
public:
    Point();
    Point(int, int, Color, const QString &);
    ~Point() {}

public:
    void paint(QPainter &);
    void setCenter(int, int);
    void setColor(Color);
    void setWeight(const QString &);

private:
    int centerX;
    int centerY;
    Color color;
    QString weight;
};

class Edge : public Shape {
public:
    Edge();
    Edge(int, int, int, int);
    ~Edge() {}
    void paint(QPainter &);
    void setStartCoodinate(int, int);
    void setEndCoodinate(int, int);

private:
    int startX;
    int startY;
    int endX;
    int endY;
};

#endif // UI_TREE_ELEMENT_H
