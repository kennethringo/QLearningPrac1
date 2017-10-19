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
	std::vector<std::pair<SVector2D<int>, vector<double>  > > qTable;
	double learningFactor = 0.2;
	double lambda = 0.8;
	CQLearningController(HWND hwndMain);
	virtual void InitializeLearningAlgorithm(void);
	double R(uint x, uint y, uint sweeper_no);
	int getActionMax(vector<double> actions);
	virtual bool Update(void);
	virtual ~CQLearningController(void);
};

