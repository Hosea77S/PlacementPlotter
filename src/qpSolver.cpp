#include "qpSolver.h"



void 
	qpSolver::generateQMatrix (const std::map< INT_PAIR, double>& matrix, 
	CompCol_Mat_double* Q) 
{

	int count = matrix.size();
	double *val = new double[count];
	int *colind = new int[count], *rowind = new int[count];
	//cout << "count is: " << count << endl;

	int maxRow=0;
	int maxCol=0;

	unsigned int i = 0;
	for (auto it_Q = matrix.begin(); it_Q != matrix.end(); ++it_Q) {
		int row = it_Q->first.first;
		int col = it_Q->first.second;
		
		if (maxRow < row) maxRow = row;
		if (maxCol < col) maxCol = col;
		

		val[i] = it_Q->second;
		rowind[i] = row;
		colind[i] = col;
		
		
		//Make sure Diagnoal elements are not 0
		if(row == col && val[i] == 0)
			std::cerr << "Diagonal element is zero: " << row << "\n";

		i++;
	}
	
	
	Coord_Mat_double C(maxRow+1,maxCol+1,count, val, rowind, colind);
	//CompCol_Mat_double* Q;
	*Q = C;
	
	delete [] val;
	delete [] rowind;
	delete [] colind;
	
	
	return ;
}


void 
	qpSolver::generateCMatrix (const std::map<int, double> &matrix, 
	MV_Vector_double* C ) 
{
		
	int count = _numOfNonTerminals; //matrix.size();
	double *val = new double[count];

	//Generating C maxtrix, adding zeros to the elements with no zeros
	auto it_C = matrix.begin();
	for (int i=0; i < count; i++)
	{
		if(it_C != matrix.end()){
			if(it_C->first == i){
				//cout << "setting C index: " << i << "to " << -1 * it_C->second << endl;
				val[i] = -1 * it_C->second;
				it_C++;
			}
			else{
				//cout << "setting C index: " << i << "to 0\n";
				val[i] = 0;
			}			
		}
		else{
			//cout << "setting C index: " << i << "to 0\n";
			val[i] = 0;						
		}
	}
	
	MV_Vector_double T(val, count);
	//MV_Vector_double* C;
	*C = T;

	delete [] val;
	
	return ;
}




std::vector<double> 
	qpSolver::solveCG( CompCol_Mat_double& Qx,
					    MV_Vector_double&   Cx, 
						Dir d,
						bool acc ) 
{


/* 	std::cout << "\n\n************************";
	std::cout << "Solving system of linear equations"; 
	std::cout << "************************\n\n";
 */
	//Creating 2 emty vectors to get the results of the solver
	//VECTOR_double X(_numOfNonTerminals, 0.0);     // Create rhs, solution vectors
	
	double *xxx = new double[_numOfNonTerminals];	
	for (int i=0; i < _numOfNonTerminals; i++)
	{
		if (d == _XX)
			xxx[i] = (*_pl)[i].x;
		else
			xxx[i] = (*_pl)[i].y;
	}
	VECTOR_double X(xxx, _numOfNonTerminals);

/* 	writetxtfile_mat ("Qx", Qx);
 */	
	
	DiagPreconditioner_double Mx(Qx);
		
	
/* 	std::cout << "Sizes are Qx: " << Qx.dim(0) 
	<< " " << Qx.dim(1)  << " Cx: " << Cx.size() 
	<< " X: " << X.size() <<  "\n";
 */		
	int max_iter = (int)MAX_SOLVER_ITERATION;
	double tot = (double)SOLVER_TOLERNCE;

	if (acc)
	{
	  max_iter *= 10;
	  tot *= 0.1;
	}
	
	/*std::cout << "\n\tSolver: maxIt = " << max_iter 
	<< " tol = " << tot << "\n";*/
	
	//int result_x = CG(Qx, X, Cx, Mx, max_iter, tot);	
	CG(Qx, X, Cx, Mx, max_iter, tot);	
	
	std::string D = (d == _XX) ? "X" : "Y";
	std::cout << "CG-"<< D << " : " << max_iter << 
				" " << tot << "\n";

	std::vector<double> result ;
	for (int i=0; i< X.size(); i++)
	{
		result.push_back(X[i]);
	}
				
				
	delete [] xxx;
	return result;
}


std::vector<double> 
	qpSolver::solve(const std::map<INT_PAIR, double>& Qx, 
					const std::map<int, double> &Cx, 
					Dir d,
					bool acc)
{
	//standard version of Q matrix
	CompCol_Mat_double Q ; 
	generateQMatrix(Qx, &Q);

	//standard version of C matrix
	MV_Vector_double C   ; 
	generateCMatrix(Cx, &C);
	auto result = solveCG(Q, C, d, acc);
	
	
	
	
	return result;	
}


std::vector<double> 
	qpSolver::solve( CompCol_Mat_double& Q, 
					 MV_Vector_double &C , Dir d )
{
	auto result = solveCG(Q, C, d);
	
	return result;	
}

