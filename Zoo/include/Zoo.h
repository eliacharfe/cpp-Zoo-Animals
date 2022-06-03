#pragma once
#include "Utilities.h"
#include "FactoryAnimal.h"
#include "Exception.h"
#include "Board.h"
#include "Lion.h"
#include "Goose.h"
#include "Monkey.h"

using MyAnimal = unique_ptr < Animal >;

class Zoo
{
public:
	Zoo(std::ostream& ostr);
	void run(std::istream& input);

private:
    void step();
	void stop(std::istream& input);
	void move(std::istream& input);
	void create(std::istream& input);
	void del(std::istream& input);
	void delAll(std::istream& input);
    void help();
	void exit();

    void initAnimals();
    void printZoo();
    void printList();

    Board m_board;
    using MyAnimals = vector < MyAnimal >;
    MyAnimals m_animals; // vector < unique_ptr < Animal > > m_animals

    bool m_running = true;
    std::ostream& m_ostr;

    void createAnimal(const string& name, const Location& location, const string& kind);
    MyAnimal createAnimalObject(const string& name, const Location& location, const string& kind) const;

    size_t getIndexAnimal(MyAnimal& animal);

    enum class Action {
        Invalid, Stop, Move, Step, Create, Del, DelAll, Help, Exit
    };

    struct ActionDetails {
        string command;
        string description;
        Action action;
    };

    using ActionMap = vector < ActionDetails >;
    const ActionMap m_actions;

    Action readAction(std::istream& input) const;
    void runAction(Action action, std::istream& input);
    static ActionMap createActions();

    void clear(std::istream& input);
    void clear(std::istream& input, Action action);
};
