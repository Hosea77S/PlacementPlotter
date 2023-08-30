#ifndef _CONSTANTS_H
#define _CONSTANTS_H
 
namespace Constants
{
  // since the actual variables are inside a namespace, the forward declarations need to be inside a namespace as well
  extern  double SPL_HEIGHT;
  extern  double SPL_WIDTH ;
  extern  double PAD_WIDTH ; 
  extern  double PAD_HEIGHT;
  extern  double PAD_OFFSET; 
  extern  double PITCH ;
  extern  double SPL_DELAY ;
  extern  double JTL_DELAY ;
  extern  double JTL_HEIGHT;
  extern  double JTL_WIDTH ;
  extern  double SPEED_OF_PTL;  
  extern  double SLACK_UNCERTAINTY;  
  
  
  extern const int    OUT_PIN_1 ;
  extern const int    OUT_PIN_2 ;
  
  extern const double CELL_IN1_PIN_POS ;
  extern const double CELL_IN2_PIN_POS ;
  extern const double CELL_OUT_PIN_POS ;
  
  extern const double JTL_IN_PIN_POS ;
  extern const double JTL_OUT_PIN_POS ;
  
  extern const double CLK_IN_PIN_POS ;
  extern const double CLK_OUT_PIN_1_POS;	
  extern const double CLK_OUT_PIN_2_POS;		
  
  
  //lp based topology params
  extern const double ALPHA_TOP;  
  extern const double BETA_TOP;  
  
}
 
#endif
