#pragma once
#include "main_includes.h"

using namespace sf;



class Atom
{

private:


	CircleShape m_shape;

	Vector2f m_velocity;

	void _InitMembers();




public:


	const CircleShape& GetShape() const;
	__declspec(property(get = GetShape)) CircleShape shape;


	const Vector2f& GetVelocity() const;
    void SetVelocity(const Vector2f& velocity);
	__declspec(property(get = GetVelocity, put = SetVelocity)) Vector2f velocity;


     int GetRadias() const;
	void SetRadias(const int radias);
	__declspec(property(get = GetRadias, put = SetRadias)) int radias;



	const Vector2f& GetPosition() const;
	void SetPosition(const Vector2f& position);
	__declspec(property(get = GetPosition, put = SetPosition)) Vector2f position;



	const Color& GetShapeColor() const;
	void SetShapeColor(const Color& color);
	__declspec(property(get = GetShapeColor, put = SetShapeColor)) Color color;




	void Render(RenderWindow* Window);



	/// <summary>
	/// Moves the current atom by affset.
	/// </summary>
	void move();


	/// <summary>
	/// Handles collision between two atoms.
	/// </summary>
	/// <param name="atom"></param>
	/// <returns></returns>
	bool Collide(Atom& atom);




	Atom();

	Atom(Vector2f velocity, int radias, Vector2f position);

	virtual ~Atom();



};

