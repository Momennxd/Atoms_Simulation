#pragma once


#include "main_includes.h"
#include "Atom.h"
using namespace sf;
using namespace std;
/*
class that acts like the game engine
*/
class AtomsSimulation
{

private:

	//Variables
	sf::RenderWindow* m_Window;
	sf::VideoMode m_videoMode;
	sf::Event m_ev;



	vector<Atom> m_atoms;

	
	void _InitVariables();
	void _InitWindow();


    bool _Running();
	void _pollEvents();


	/// <summary>
	/// Handles window-atom collision.
	/// </summary>
	/// <param name="atom"></param>
	void _WindowCollide(Atom& atom);


	void _SpawnAtom();

	void _SpawnAtoms();


	/// <summary>
	/// Gets a random spawn position starting form any edge of the widnow
	/// </summary>
	/// <returns></returns>
	Vector2f _GetRndSpwanPos() const;


	/// <summary>
	/// Handles objects and window collision.
	/// </summary>
	void _HandleCollision();

	void _MoveAtoms();



	void _Update();



	void _RenderAtoms();
	void _Render();


public:

	AtomsSimulation();

	virtual ~AtomsSimulation();


	void Run();
	

};

