/*
 * Entry: 0050e568
 * Name: Defense_Map::Reset_Next_Best_Cell_Index
 * Namespace: Defense_Map
 * Signature: void Reset_Next_Best_Cell_Index(Defense_Map * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Defense_Map::Reset_Next_Best_Cell_Index(Defense_Map *this)

{
  this->next_best_cell_index = this->max_cells + -1;
  return;
}
