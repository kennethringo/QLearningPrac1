/**
         (                                      
   (     )\ )                                   
 ( )\   (()/(   (    ) (        (        (  (   
 )((_)   /(_)) ))\( /( )(   (   )\  (    )\))(  
((_)_   (_))  /((_)(_)|()\  )\ |(_) )\ )((_))\  
 / _ \  | |  (_))((_)_ ((_)_(_/((_)_(_/( (()(_) 
| (_) | | |__/ -_) _` | '_| ' \)) | ' \)) _` |  
 \__\_\ |____\___\__,_|_| |_||_||_|_||_|\__, |  
                                        |___/   

Refer to Watkins, Christopher JCH, and Peter Dayan. "Q-learning." Machine learning 8. 3-4 (1992): 279-292
for a detailed discussion on Q Learning
*/
#include "CQLearningController.h"


CQLearningController::CQLearningController(HWND hwndMain):
	CDiscController(hwndMain),
	_grid_size_x(CParams::WindowWidth / CParams::iGridCellDim + 1),
	_grid_size_y(CParams::WindowHeight / CParams::iGridCellDim + 1)
{
}
/**
 The update method should allocate a Q table for each sweeper (this can
 be allocated in one shot - use an offset to store the tables one after the other)

 You can also use a boost multiarray if you wish
*/
void CQLearningController::InitializeLearningAlgorithm(void)
{

	
	

	
	/*for (int i = 0; i < m_vecSweepers.size(); i++) {
		vector <double> actions = { 0.0,0.0,0.0,0.0 };
		qTable.push_back(make_pair(m_vecSweepers.at(i)->PrevPosition(), actions));
		
		
	}*/
	vector <double> actions = { 0.0,0.0,0.0,0.0 };
	

	vector<vector<vector<double>>> qTable1(_grid_size_y, vector<vector<double>>(_grid_size_x, vector<double>(4)));
	

	for (uint x = 0; x < _grid_size_x; x++) {
		
		for (uint y = 0; y < _grid_size_y; y++) {
			qTable1[y][x] = actions;
		}
		
	}
	qTable = qTable1;

	for (uint i = 0; i < CParams::iNumSweepers; i++) {
		deadSweepers.push_back(false);
	}
	


	//TODO
}


void CQLearningController::resetDeadSweepers() {
	for (uint i = 0; i <CParams::iNumSweepers; i++) {
		deadSweepers.at(i) = false;
	}
}


/**
 The immediate reward function. This computes a reward upon achieving the goal state of
 collecting all the mines on the field. It may also penalize movement to encourage exploring all directions and 
 of course for hitting supermines/rocks!
*/
double CQLearningController::R(uint x,uint y, uint sweeper_no){
	double reward = 0.0f;
	//TODO: roll your own here!
	int foundOne = ((m_vecSweepers.at(sweeper_no))->CheckForObject(m_vecObjects,
		CParams::dMineScale));
	
	
	if (foundOne >= 0)
	{
		switch (m_vecObjects.at(foundOne)->getType()) {
			case CDiscCollisionObject::Mine:
			{
				reward = 100.0f;
				break;
			}
			case CDiscCollisionObject::Rock:
			{
				reward = -100.0f;
				break;
			}
			case CDiscCollisionObject::SuperMine:
			{
				reward = -100.0f;
				break;
			}
		}
	}
	//else {
	//	reward = -5.0f;
	//	
	//}
	if (m_vecSweepers[sweeper_no]->MinesGathered() == (CParams::iNumMines)) {
		reward = 400.0f;
	}
	return reward;
}

int CQLearningController::getActionMaxIndex(std::vector<double> &actions) {

	int maxVal = (int)actions.at(0);
	int index = 0;
	for (uint a = 0; a < 4; a++) {
		if (actions.at(a) > maxVal) {
			maxVal = actions.at(a);
			index = a;
		}
	}
	std::vector<int> allMaxIndexes;
	allMaxIndexes.push_back(index);
	for (uint a = 0; a < 4; a++) {
		if (a == index) {
			//skip
		}
		else {
			if (actions.at(a)== maxVal) {
				allMaxIndexes.push_back(a);
			}
		}
	}
	int randomIndex = index;
	if (allMaxIndexes.size() > 1) {
		randomIndex = RandInt(0, allMaxIndexes.size() - 1);
	}

	return randomIndex;
	///////////////////////////////////////////////////////////////////

}



int CQLearningController::getActionMaxVal(std::vector<double> &actions) {

	int maxVal = (int)actions.at(0);
	int index = 0;
	for (uint a = 0; a < 4; a++) {
		if (actions.at(a) > maxVal) {
			maxVal = actions.at(a);
			index = a;
		}
	}

	return maxVal;
	////////////////////////////////////////////////////////////////////////
	
	
}


/**
The update method. Main loop body of our Q Learning implementation
See: Watkins, Christopher JCH, and Peter Dayan. "Q-learning." Machine learning 8. 3-4 (1992): 279-292
*/
bool CQLearningController::Update(void)
{
	//m_vecSweepers is the array of minesweepers
	//everything you need will be m_[something] ;)
	uint cDead = std::count_if(m_vecSweepers.begin(),
							   m_vecSweepers.end(),
						       [](CDiscMinesweeper * s)->bool{
								return s->isDead();
							   });
	if (cDead == CParams::iNumSweepers){
		printf("All dead ... skipping to next iteration\n");
		m_iTicks = CParams::iNumTicks;
		resetDeadSweepers();
	}

	for (uint sw = 0; sw < CParams::iNumSweepers; ++sw){
		if (m_vecSweepers[sw]->isDead() && deadSweepers[sw]) {
			
			continue;
		}
		else if (m_vecSweepers[sw]->isDead()) {
			deadSweepers[sw] = true;
		}
		/**
		Q-learning algorithm according to:
		Watkins, Christopher JCH, and Peter Dayan. "Q-learning." Machine learning 8. 3-4 (1992): 279-292
		*/
		
		
		//1:::Observe the current state:
		//2:::Select action with highest historic return:
		int action;
		SVector2D<int> position = m_vecSweepers[sw]->Position();
		position /= 10;
		action = getActionMaxIndex(qTable[position.x][position.y]);
		m_vecSweepers[sw]->setRotation((ROTATION_DIRECTION)action);
		
		
		//now call the parents update, so all the sweepers fulfill their chosen action
	}
	
	CDiscController::Update(); //call the parent's class update. Do not delete this.
	
	for (uint sw = 0; sw < CParams::iNumSweepers; ++sw){
		if (m_vecSweepers[sw]->isDead()) {
			deadSweepers.at(sw) = true;
			continue;
		} 
		//TODO:compute your indexes.. it may also be necessary to keep track of the previous state
		//3:::Observe new state:
		SVector2D<int> prevPosition = m_vecSweepers[sw]->PrevPosition();
		prevPosition /= 10;
		SVector2D<int> position = m_vecSweepers[sw]->Position();
		position /= 10;
		int currentAction = (int)m_vecSweepers[sw]->getRotation();
			
		//4:::Update _Q_s_a accordingly:
		qTable[prevPosition.x][prevPosition.y][currentAction] += learningFactor * (R(position.x, position.y, sw) + (lambda * (getActionMaxVal(qTable[position.x][position.y])) - qTable[prevPosition.x][prevPosition.y][currentAction]));
		
	}
	if (m_iTicks == CParams::iNumTicks) {
		resetDeadSweepers();
	}
	return true;
}

CQLearningController::~CQLearningController(void)
{
	//TODO: dealloc stuff here if you need to	
}
