#include "AtomsSimulation.h"
#include "Glob.h"
#include "SimSettings.h"

//constructor
AtomsSimulation::AtomsSimulation()
{
	this->_InitVariables();
	this->_InitWindow();


}

AtomsSimulation::~AtomsSimulation()
{
	delete this->m_Window;

}







void AtomsSimulation::_InitVariables()
{
	this->m_Window = nullptr;
	this->m_atoms = vector<Atom>();
	
}

void AtomsSimulation::_InitWindow()
{
	this->m_videoMode.height = 720;
	this->m_videoMode.width = 1250;

	this->m_Window = new sf::RenderWindow(this->m_videoMode, "SIMULATION", sf::Style::Titlebar | sf::Style::Close);
	this->m_Window->setFramerateLimit(60);
}




bool AtomsSimulation::_Running()
{
	return this->m_Window->isOpen();
}

void AtomsSimulation::_pollEvents()
{
	while (this->m_Window->pollEvent(this->m_ev))
	{
		switch (m_ev.type)
		{
		case sf::Event::Closed:
		{
			this->m_Window->close();
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (m_ev.key.code == sf::Keyboard::Escape)
			{
				this->m_Window->close();
				break;
			}
		
		}


		default:
			break;
		}
	}
}

void AtomsSimulation::_WindowCollide(Atom& atom)
{

	if (atom.position.x + atom.radias * 2 >= m_Window->getSize().x || atom.position.x  <= 0)
	{
		atom.SetVelocity(Vector2f(atom.velocity.x * -1, atom.velocity.y));
	}
		
	if (atom.position.y >= m_Window->getSize().y || (atom.position.y + atom.radias * 2 <= 0))
	{
		atom.SetVelocity(Vector2f(atom.velocity.x, atom.velocity.y * -1));
	}
	

}

void AtomsSimulation::_SpawnAtom()
{

	Vector2f pos = _GetRndSpwanPos();


	//TEMPORARY FOR TEST
	Vector2f velocity = Vector2f(atoms_speed, atoms_speed);

	Atom atom = Atom(velocity, atom_radias, pos);

	this->m_atoms.push_back(atom);

}

void AtomsSimulation::_SpawnAtoms()
{
	if (this->m_atoms.size() < atoms_max)
	{
		this->_SpawnAtom();
	}
}




Vector2f AtomsSimulation::_GetRndSpwanPos() const
{
	///* This variable stores a random number that represents the spawn side 1-right, 2-down, 3-left, 4-up */
	//short SpawnSide = Glob::GetRandomNumber(1, 4);

	//switch (SpawnSide)
	//{
	//	case 1: // Right
	//	{
	//		return Vector2f(this->m_Window->getSize().x, Glob::GetRandomNumber(0, this->m_Window->getSize().y));
	//	}
	//	case 2: // Bottom
	//	{
	//		return Vector2f(Glob::GetRandomNumber(0, this->m_Window->getSize().x), this->m_Window->getSize().y);
	//	}
	//	case 3: // Left
	//	{
	//		return Vector2f(0, Glob::GetRandomNumber(0, this->m_Window->getSize().y));
	//	}
	//	case 4: // Top
	//	{
	//		return Vector2f(Glob::GetRandomNumber(0, this->m_Window->getSize().x), 0);
	//	}
	//	default:
	//	{
	//		// Handle default case properly. Return a valid position to avoid undefined behavior.
	//		return Vector2f(0, 0); // Or any default value
	//	}
	//}


	return Vector2f(Glob::GetRandomNumber(1, this->m_Window->getSize().x - 1),
		Glob::GetRandomNumber(1, this->m_Window->getSize().y - 1));
}



void AtomsSimulation::_HandleCollision()
{

	//handling atoms collision with themselves and window.
	for (int i = 0; i < this->m_atoms.size(); ++i)
	{
		this->_WindowCollide(m_atoms[i]);
		for (int j = 0; j < this->m_atoms.size(); ++j)
		{
			if (i != j)
			{
				m_atoms[i].Collide(m_atoms[j]);

			}
		}
	}

}


void AtomsSimulation::_MoveAtoms()
{
	for (Atom& atom: m_atoms)
	{
		atom.move();
	}
}



void AtomsSimulation::_Update()
{
	this->_pollEvents();
	this->_SpawnAtoms();
	this->_HandleCollision();
	this->_MoveAtoms();

	
}


void AtomsSimulation::_RenderAtoms()
{
	for (Atom& atom : m_atoms)
	{
		atom.Render(this->m_Window);
	}
}

void AtomsSimulation::_Render()
{
	this->m_Window->clear();

	_RenderAtoms();

	this->m_Window->display();
}


void AtomsSimulation::Run()
{
	while (_Running())
	{
		
		_Update();

		//LOGS

		//TODO---->HANDLING LOGS


		_Render();

	}
}
