#ifndef MYRAND_H
#define MYRAND_H

#include <climits>

class randomNumber {
	
private:	
	int _minV;
	int _maxV;
	unsigned _seed;

public:	
	randomNumber(int mn, int mx):_minV(mn), _maxV(mn), _seed(UINT_MAX){
		
	}
    unsigned operator()(unsigned N) 
	{
		srand(_seed);
		return (rand()%int(_maxV)) + _minV;
	}
	
    operator unsigned() 
	{
		srand(_seed);
		return (rand()%int(_maxV)) + _minV;
	}
	
	unsigned getRand(){
		srand(_seed);
		return (rand()%int(_maxV)) + _minV;		
	}
	
};

#endif //MYRAND_H
