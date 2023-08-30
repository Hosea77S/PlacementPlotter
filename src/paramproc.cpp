#include "paramproc.h"



static char _uninitialized[]="Uninitialized";

Param::Param(Type pt,int argc, const char * const argv[])
: _b(false), _on(false), _i(INT_MAX), _u(unsigned(-1)), _d(-1.29384756657), 
  _s(_uninitialized), _pt(pt), _key("")
{
  myAssert(pt==NOPARAM," This constructor can only work with Param:NOPARAM\n");
  (void)argv; // please compiler 
   
  _b=(argc<2?true:false);
  return;
} 

Param::Param (const char * key, Type pt,int argc, const char * const argv[])
: _b(false), _on(false), _i(-1), _u(unsigned(-1)), _d(-1.23456), 
  _s(_uninitialized), _pt(pt), _key(key)
{
  myAssert(strlen(_key)>0," Zero length key for command line parameter");
  
  int n=0;
  if (_pt==NOPARAM)
  {
     if (argc<2)  _b=true; 
     else _b=false;
     return;
  }
  while ( ++n < argc && ! found())
  {
     if (argv[n][0]=='-' || argv[n][0]=='+')
     {
         const char * start=argv[n]+1;
         if (argv[n][0]=='-')
            {
                if (argv[n][1]=='-') start++;
            }
         else
            _on=true;  

         if (strcasecmp(start,_key)==0)
         {
              _b=true;
              if (n+1 < argc)
              {
                 switch (_pt)
                 {
                    case BOOL	  : break;
                    case INT      : _i=atoi(argv[n+1]); break;
                    case UNSIGNED : _u=strtoul(argv[n+1],(char**)NULL,10);
                                                        break;
                    case DOUBLE   : _d=atof(argv[n+1]); break;
                    case STRING   : _s=argv[n+1];       break;
                    default : myAssert(0," Unknown command line parameter");
                 }
              }
          }
      }
  }
}

bool      Param::found()       const
{ return _b; }

bool      Param::on()          const // true for +option, false otherwise
{ 
  myAssert(found()," Parameter not found: you need to check for this first\n");
  return _on;
}

int       Param::getInt()      const
{ 
   myAssert(_pt==INT," Parameter is not INT ");
   myAssert(found()," Parameter not found: you need to check for this first\n");
   return _i;
}

unsigned  Param::getUnsigned() const
{ 
   myAssert(_pt==UNSIGNED," Parameter is not UNSIGNED ");
   myAssert(_u >= 0," Parameter is not UNSIGNED ");   
   myWarn3(found(),
      " UNSIGNED Parameter ", _key," not found: you need to check for this first\n");
   return _u;
}

double    Param::getDouble()   const
{ 
   myAssert(_pt==DOUBLE," Parameter is not DOUBLE "); 
   myAssert(found(),
      " DOUBLE parameter not found: you need to check for this first\n");
   return _d;
}

const char * Param::getString()   const
{ 
   myAssert(_pt==STRING," Parameter is not STRING"); 
   myAssert(found(),
      " STRING parameter not found: you need to check for this first\n");
   return _s;
}

