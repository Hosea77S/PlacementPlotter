#include "dbSym.h"



// definitions of static class members

std::string Symmetry::text = ""; 
std::string Orient::text = "";

Symmetry::Symmetry(const std::string txt)
{
    if ( txt == "R90" || txt == "r90" ) rot90=true; else rot90=false;
    if ( txt == "Y"   || txt == "y"   ) y=true;     else y=false;
    if ( txt == "X"   || txt == "x"   ) x=true;     else x=false;
}

Symmetry::operator const std::string() const
{
	std::string txt;
    if (rot90) txt == " R90";
    if (y)     txt == " Y";
    if (x)     txt == " X";
    return text;
}


Orient::Orient(const std::string txt)
{
    if ( txt == "F" || txt == "f") _faceUp=false;  else _faceUp=true;
    if ( txt == "N" || txt == "n") { _angle=0; return;}
    if ( txt == "E" || txt == "e") { _angle=1; return;}
    if ( txt == "S" || txt == "s") { _angle=2; return;}
    if ( txt == "W" || txt == "w") { _angle=3; return;}
}

Orient::operator const std::string() const
{
    text = _faceUp ? " ":"F";
    switch (_angle)
    {
        case 0 : text = "N "; break;
        case 1 : text = "E "; break;
        case 2 : text = "S "; break;
        case 3 : text = "W "; break;
    }
    return text;
}


OrientationSet::OrientationSet (const Symmetry& sym, const Orient& orient)
{
  unsigned r = 0;
  unsigned ori= orient.getAngle() + (orient.isFaceUp() ? 1 : 0);

//  std::cout << "sym: " << sym << " orient " << orient << std::endl;
//  std::cout << "sym, or: " << unsigned(sym) << " " << or << std::endl;
  
  switch (unsigned(sym)) {
  case 0:   // No symmetry
    switch (ori) {
    case 1: r = 1; // N
	    break;
    case 0: r = 2; // FN
	    break;
    case 91: r = 4; // E
	    break;
    case 90: r = 8; // FE
	    break;
    case 181: r = 16; // S
	    break;
    case 180: r = 32; // FS
	    break;
    case 271: r = 64; // W
	    break;
    case 270: r = 128; // FW
	    break;
    default:
	std::cout << "bad value case 0: " << ori << std::endl;    
    }
  case 1:    // X only
    switch (ori) {
    case 1: case 180:
      r = 33; // N+FS
      break;
    case 0: case 181:
      r = 18; // FN+S
      break;
    case 90: case 91:
      r = 12; // E+FE
      break;
    case 270: case 271:
      r = 192; // W+FW
      break;
    default:
      std::cout << "bad value case 1: " << ori << std::endl;
    }
    break;
  case 2:    // Y only
    switch (ori) {
    case 0: case 1:
      r = 3; // N+FN
      break;
    case 91: case 270:
      r = 132; // E+FW
      break;
    case 90: case 271:
      r = 72; // FE+W
      break;
    case 180: case 181:
      r = 48; // S+FS
      break;
    default:
      std::cout << "bad value case 2: " << ori << std::endl;
    }
    break;
  case 3:    // X and Y 
    switch (ori) {
    case 0: case 1: case 180: case 181:
      r = 51; // N+FN+S+FS
      break;
    default:
      r = 214; // E+FE+W+FW
    }
    break;
  case 4:    // Rot90 only
    switch (ori) {
    case 1: case 91: case 181: case 271:
      r = 85; // N+E+S+W
      break;
    default:
      r = 170; // FN+FE+FS+FW
    }
    break;
    
  default:  // all other cases are the same
    r = 255;
  }
	
  // Now just set all the bits

  N   = r%2; r /= 2;
  FN  = r%2; r /= 2;
  E   = r%2; r /= 2;
  FE  = r%2; r /= 2;
  S   = r%2; r /= 2;
  FS  = r%2; r /= 2;
  W   = r%2; r /= 2;
  FW  = r%2;
  
}

OrientationSet::OrientationSet (unsigned x)
{
  N   = x%2; x /= 2;
  FN  = x%2; x /= 2;
  E   = x%2; x /= 2;
  FE  = x%2; x /= 2;
  S   = x%2; x /= 2;
  FS  = x%2; x /= 2;
  W   = x%2; x /= 2;
  FW  = x%2;
}

Orient OrientationSet::getNth(unsigned n)
{
  if (N)
  {
    if (n == 0) return Orient("N");
    else --n;
  }
  if (FN)
  {
    if (n == 0) return Orient("FN");
    else --n;
  }
  if (E)
  {
    if (n == 0) return Orient("E");
    else --n;
  }
  if (FE)
  {
    if (n == 0) return Orient("FE");
    else --n;
  }
  if (S)
  {
    if (n == 0) return Orient("S");
    else --n;
  }
  if (FS)
  {
    if (n == 0) return Orient("FS");
    else --n;
  }
  if (W)
  {
    if (n == 0) return Orient("W");
    else --n;
  }
  if (FW)
  {
    if (n == 0) return Orient("FW");
    else --n;
  }
  myAssert(false, "Requested non-existent member of orientation set.");

  return Orient(NULL); //satisfy compiler
}
  
Orient OrientationSet::getOrient ()
{
  myAssert(isNotEmpty(),"Tried to extract orientation from empty set");
  if (N) return(Orient("N"));
  else if (FN) return(Orient("FN"));
  else if (E) return(Orient("E"));
  else if (FE) return(Orient("FE"));
  else if (S) return(Orient("S"));
  else if (FS) return(Orient("FS"));
  else if (W) return(Orient("W"));
  else if (FW) return(Orient("FW"));
  else
    myAssert(false,"Logic failure in OrientationSet::getOrient");

  return Orient(NULL); //satisfy compiler
}

std::ostream &operator << (std::ostream &out, const OrientationSet& os)
{
  out << "OrientationSet{";
  if (os.N) out << "N ";
  if (os.FN) out << "FN " ;
  if (os.E) out  << "E ";
  if (os.FE) out << "FE ";
  if (os.S) out << "S ";
  if (os.FS) out << "FS " ;
  if (os.W) out  << "W ";
  if (os.FW) out << "FW ";
  out << "}" ;
  return out;
}

std::ostream& operator<<(std::ostream& out, const Symmetry& sym)
{
    out << (const std::string)sym;
    return out;
};

std::ostream& operator<<(std::ostream& out, const Orient& ori)
{
    out << (const std::string) ori;
    return out;
};

