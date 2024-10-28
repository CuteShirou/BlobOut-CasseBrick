#ifndef ENTITY_H__
#define ENTITY_H__

class Entity
{
public:
	Entity();
	~Entity();
	virtual void destroy() = 0;
	virtual void move() = 0;
	virtual bool onCollision(Entity& entity) = 0;
	virtual


private:

};


#endif // !ENTITY_H__

