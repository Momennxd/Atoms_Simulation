#include "Atom.h"




void Atom::_InitMembers()
{
	this->m_shape = CircleShape();
	this->m_velocity = Vector2f(0,0);
	this->m_shape.setFillColor(Color::Green);


}

const CircleShape& Atom::GetShape() const
{
	
	return m_shape;
	
}

const Vector2f& Atom::GetVelocity() const
{
	return m_velocity;

}

void Atom::SetVelocity(const Vector2f& velocity)
{
	this->m_velocity = velocity;
}

int Atom::GetRadias() const
{
	return m_shape.getRadius();
}

void Atom::SetRadias(const int radias)
{	
	this->m_shape.setRadius(radias);
}

const Vector2f& Atom::GetPosition() const
{
	return this->m_shape.getPosition();
}

void Atom::SetPosition(const Vector2f& position)
{
	this->m_shape.setPosition(position);
}

const Color& Atom::GetShapeColor() const
{
	return this->m_shape.getFillColor();
}

void Atom::SetShapeColor(const Color& color)
{
	this->m_shape.setFillColor(color);
}

void Atom::Render(RenderWindow* Window)
{
	Window->draw(this->m_shape);
}

void Atom::move()
{
	this->m_shape.move(m_velocity);
}

void Atom::Collide(Atom& atom)
{
    if (this->m_shape.getGlobalBounds().intersects(atom.m_shape.getGlobalBounds()))
    {
        sf::FloatRect rect1 = this->m_shape.getGlobalBounds();
        sf::FloatRect rect2 = atom.m_shape.getGlobalBounds();

        // Calculate overlap
        float overlapX = std::min(rect1.left + rect1.width - rect2.left, rect2.left + rect2.width - rect1.left);
        float overlapY = std::min(rect1.top + rect1.height - rect2.top, rect2.top + rect2.height - rect1.top);

        // Reverse velocity based on which axis the collision happened on
        if (overlapX < overlapY)
        {
            // X-axis collision: reverse the X component of velocity
            this->velocity = Vector2f(-this->velocity.x, this->velocity.y);
        }
        else
        {
            // Y-axis collision: reverse the Y component of velocity
            this->velocity = Vector2f(this->velocity.x, -this->velocity.y);
        }

        // Change color to indicate a collision
        if (this->shape.getFillColor() == Color::Green)
        {
            this->m_shape.setFillColor(Color::Red);
        }
        else
        {
            this->m_shape.setFillColor(Color::Green);
        }
    }
}

Atom::Atom()
{
	_InitMembers();
}

Atom::Atom(Vector2f velocity, int radias, Vector2f position)
{
	_InitMembers();
	this->m_velocity = velocity;
	this->radias = radias;
	this->position = position;

}

Atom::~Atom()
{
}
