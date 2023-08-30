#ifndef DBCLKCELL_H
#define DBCLKCELL_H

#include "dbCell.h"

class dbClkCell {	

private:
  int _id;
  int _left ;
  int _right;
  int _parent;
  int _height;
  Point _origin;

	
public : 

  const dbCell* myCell;
  
  dbClkCell(int k, int l, int r, int p, Point orig, dbCell* c) : 
  _id(k), _left(l), _right(r), _parent(p), _height(0),
	_origin(orig), myCell(c) {}

  dbClkCell(int k, int l, int r, int p, int h, Point orig, dbCell* c) : 
  _id(k), _left(l), _right(r), _parent(p), _height(h),
	_origin(orig), myCell(c) {}
	
  dbClkCell(int key) : _id(key), _left(-1), _right(-1), _parent(-1), _height(0), myCell(NULL) {}
  
  dbClkCell() : _id(-1), _left(-1), _right(-1), _parent(-1), _height(0), myCell(NULL){}
	
		
	bool isSinkNode() const { //shouldn't have any kids
		//if (!this->myCell) return false;
		return ( (_left == -1) && (_right == -1));
	}
	
	bool isHalfSinkNode() const {	// can have a kid
		if (!this->myCell) return false;
		return (this->_left == -1 && this->_right != -1) || 
			   (this->_left != -1 && this->_right == -1);
	}
	
  int getId()     const { return _id     ;}  
  int getLeft ()  const { return _left   ;}
  int getRight()  const { return _right  ;}
  int getParent() const { return _parent ;}
  int getHeight() const { return _height ;}
  Point getOrigin() const { return _origin; }
  dbCell const* getCell() const { return myCell; }

  void setOrigin ( Point pt ) { _origin = pt; }
  void setCell ( dbCell* c) { myCell = c; }
  void setHeight ( int h ) { _height = h; }
  void setLeft (int n)  { _left  = n ;}
  void setRight(int n)  { _right = n ;}
  void setId(int n) { _id = n;}  
  void setParent(int n) { _parent = n;}  
  
	
friend std::ostream& operator<<
	( std::ostream& os, const dbClkCell& c)
{
	os << "idx: " << c.getId() << " par: " << c.getParent() << " left: " << c.getLeft ()
		<< " right: " << c.getRight() << " height: " << c.getHeight();
		os << " | orig: " << c.getOrigin() ;
		if (c.myCell != NULL)
			os << "| myCell: " << *(c.myCell) ;
	return os;
}		

};

class CompareClkCellsByHeight
{
public:
   CompareClkCellsByHeight(){}
   bool operator() ( dbClkCell* p1, dbClkCell* p2) const {
	   if (p1->getHeight() == p2->getHeight()){
	       if (p1->isSinkNode() && p2->isSinkNode())
		       return p1->getId() < p2->getId();
		   else return p1->getLeft() + p1->getRight() > p2->getLeft() + p2->getRight() ;
	   }
		
	 return p1->getHeight() < p2->getHeight();   
   }
   bool operator() ( dbClkCell p1, dbClkCell p2) const {
	   if (p1.getHeight() == p2.getHeight()){
	       if (p1.isSinkNode() && p2.isSinkNode())
		       return p1.getId() < p2.getId();
		   else return p1.getLeft() + p1.getRight() > p2.getLeft() + p2.getRight() ;
	   }
		
	 return p1.getHeight() < p2.getHeight();   
   }
	
};

class CompareClkCellsByHeight_Id
{
public:
   CompareClkCellsByHeight_Id(){}

   bool operator() ( dbClkCell p1, dbClkCell p2) const {
	   if (p1.getHeight() == p2.getHeight()){
	       return p1.getId() < p2.getId();
	   }		
	 return p1.getHeight() < p2.getHeight();   
   }
   bool operator() ( dbClkCell* p1, dbClkCell* p2) const {
	   if (p1->getHeight() == p2->getHeight()){
		return p1->getId() < p2->getId();
	   }		
	 return p1->getHeight() < p2->getHeight();   
   }
   
};

class CompareClkCellsByID
{
public:
   CompareClkCellsByID(){}
   bool operator() ( dbClkCell* p1, dbClkCell* p2) const {
	   return p1->getId() < p2->getId();
   }
   bool operator() ( dbClkCell p1, dbClkCell p2) const {
	   return p1.getId() < p2.getId();
   }
	
};




#endif //DBCLKCELL_H