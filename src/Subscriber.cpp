#include "Subscriber.h"

Subscriber::Subscriber() : id(""), x(0), y(0) {}

Subscriber::Subscriber(const std::string &newId, int newX, int newY)
    : id(newId), x(newX), y(newY) {}

int Subscriber::getX() const { return x; }

int Subscriber::getY() const { return y; }

std::string Subscriber::getId() const { return id; }

void Subscriber::setId(const std::string &newId) { id = newId; }

void Subscriber::setX(int newX) { x = newX; }

void Subscriber::setY(int newY) { y = newY; }
