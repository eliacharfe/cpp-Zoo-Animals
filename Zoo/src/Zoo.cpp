#include "Zoo.h"

Zoo::Zoo(std::ostream& ostr)
	: m_actions(createActions()), m_ostr(ostr), m_running(true)
{
	initAnimals();
	printZoo();
}
//-----------------------
void Zoo::run(std::istream& input)
{
	do {
		try {
			const auto action = readAction(input);
			runAction(action, input);
			clear(input, action);
			if (action != Action::Help)
				printZoo();
		}
		catch (Exception& e) { cerr << e.what() << '\n'; clear(input); }
		catch (std::invalid_argument& e) { cerr << e.what() << '\n'; clear(input); }
		catch (std::istream::failure& e) { cerr << e.what() << '\n'; clear(input); }
		catch (OutOfRange e) { cerr << e.what() << '\n'; clear(input); }
		catch (std::out_of_range& e) { cerr << e.what() << '\n'; clear(input); }
		catch (...) { clear(input);  throw; }
	} while (m_running);
}
//-------------------------
void Zoo::step()
{
	for (auto& animal : m_animals)
		animal->step();
}
//--------------------------------
void Zoo::stop(std::istream& input)
{
	auto numAnimal = 0;
	input >> numAnimal;

	if (input.fail())
		throw std::istream::failure("\nstop: input failed. not an integer\n");
	if (numAnimal >= m_animals.size() || numAnimal < 0)
		throw OutOfRange("Out of range\n");

	m_animals[numAnimal]->stop();
}
//------------------------------
void Zoo::move(std::istream& input)
{
	auto numAnimal = 0;
	input >> numAnimal;

	if (input.fail())
		throw std::istream::failure("\ninput failed. not an integer\n");
	if (numAnimal >= m_animals.size() || numAnimal < 0)
		throw OutOfRange("Out of range\n");

	m_animals[numAnimal]->move();
}
//---------------------------------
void Zoo::create(std::istream& input)
{
	auto kind = string();
	input >> kind;
	if (input.fail())
		throw std::istream::failure("\ninput failed: not a string \n");

	auto name = string();
	input >> name;
	if (input.fail())
		throw std::istream::failure("\ninput failed: not a string \n");

	createAnimal(name, Location(), kind);
}
//---------------------------
void Zoo::del(std::istream& input)
{
	auto numAnimal = 0;
	input >> numAnimal;

	if (input.fail())
		throw std::istream::failure("\ninput failed. not an integer\n");
	if (numAnimal >= m_animals.size() || numAnimal < 0)
		throw OutOfRange("Out of range\n");

	m_board.setChar(m_animals[numAnimal]->getLocation()._y, m_animals[numAnimal]->getLocation()._x, EMPTY);
	m_animals.erase(m_animals.begin() + numAnimal);
}
//--------------------------------
void Zoo::delAll(std::istream& input)
{
	auto kind = string();
	input >> kind;

	if (input.fail())
		throw std::istream::failure("\naction failed: not a string \n");
	for (auto& c : kind)
		if (isdigit(c))
			throw std::invalid_argument("\naction failed: name of kind contains digits\n: invalid_argument\n");

	auto it = m_animals.begin();
	while (it != m_animals.end()) {
		if (kind == it->get()->getKind()) {
			m_board.setChar(it->get()->getLocation()._y, it->get()->getLocation()._x, EMPTY);
			it = m_animals.erase(it);
		}
		else it++;
	}
}
//--------------------------------
void Zoo::help()
{
	m_ostr << "The available commands are:\n";
	for (const auto& action : m_actions)
		m_ostr << "* " << action.command << action.description << '\n';
	m_ostr << '\n';
}
//---------------------------
void Zoo::exit()
{
	m_running = false;
}
//---------------------------------
void Zoo::clear(std::istream& input)
{
	input.clear();
	input.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
	system("cls");
}
//----------------------------------------
void Zoo::clear(std::istream& input, Action action)
{
	input.clear();
	input.ignore(std::numeric_limits < std::streamsize >::max(), '\n');

	if (action != Action::Help)
		system("cls");
}
//-------------------------------
void Zoo::initAnimals()
{
	createAnimal("Mufasa", Location(), "Lion");
	createAnimal("Simba", Location(), "Lion");
	createAnimal("Rafiki", Location(), "Monkey");
	createAnimal("Akka", Location(), "Goose");
	createAnimal("Morten", Location(), "Goose");
	createAnimal("Duffy Duck", Location(), "Goose");
}
////---------------------------------------
void Zoo::createAnimal(const string& name, const Location& location, const string& kind)
{
	MyAnimal animal = createAnimalObject(name, location, kind);
	if (animal)
		m_animals.push_back(std::move(animal));
}
//----------------------------------------------------
MyAnimal Zoo::createAnimalObject(const string& name, const Location& location, const string& kind) const
{
	return FactoryAnimal::create(name, location, kind);
}
//-----------------------------------
void Zoo::printZoo()
{
	for (auto& animal : m_animals) {
		m_board.setChar(animal->getLastLocation()._y, animal->getLastLocation()._x, EMPTY);
		m_board.setChar(animal->getLocation()._y, animal->getLocation()._x, animal->getInitial());
	}
	m_board.printZoo(m_ostr);
	printList();
}
//--------------------------
void Zoo::printList()
{
	for (auto& animal : m_animals) {
		m_ostr << getIndexAnimal(animal) << ": ";
		animal->printDetails();
	}
}
//-----------------------------
size_t Zoo::getIndexAnimal(MyAnimal& animal)
{
	auto it = find(m_animals.begin(), m_animals.end(), animal);
	if (it != m_animals.end())
		return it - m_animals.begin();
	else
		throw OutOfRange("index out of range");
}
//---------------------------------------
Zoo::Action Zoo::readAction(std::istream& input) const
{
	m_ostr << "\nEnter command ('help' for the list of available commands): ";

	auto action = string();
	input >> action;

	if (input.fail())
		throw std::istream::failure("\ninput failed\n: istream failure\n");

	for (auto& c : action)
		if (isdigit(c))
			throw std::invalid_argument("\nname of function contains digits\n: invalid_argument\n");

	for (decltype(m_actions.size()) i = 0; i < m_actions.size(); ++i)
		if (action == m_actions[i].command)
			return m_actions[i].action;

	return Action::Invalid;
}
//---------------------------------------------------------------
void Zoo::runAction(Action action, std::istream& input)
{
	switch (action)
	{
	default: m_ostr << "Unknown enum entry used!\n";  break;
	case Action::Invalid: { m_ostr << "\nCommand not found\n";
		throw std::invalid_argument(": invalid argument (name of function)");// throw exception
		break;
	}
	case Action::Move:		move(input);        break;
	case Action::Stop:		stop(input);        break;
	case Action::Step:		step();             break;
	case Action::Create:	create(input);      break;
	case Action::Del:		del(input);         break;
	case Action::DelAll:	delAll(input);      break;
	case Action::Help:		help();             break;
	case Action::Exit:		exit();             break;
	}
}
//----------------------------------------
Zoo::ActionMap Zoo::createActions()
{
	return ActionMap
	{
		{  "move", " (num animal) - allow to move the animal",
			Action::Move
		},
		{  "stop", " (num animal) - disallow to move the animal",
			Action::Stop
		},
		{  ".", " (point) - move the animal to their new location (if they are allowed to move)",
			Action::Step
		},
		{  "create", " (kind animal and a new name) - creates new animal after given the kind and a name",
			Action::Create
		},
		{  "del", " (num animal) - delete animal #num from the animals vector",
			Action::Del
		},
		{  "delAll", " (kind animal) - delete all animals of that kind",
			Action::DelAll
		},
		{  "help", " - print this command list",
			Action::Help
		},
		{  "exit", " - exit the program",
			Action::Exit
		},
	};
}
//----------------------------------------