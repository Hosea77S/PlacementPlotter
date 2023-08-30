#include "permute.h"



template<class T>
void reorderVector(std::vector<T>& vec,const Permutation& pm)
{
    myAssert(vec.size()==pm.getSize(),"Size mismatch during reordering");
    std::vector<T> tmpVec(vec.size());
    for(unsigned k=0;k<vec.size();k++) tmpVec[pm[k]]=vec[k];
    vec=tmpVec;
}


template<class T>
void reorderVectorBack(std::vector<T>& vec,const Permutation& pm)
{
    myAssert(vec.size()==pm.getSize(),"Size mismatch during reordering");
    std::vector<T> tmpVec(vec.size());
    for(unsigned k=0;k<vec.size();k++) tmpVec[k]=vec[pm[k]];
    vec=tmpVec;
}


void reorderBitVectorBack(bit_vector& bvec,const Permutation& pm);
void reorderBitVector(bit_vector& bvec,const Permutation& pm);

/*------------------------      INTERFACES END HERE    -------------------
------------------------ IMPLEMENTATION BEGINS HERE  -------------------*/

inline void _swapInsideNextLex(unsigned& a, unsigned& b)
{
    unsigned tmp=a;
    a=b;
    b=tmp;
}


inline bool Permutation::nextLexicographic()
{
    unsigned n=getSize();
    // unsigned* v=_meat;
    int k = n-2;        // 
    //
    while (k>=0 && _meat[k] > _meat[k+1])
        k--;
    if (k < 0)
        return 0;
    else
    {
        int j = n-1;     //
        while (_meat[k] > _meat[j])
            j--;
        _swapInsideNextLex(_meat[j],_meat[k]);
        int r = n-1;     //
        int s = k+1;
        while (r>s)
        {
            _swapInsideNextLex(_meat[r],_meat[s]);
            r--;
            s++;
        }
    }
    return 1;
}



Permutation::Permutation(const std::vector<double>& unsorted, double epsilon)
:Mapping(unsorted.size(),unsorted.size())
{
    std::vector<NumNum> data(unsorted.size());
    unsigned k;
    for(k=0;k<unsorted.size();k++)
    {
        data[k].first=unsorted[k];
        data[k].second=k;
    }
    std::sort(data.begin(),data.end(),CompareNumNum(epsilon));
    for(k=0;k<unsorted.size();k++) _meat[data[k].second]=k;
}


Permutation& Permutation::getInverse(Permutation& result) const
{
    // see comments next to declaration
    // NB: no need to check for surjectivity
    result=Permutation(getSize());
    unsigned i;
    for(i=0;i!=_meat.size();i++) result._meat[i]=(unsigned)-1;
    for(i=0;i<getSize();i++)
    {
        unsigned tmp=result[_meat[i]];
        myAssert(tmp==(unsigned)-1, "Can\'t invert permutation: not injective");
        result[_meat[i]]=i;
    };
    return result;
}


void reorderBitVector(bit_vector& bvec,const Permutation& pm)
{
    myAssert(bvec.size()==pm.getSize(),"Size mismatch during reordering");
    bit_vector tmpBVec(bvec.size());
    for(unsigned k=0;k<bvec.size();k++) tmpBVec[pm[k]]=bvec[k];
    bvec=tmpBVec;
}


void reorderBitVectorBack(bit_vector& bvec,const Permutation& pm)
{
    myAssert(bvec.size()==pm.getSize(),"Size mismatch during reordering");
    bit_vector tmpBVec(bvec.size());
    for(unsigned k=0;k<bvec.size();k++) tmpBVec[k]=bvec[pm[k]];
    bvec=tmpBVec;
}


std::ostream& operator<<(std::ostream& out, const Permutation& pm)
{
    out << " Permutation size : " << pm.getSize() << std::endl;
    for(unsigned i=0;i<pm.getSize();i++)
        out << i << " : " << pm[i] << std::endl;
    return out;
}
