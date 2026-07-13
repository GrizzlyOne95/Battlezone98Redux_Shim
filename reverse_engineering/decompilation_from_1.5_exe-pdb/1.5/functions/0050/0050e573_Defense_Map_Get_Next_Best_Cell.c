/*
 * Entry: 0050e573
 * Name: Defense_Map::Get_Next_Best_Cell
 * Namespace: Defense_Map
 * Signature: char Get_Next_Best_Cell(Defense_Map * this, float * param_1, float * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char __thiscall Defense_Map::Get_Next_Best_Cell(Defense_Map *this,float *param_1,float *param_2)

{
  byte bVar1;
  char extraout_AL;
  void *pvVar2;
  
  pvVar2 = Sortlist_Return_Data_By_Number(this->best_cells,(int)this->next_best_cell_index);
  Sortlist_Return_Key_By_Number(this->best_cells,(int)this->next_best_cell_index);
  _ftol2_sse();
  bVar1 = this->width;
  this->next_best_cell_index = this->next_best_cell_index + -1;
  *param_1 = (float)((int)pvVar2 % (int)(uint)bVar1) * this->cell_width + this->x_base;
  *param_2 = (float)((int)pvVar2 / (int)(uint)bVar1) * this->cell_height + this->z_base;
  return extraout_AL;
}
