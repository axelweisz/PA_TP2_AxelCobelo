#pragma once

class Player;

class GameObject
{
public:
    GameObject(double x, double y);

    virtual void update(double dt);
    virtual void render(SDL_Renderer* renderer) const;
    void testCollision(Player& obj);
    bool deleteMe;

    double getW() const;
    double getH() const;
    bool shouldDelete() const;

    double x;
    double bloop[256];
    double y;
    double blaap[256];
    double w, h;
protected:
    bool isColliding(Player& obj);
    virtual void collide(Player& obj) = 0;

    double vx;
    double bleep[256];
    double vy;
    double bliip[256];
    double ax;
    double bluup[256];
    double ay;
    double blyyp[256];

    double color_r, color_g, color_b, color_a;
    
};
