#include "partitionIds.h"


std::ostream& operator<<(std::ostream& os, const PartitionIds& part);

//: A vector to save the partition status of all cells
class Partitioning      : public std::vector<PartitionIds>
{
    public:
        Partitioning() {}
        Partitioning(unsigned size) : std::vector<PartitionIds>(size) {}
        Partitioning(unsigned size, PartitionIds p) : std::vector<PartitionIds>(size,p){}
        ~Partitioning() { }
        friend std::ostream& operator<<(std::ostream& os, const Partitioning& part);
        void randomize(unsigned nParts);
        //return the random partitioning result of nParts-way partitioning
};


std::ostream& operator<<(std::ostream& os, const Partitioning& part);


/*___________________PartitionIds inline methods __________________ */

inline void PartitionIds::setToPart(unsigned part)
{
    _partitions =  (1<<part);
}


inline void PartitionIds::removeFromPart(unsigned part)
{
    _partitions &=  ~(1<<part);
}


inline void PartitionIds::setToAll(unsigned k)
{

    if (k==32)
        // this should not be necessary; next branch
        _partitions=0xffffffff;
    // should work always.  But at least on MSVC++
    // it returns that you're in *no* partitions
    // (instead of *every*)partition.  Reason
    // is unknown.  mro
    else
        _partitions =  ~(0xffffffff<<k);
}


inline void PartitionIds::addToPart(unsigned part)
{

    _partitions |=  (1<<part);
}


inline bool PartitionIds::isInPart(unsigned part) const
{


    return _partitions & (1<<part);

}


inline unsigned PartitionIds::lowestNumPart()    const
{
    //return the lowest numbered patition marked 'true'
    // return of 0-31 == lowest numbered partition

    if(_partitions & 0x1)
    	return 0;
    if(_partitions & 0x2)
    	return 1;
    if(!_partitions)
	return 32;
    unsigned bitVec = _partitions>>2;
    for(unsigned k = 2;;k++, bitVec>>=1)
    {
	if(bitVec & 0x1)
	   return k;
    }
}

inline unsigned PartitionIds::numberPartitions() const
{		//how many 1's are there in the partitionIds

    unsigned count = 0;
    unsigned bitVec = _partitions;

    if(bitVec)
	do {
	    count++;
	} while( bitVec &= bitVec-1);

    return count;
}


inline unsigned PartitionIds::numberPartitions(unsigned nParts) const
{
    //how many partitions are marked true 
    //anyone got a better name for this?
    unsigned count = 0;
    for(int k = nParts-1; k >= 0; k--)
        if(_partitions & (1<<k)) count++;
    return count;
}




std::ostream& operator<< (std::ostream& os, const PartitionIds& part)
{
    os<<"[ ";
    for(unsigned k = 0; k < 32; k++)
       if(part.isInPart(k))
                os<<k<<" ";
    os<<" ]"<<std::endl;

    return os;
}


std::ostream& operator<<(std::ostream& os, const Partitioning& part)
{
    os<<"Begining of the partitioning"<<std::endl;
	auto p = part ;
    os<< p;
    return os;
}

void Partitioning::randomize(unsigned nParts)
{
  randomNumber ru(0, nParts);
  for(std::vector<PartitionIds>::iterator pit = begin(); pit != end(); ++pit)
  {
    pit->setToPart( int(ru) );
  }
}

