/*
 * Entry: 0050e493
 * Name: Defense_Map::Adjust_Defensive_Cell
 * Namespace: Defense_Map
 * Signature: int Adjust_Defensive_Cell(Defense_Map * this, int param_1, int param_2, char param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall
Defense_Map::Adjust_Defensive_Cell(Defense_Map *this,int param_1,int param_2,char param_3)

{
  int iVar1;
  
  if ((((param_1 < 0) || (param_2 < 0)) || ((int)(uint)this->width <= param_1)) ||
     ((int)(uint)this->height <= param_2)) {
    iVar1 = -10;
  }
  else {
    this->def_cells[param_1 + (uint)this->width * param_2] =
         this->def_cells[param_1 + (uint)this->width * param_2] + param_3;
    iVar1 = 0;
  }
  return iVar1;
}
