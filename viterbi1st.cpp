// viterbi1st.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<math.h>

using	namespace std;

class stateTable;

//******************************************************** Definition Of class state
class state
{
public:
	void initialise(int);
	state();
	~state();
	friend void createStateTable(int);

private:
	char stateId,	nextState0Id,	nextState1Id;
	int	noOfStateVariables;
	bool *stateVariables, *nextState0, *nextState1;
	

};


//******************************************************* Definition of class StateTable
class stateTable
{
public:
	friend void createStateTable(int);
	stateTable(int);
	~stateTable();

private:
	int noOfStates;
	state*	states;

};

//-----------------------------------------------constructor for stateTable
stateTable::stateTable(int n)					
{
	noOfStates = pow(2, n);

	states = new state[noOfStates];

	for (size_t i = 0; i < noOfStates; i++)   states[i].initialise(n);
}

//-----------------------------------------------constructor for stateTable
stateTable::~stateTable()					
{
}

//-----------------------------------------------constructor for state
state::state()					
{
}

//-----------------------------------------------initialiser for state
void state::initialise(int n)
{
	stateVariables = new bool[n];
	nextState0 = new bool[n];
	nextState1 = new bool[n];
}

//-----------------------------------------------destructor for state
state::~state()
{
}


//_______________________________________________definition of function createStateTable

void createStateTable(int n)
{
	stateTable table(n);

	int count;
	bool bit;
	char stateId1st = 'a';

	//................................................................. assign state ids
	for (int i = 0; i < table.noOfStates; i++) table.states[i].stateId = stateId1st++;


	//................................................................. assign state variables
	for (int bitPos = 0; bitPos < n; bitPos++)
	{
		count = 0;
		bit = 0;

		for (int j = 0; j < table.noOfStates; j++)
		{
			table.states[j].stateVariables[n - (bitPos + 1)] = bit;

			++count;
			if (count == pow(2, bitPos))
			{
				count = 0;
				if (bit)
				{
					bit = 0;
				}
				else
				{
					bit = 1;
				}


			}
		}


	}

	//................................................................. assign next states
	for (int i = 0; i < table.noOfStates; i++)
	{
		for (int j = n-1; j > 0; j--)
		{
			table.states[i].nextState0[j] = table.states[i].stateVariables[j-1];
			table.states[i].nextState1[j] = table.states[i].stateVariables[j-1];
		}

		table.states[i].nextState0[0] = 0;
		table.states[i].nextState1[0] = 1;

		for (int j = 0; j < table.noOfStates; j++)
		{
			bool flag = true;

			for (int k = 0; k < n; k++)
			{
				if (table.states[i].nextState1[k] != table.states[j].stateVariables[k])
					flag = false;
			}
			
			if(flag)
			{
				table.states[i].nextState1Id = table.states[j].stateId;
				break;
			}
		}

		for (int j = 0; j < table.noOfStates; j++)
		{
			bool flag = true;
			for (int k = 0; k < n; k++)
			{
				if (table.states[i].nextState0[k] != table.states[j].stateVariables[k])
					flag = false;
			}

			if (flag)
			{
				table.states[i].nextState0Id = table.states[j].stateId;
				break;
			}
		}
	}

	//................................................................. display state variables
	for (int i = 0; i < table.noOfStates; i++)
	{   
		cout << table.states[i].stateId << "\t";
		for (int j = 0; j < n; j++)
		{
			cout << table.states[i].stateVariables[j];
		}
		cout << "\t";
		for (int j = 0; j < n; j++)
		{
			cout << table.states[i].nextState0[j];
		}
		cout << "\t";
		for (int j = 0; j < n; j++)
		{
			cout << table.states[i].nextState1[j];
		}

		cout << table.states[i].nextState0Id << "\t";

		cout << table.states[i].nextState1Id << "\t";

		cout << "\n";
	}
}


int main()
{
	createStateTable(2);
    return 0;
}

