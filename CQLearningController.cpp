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

	
	

	
	for (int i = 0; i < m_vecSweepers.size(); i++) {
		
		qTable.push_back(make_tuple(m_vecSweepers.at(i), m_vecSweepers.at(i)->Position(), 0.0));
	}
	


	//TODO
}
/**
 The immediate reward function. This computes a reward upon achieving the goal state of
 collecting all the mines on the field. It may also penalize movement to encourage exploring all directions and 
 of course for hitting supermines/rocks!
*/
double CQLearningController::R(uint x,uint y, uint sweeper_no){
	
	int GrabHit = ((m_vecSweepers[sweeper_no])->CheckForObject(m_vecObjects,
		CParams::dMineScale));

	if (GrabHit >= 0)
	{
		switch (m_vecObjects[GrabHit]->getType()) {
		case CDiscCollisionObject::Mine:
		{
			return 100;
		}
		case CDiscCollisionObject::Rock:
		{
			return -80;
		}
		case CDiscCollisionObject::SuperMine:
		{
			return -80;
		}
		}
	}
		
	
	//return -10;
		
	/*for (int i = 0; i < m_vecObjects.size(); i++) {
		if (!m_vecObjects[i]->isDead()) {
			return -10;
		}
		return 50;
	}*/
	/*if (m_vecSweepers[sweeper_no]->Position() !=  m_vecSweepers[sweeper_no]->PrevPosition()) {
	}*/
			//return -10;
		
	
	//TODO: roll your own here!
	
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
	}

	for (uint sw = 0; sw < CParams::iNumSweepers; ++sw){
		if (m_vecSweepers[sw]->isDead()) continue;
		/**
		Q-learning algorithm according to:
		Watkins, Christopher JCH, and Peter Dayan. "Q-learning." Machine learning 8. 3-4 (1992): 279-292
		*/
		//1:::Observe the current state:
		
		/*double action;
		for (int i = 0; i < m_vecSweepers.size(); i++) {
			std::get<1>(qTable[i]) = m_vecSweepers[i]->Position();
			action = R(m_vecSweepers[i]->Position().x, m_vecSweepers[i]->Position().y, i);
			if (action < 0) {
				m_vecSweepers[i]->setRotation((ROTATION_DIRECTION)RandInt(0, 3));
			}
		}
		*/

		for (int i = 0; i < m_vecSweepers.size(); i++) {
			//std::vector<int> list{ 0, 1, 2, 3 };
			//int index = rand() % list.size(); // pick a random index
			//int value = list[index];
			// RandInt(m_vecSweepers[i]->getRotation);  
			
		}
		//TODO
		//2:::Select action with highest historic return:
		//TODO
		for (int i = 0; i < m_vecSweepers.size(); i++) {
		
		}


		//now call the parents update, so all the sweepers fulfill their chosen action
	}
	
	CDiscController::Update(); //call the parent's class update. Do not delete this.
	
	for (uint sw = 0; sw < CParams::iNumSweepers; ++sw){
		if (m_vecSweepers[sw]->isDead()) continue;
		//TODO:compute your indexes.. it may also be necessary to keep track of the previous state
		//3:::Observe new state:
		//TODO
		//4:::Update _Q_s_a accordingly:
		//TODO
	}
	return true;
}

CQLearningController::~CQLearningController(void)
{
	//TODO: dealloc stuff here if you need to	
}
