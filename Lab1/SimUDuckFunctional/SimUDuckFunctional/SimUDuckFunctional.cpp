#include <cassert>
#include <iostream>
#include <memory>
#include <functional>
#include <vector>

using namespace std;

using FlyStrategy = function<void()>;

using DanceStrategy = function<void()>;

using QuackStrategy = function<void()>;

void FlyWithWings()
{
	cout << "I'm flying with wings!!" << endl; // не знаю как сделать чтобы считало количество вылетов
}

void FlyNoWay(){}

void DanceValse()
{
	cout << "I'm Dancing Valse!" << endl;
}

void DanceMinuet()
{
	cout << "I'm Dancing Minuet!" << endl;
}

void NoDance(){}


void NormalQuack() 
{
	cout << "Quack Quack!!!" << endl;
}

void Squeak()
{
	cout << "Squeek!!!" << endl;
}

void MuteQuack() {};

class Duck
{
public:
	Duck(const FlyStrategy& flyBehavior,
		const QuackStrategy& quackBehavior,
		const DanceStrategy& danceBehavior)
	{
		SetQuackBehavior(quackBehavior);
		SetFlyBehavior(flyBehavior);
		SetDanceBehavior(danceBehavior);
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	void Dance()
	{
		//cout << "I'm Dancing" << endl;
		m_danceBehavior();
	}

	void SetDanceBehavior(const DanceStrategy& danceBehavior)
	{
		assert(danceBehavior);
		m_danceBehavior = danceBehavior;
	}

	void SetFlyBehavior(const FlyStrategy& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = flyBehavior;
	}

	void SetQuackBehavior(const QuackStrategy& quackBehavior)
	{
		assert(quackBehavior);
		m_quackBehavior = quackBehavior;
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyStrategy m_flyBehavior;
	QuackStrategy m_quackBehavior;
	DanceStrategy m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings, NormalQuack, DanceValse)
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWings, NormalQuack, DanceMinuet)
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(FlyNoWay, MuteQuack, NoDance)
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay, Squeak, NoDance)
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay, NormalQuack, NoDance)
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

void main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);
	/*PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);
	mallardDuck.SetFlyBehavior(FlyNoWay);
	PlayWithDuck(mallardDuck);
	mallardDuck.SetFlyBehavior(FlyWithWings);
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);
	*/
	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyWithWings);
	PlayWithDuck(modelDuck);
}