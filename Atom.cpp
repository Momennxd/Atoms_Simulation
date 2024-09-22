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

bool Atom::Collide(Atom& atom)
{
    // Calculate the distance between the centers of the two atoms
    Vector2f delta = this->m_shape.getPosition() - atom.m_shape.getPosition();
    float distanceSquared = delta.x * delta.x + delta.y * delta.y;

    // Get the radii of both atoms
    float radiusSum = this->m_shape.getRadius() + atom.m_shape.getRadius();
    float radiusSumSquared = radiusSum * radiusSum;

    // Check if distance between centers is less than the sum of their radii
    if (distanceSquared < radiusSumSquared)
    {
        // Collision detected

        // Calculate the actual distance between the atoms
        float distance = std::sqrt(distanceSquared);
        if (distance == 0.0f)
        {
            distance = 0.1f;  // Prevent division by zero if atoms are at the same position
        }

        // Calculate collision normal (normalized direction between atoms)
        Vector2f collisionNormal = delta / distance;

        // Reflect the velocity based on the collision normal
        Vector2f relativeVelocity = this->velocity - atom.velocity;
        float velocityAlongNormal = relativeVelocity.x * collisionNormal.x + relativeVelocity.y * collisionNormal.y;

        // If the objects are moving apart, we don't process the collision
        if (velocityAlongNormal > 0)
        {
            return false;
        }

        // Coefficient of restitution (bounciness factor)
        float restitution = 1.0f;  // Perfect elastic collision

        // Impulse scalar (assuming equal mass for both atoms)
        float impulse = -(1 + restitution) * velocityAlongNormal / 2.0f;

        // Apply impulse to each atom's velocity
        Vector2f impulseVector = impulse * collisionNormal;
        this->velocity += impulseVector;
        atom.velocity -= impulseVector;

        // Resolve overlap (optional for smooth visual)
        float overlap = 0.5f * (radiusSum - distance);  // Half the overlap
        this->m_shape.setPosition(this->m_shape.getPosition() + collisionNormal * overlap);
        atom.m_shape.setPosition(atom.m_shape.getPosition() - collisionNormal * overlap);

        // Change color to indicate collision
        if (this->m_shape.getFillColor() == sf::Color::Green) {
            this->m_shape.setFillColor(sf::Color::Red);
        }
        else {
            this->m_shape.setFillColor(sf::Color::Green);
        }

        return true;
    }

    return false;
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
