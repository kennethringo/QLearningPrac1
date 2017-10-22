#pragma once
#include "cdisccontroller.h"
#include "CParams.h"
#include "CDiscCollisionObject.h"
#include <cmath>
#include <vector>
#include <math.h>
typedef unsigned int uint;
class CQLearningController :
	public CDiscController
{
private:
	uint _grid_size_x;
	uint _grid_size_y;
public:
	std::vector<std::vector< std::vector<double>  > > qTable;
	double learningFactor = 0.2;
	double lambda = 0.8;

	

	CQLearningController(HWND hwndMain);
	virtual void InitializeLearningAlgorithm(void);

	std::vector<bool> deadSweepers;
	void resetDeadSweepers();

	double R(uint x, uint y, uint sweeper_no);

	int getActionMaxIndex(std::vector<double> &actions);
	int getActionMaxVal(std::vector<double> &actions);
	
	virtual bool Update(void);
	virtual ~CQLearningController(void);
};

