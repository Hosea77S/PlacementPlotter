#include "verbosity.h"



using std::ostream; using std::cout; using std::endl; ostream& operator<<(ostream& os, const Verbosity& verbsty) {
        unsigned numLevels=verbsty._levels.size();
        os << " Verbosity levels : " << numLevels << endl;
        os << " For actions : " << verbsty.getForActions() << ", "
           << " For sys resources : " << verbsty.getForSysRes() << ", "
           << " For major stats : " << verbsty.getForMajStats() << endl;
      
        if (numLevels > 3)
        {
          os << " Other levels : " ;
          for (unsigned i=3; i!=numLevels; ++i)
          {
                if ( i % 10 == 0 )
                {
                    if (i) os << endl;
                    os <<" ";
                }
                os<<std::setw(3)<<verbsty._levels[i]<<" ";
          }
          os << endl;
        }
    return os;
}
void Verbosity::_ctructFromString(const char* levels) {
   if (levels==NULL ||
       !strcmp(levels,"0") || !strcasecmp(levels,"silent"))
   {
      _levels.erase(_levels.begin()+3,_levels.end());
      return;
   }
   unsigned len=strlen(levels);
   char * levs=new char[len+1];
   for(unsigned c=0;c<len;c++)
   if (levels[c]=='_') levs[c]=' '; else levs[c]=levels[c];
   levs[len]='\0';
   unsigned numLev=0;
   char *start =levs;
   char *finish=levs;
   while (start<levs+len)
   {
      unsigned tmp=strtoul(start,&finish,10);
      if (start==finish) start++;
      else
      {
         myAssert(tmp<=INT_MAX,"Verbosity levels can't be >INT_MAX");
         myAssert(numLev<100,"This ctor can't work with 100+ verbosity levels");
         _levels[numLev]=tmp;
         start=finish;
         numLev++;
      }
   }
   myAssert(numLev>2," Can't ctruct Verbosity: need at least 3 levels\n ");
   _levels.erase(_levels.begin()+numLev,_levels.end());
   delete[] levs;
}
Verbosity::Verbosity(const char* levels) // space or underscore-separated unsigneds
:_levels(100,0)
{
  _ctructFromString(levels);
}
Verbosity::Verbosity(int argc, const char *argv[]) // catches -verb
:_levels(100,0)
{
 /* StringParam verb("verb",argc,argv);
    BoolParam helpRequest1("h",argc,argv);
    BoolParam helpRequest2("help",argc,argv);
    if (helpRequest1.found() || helpRequest2.found())
    {
      cout << " -verb 1_1_1 | silent " << endl;
      _levels.erase(_levels.begin()+3,_levels.end());
      _levels[0] = _levels[1] = _levels[2] = 1;
      return;
    }
  
    if (verb.found()) _ctructFromString(verb);
    else
    {
       _levels.erase(_levels.begin()+3,_levels.end());
       _levels[0] = _levels[1] = _levels[2] = 1;
    }
 */} Verbosity::Verbosity(): _levels(3,1) {
}
Verbosity::Verbosity(const std::vector<unsigned>& levels): _levels(levels) {
   myAssert(levels.size()>=3,
            "Can not initialize verbosity --- too few levels\n ");
}
Verbosity::Verbosity(unsigned numLevels, unsigned ForActions,
                     unsigned ForSysRes, unsigned ForMajStats, ...): _levels(numLevels,0) { /* myAssert(numLevels>=3,"Can not initialize verbosity --- too few levels\n ");
   _levels[0]=ForActions;
   _levels[1]=ForSysRes;
   _levels[2]=ForMajStats;
   va_list ap;
   va_start(ap,ForMajStats);
   for(unsigned k=3;k<numLevels;k++)
   {
     _levels[k]=va_arg(ap,unsigned);
     myAssert(_levels[k]<INT_MAX/2," Verbosity levels can't be > INT_MAX /2");
   }
 */} unsigned & Verbosity::operator[](unsigned diagType) {
   myAssert(diagType<_levels.size(),"Inexistant diagnostic type");
   return _levels[diagType];
}
