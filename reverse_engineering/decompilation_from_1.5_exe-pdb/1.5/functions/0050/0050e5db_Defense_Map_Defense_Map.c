/*
 * Entry: 0050e5db
 * Name: Defense_Map::Defense_Map
 * Namespace: Defense_Map
 * Signature: Defense_Map * Defense_Map(Defense_Map * this, uchar param_1, uchar param_2, float param_3, float param_4, float param_5, float param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Defense_Map * __thiscall
Defense_Map::Defense_Map
          (Defense_Map *this,uchar param_1,uchar param_2,float param_3,float param_4,float param_5,
          float param_6)

{
  char *pcVar1;
  tag_sortlist *ptVar2;
  
  this->cell_width = param_3;
  this->width = param_1;
  this->height = param_2;
  this->cell_height = param_4;
  this->x_base = param_5;
  this->z_base = param_6;
  this->max_cells = (ushort)param_1 * (ushort)param_2;
  pcVar1 = malloc((int)(short)((ushort)param_1 * (ushort)param_2));
  this->def_cells = pcVar1;
  ptVar2 = Sortlist_New((int)this->max_cells);
  this->best_cells = ptVar2;
  this->next_best_cell_index = this->max_cells + -1;
  Reset_Defensive_Map(this);
  return this;
}
