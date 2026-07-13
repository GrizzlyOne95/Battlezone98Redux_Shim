/*
 * Entry: 0050e4d0
 * Name: Defense_Map::Adjust_Defensive_Location
 * Namespace: Defense_Map
 * Signature: int Adjust_Defensive_Location(Defense_Map * this, float param_1, float param_2, char param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall
Defense_Map::Adjust_Defensive_Location(Defense_Map *this,float param_1,float param_2,char param_3)

{
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar1;
  
  _ftol2_sse();
  _ftol2_sse();
  iVar1 = Adjust_Defensive_Cell(this,extraout_EAX,extraout_EAX_00,param_3);
  return iVar1;
}
