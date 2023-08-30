#include "dbTypes.h"


dbPinType::dbPinType (std::string dir){
	
	if      (dir == "INPUT" || dir == "IN") _dir = INPUT;
	else if (dir == "OUTPUT" || dir == "OUT") _dir = OUTPUT;
	else if (dir == "BIDIR"  || dir == "BI") _dir = BIDIR;
	else _dir = UNKNOWN;
	
}

dbPinType::operator std::string() const {
	std::string text;
	switch (_dir){
		case INPUT: text = "INPUT"; break;
		case OUTPUT: text = "OUTPUT";  break;
		case BIDIR: text = "BIDIR";  break;
		case UNKNOWN: text = "UNKNOWN";  break;
	}
	return text;
}




dbNetType::dbNetType(std::string txt)
{
	this->_text = txt;
    if(!(txt.size())){ _type = UNKNOWN;}
    else if(txt == "SIGNAL"){ _type = SIGNAL;}
    else if(txt ==  "POWER"){ _type = POWER; }  
    else if(txt == "GROUND"){ _type = GROUND;}  
    else if(txt ==  "CLOCK"){ _type = CLOCK; }  
    else {_type = UNKNOWN;}
	
}

dbNetType::operator std::string() const {
	std::string text;
	switch (_type){
		case SIGNAL: text = "SIGNAL"; break;
		case POWER : text = "POWER";  break;
		case GROUND: text = "GROUND";  break;
		case CLOCK : text = "CLOCK";  break;
		case UNKNOWN:text = "UNKNOWN"; break;
	}        
	return text;
}



dbCellType::dbCellType(std::string mtype, std::string stype)
{
    
    if     ( mtype.size() == 0){ _mType = MacroUNKNOWN; }
    else if( mtype ==    "IO") { _mType = IO;  }
    else if( mtype ==   "CORE"){ _mType = CORE;}
	else if( mtype ==  "BLOCK"){ _mType = BLOCK;}
    else _mType = MacroUNKNOWN;
   
    if( isCore() )
    { 
      	if     ( stype.size() == 0){ _subType = COREUNKNOWN; }
		else if( stype == "SC" ) { _subType = SC; }
		else if( stype == "CC" ){ _subType = CC;}
		else _subType = COREUNKNOWN;
	
    } else if ( isIO() )
    {
      	if ( stype.size() == 0) 	     { _subType = IOUNKNOWN;}
      	else if( stype == "INPUT" || stype == "PI" ) { _subType = PI; }
      	else if( stype == "OUTPUT"|| stype == "PO" ) { _subType = PO;}
      	else if( stype == "INOUT" || stype == "PIO") { _subType = PIO; }
      	else 							 { _subType = IOUNKNOWN;}
    } else  
	_subType = IOUNKNOWN;        
}




dbCellType::operator std::string() const
{
    std::string text;
    switch (_mType)
    {
        case BLOCK        : text = "BLOCK";   break;
        case MacroUNKNOWN : text = "UNKNOWN"; break;
        case IO   : text = "IO "; 
            switch(_subType) 
            { 
                case PI       : text += "PI";     break; 
                case PO       : text += "PO";     break; 
                case PIO      : text += "PIO";    break; 
                case IOUNKNOWN : text += "UNKNOWN";break; 
            }; break; 
            
		case CORE    : text = "CORE ";
			switch(_subType)
			{
				case SC         : text += "SC";     break;
				case CC         : text += "CC";     break;
				case COREUNKNOWN  : text += "UNKNOWN";  break;
			}; break;
    };
    return text;
}        



