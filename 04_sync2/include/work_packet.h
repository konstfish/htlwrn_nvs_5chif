#pragma once

class WorkPacket{
    private:
    const int id{-1};

    public:
    WorkPacket(int i) : id( i ){}

    int getId() const { return id; }
};
