#include "mapping.h"



/*------------------------      INTERFACES END HERE    -------------------
------------------------  IMPLEMENTATIONS START HERE -------------------*/



//using std::random_sample;
using std::random_shuffle;



Mapping::Mapping(unsigned sourceSize, unsigned targetSize, Mapping::Example ex):
_destSize(targetSize), _meat(sourceSize)
{
	myAssert(sourceSize<=targetSize,
	" Map not injective: source set bigger than target set" );        
        unsigned k=0;
	switch (ex) 
        {
		case Identity :
                        for(k=0; k!=_meat.size(); k++) _meat[k]=k;
                        return;
		case _Reverse : 
                     {
                        unsigned N=_meat.size();
                        for(k=0; k!=N; k++) _meat[k]=(N-1)-k;
                        return;
                     }
		case _Random  :
                     {
			std::vector<unsigned> zero2n(targetSize);
                        for(unsigned k=0; k!=targetSize; k++) zero2n[k]=k;
			randomNumber rng(0,10);
                        //RandomRawUnsigned rng("Mapping::Mapping,case _Random,rng");
			//random_sample(zero2n.begin(),zero2n.end(),
			//_meat.begin(),_meat.end(),rng);
			random_shuffle(_meat.begin(),_meat.end(),rng);
			return;
		     }
		case _RandomOrdered  :
                     {
			std::vector<unsigned> zero2n(targetSize);
                        for(unsigned k=0; k!=targetSize; k++) zero2n[k]=k;
			randomNumber rng(0,10);
                        //RandomRawUnsigned rng("Mapping::Mapping,case _RandomOrdered,rng");
                        //random_sample_n(zero2n.begin(),zero2n.end(),
                        //_meat.begin(), sourceSize, rng);
			return;
	             }
		default: myAssert(0," Unknown mapping example");
	}
}


Mapping::Mapping(UnaryOp unop, const Mapping& arg) {
	unsigned i=0;
	switch (unop) {
		case COMPLEMENT : {
			_destSize=arg.getDestSize();
			std::vector<unsigned> partInv;
			arg.getPartialInverse(partInv);
			for(i=0;i<arg.getDestSize();i++)
			if ( partInv[i]==unsigned(-1) )
						_meat.push_back(i);
			break;
		}

		default         : myAssert(0," Unknown unary mapping operation ");
	}
}


Mapping::Mapping(const Mapping& arg1, BinaryOp binop, const Mapping& arg2) {
	unsigned i=0;
	switch (binop) {
		case COMPOSE  : {
			myAssert(arg1.getSourceSize()>=arg2.getDestSize(),
			"Can\'t compose mappings : size mismatch ");
			_destSize=arg1.getDestSize();
			_meat=std::vector<unsigned>(arg2.getSourceSize());
			for(i=0;i<_meat.size();i++) _meat[i]=arg1[arg2[i]];
			break;
		}

		case MINUS    : {
			myAssert(arg1.getDestSize()>=arg2.getDestSize(),
			"Can\'t subtract subsets : size mismatch");
			_destSize=arg1.getDestSize();
			std::vector<unsigned> partInv1, partInv2;
			arg1.getPartialInverse(partInv1);
			arg2.getPartialInverse(partInv2);
			for(i=0;i<arg1.getDestSize();i++)
			if ( partInv1[i]!=unsigned(-1) &&
				partInv2[i]==unsigned(-1)    )
							_meat.push_back(i);
			break;
		}

		case UNION   : {
			myAssert(arg1.getDestSize()>=arg2.getDestSize(),
			"Can\'t union subsets : size mismatch ");
			_destSize=arg1.getDestSize();
			std::vector<unsigned> partInv1, partInv2;
			arg1.getPartialInverse(partInv1);
			arg2.getPartialInverse(partInv2);
			for(i=0;i<arg1.getDestSize();i++)
			if ( partInv1[i]!=unsigned(-1) ||
				partInv2[i]!=unsigned(-1)    )
							_meat.push_back(i);
			break;
		}

		case XSECT   : {
			myAssert(arg1.getDestSize()>=arg2.getDestSize(),
			"Can\'t union subsets : size mismatch");
			_destSize=arg1.getDestSize();
			std::vector<unsigned> partInv1, partInv2;
			arg1.getPartialInverse(partInv1);
			arg2.getPartialInverse(partInv2);
			for(i=0;i<arg1.getDestSize();i++)
			if ( partInv1[i]!=unsigned(-1) &&
				partInv2[i]!=unsigned(-1)    )
							_meat.push_back(i);
			break;
		}
		default       : myAssert(0," Unknown binary mapping operation ");
	}
}


std::vector<unsigned>& Mapping::
getPartialInverse(std::vector<unsigned>& result) const {
	// see comments next to declaration
	unsigned i;
	result.reserve(getDestSize());
	for(i=0;i<getDestSize();i++) result.push_back((unsigned)-1);
	for(i=0;i<getSourceSize();i++) {
		myAssert(result[_meat[i]]==(unsigned)-1,"Mapping not injective");
		result[_meat[i]]=i;
	};
	return result;
}


std::ostream& operator<<(std::ostream& out, const Mapping& mp) {
	out << " Mapping source size : " << mp.getSourceSize()
	<< "    destination size : " << mp.getDestSize() << std::endl;
	for(unsigned i=0;i<mp.getSourceSize();i++)
		out << i << " : " << mp[i] << std::endl;
	return out;
}

