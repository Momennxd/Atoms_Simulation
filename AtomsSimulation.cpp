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
	///this->m_atoms_pos = unordered_set<string>();

	
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
		
	if (atom.position.y + atom.radias * 2 >= m_Window->getSize().y || atom.position.y <= 0)
	{
		atom.SetVelocity(Vector2f(atom.velocity.x, atom.velocity.y * -1));
	}
	

}

void AtomsSimulation::_SpawnAtom()
{

	Vector2f pos = _GetRndSpwanPos();
	Vector2f velocity = GetRndDirections(atoms_speed);

	
	Atom atom = Atom(velocity, atom_radias, pos);

	while (_DoesPosIntersects(atom.shape.getGlobalBounds()))
	{
		atom.position = _GetRndSpwanPos();

	}

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

	Vector2f pos = Vector2f(
		Glob::GetRandomNumber(atom_radias * 2, this->m_Window->getSize().x - atom_radias * 2),
		Glob::GetRandomNumber(atom_radias * 2, this->m_Window->getSize().y - atom_radias * 2)
	);
		

	return pos;
}

bool AtomsSimulation::_DoesPosIntersects(FloatRect bounds) const
{

	for (int i = 0; i < this->m_atoms.size(); ++i)
	{
		if (m_atoms[i].shape.getGlobalBounds().intersects(bounds))
		{
			return true;
		}
	}


	return false;
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
				if (m_atoms[i].Collide(m_atoms[j]))
					break;

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

Vector2f AtomsSimulation::GetRndDirections(double speed)
{
	int rnd = Glob::GetRandomNumber(1, 4);


	switch (rnd)
	{
	case 1:
		return Vector2f(speed, speed);


	case 2:
		return Vector2f(-speed, speed);

	case 3:
		return Vector2f(speed, -speed);

	case 4:
		return Vector2f(-speed, -speed);


	default:
		return Vector2f(speed, speed);
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
	_PrintLogs();

	this->m_Window->display();
}

void AtomsSimulation::_PrintLogs()
{
	cout << "Atoms Size = " << this->m_atoms.size() << "\n";

}


void AtomsSimulation::Run()
{
	while (_Running())
	{
		
		_Update();

	

		_Render();

	}
}
