#pragma once

class IEntity{
   public:
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void OnCollision(IEntity& other) = 0;
};
