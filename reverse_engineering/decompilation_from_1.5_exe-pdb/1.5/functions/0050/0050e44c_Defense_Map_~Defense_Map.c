/*
 * Entry: 0050e44c
 * Name: Defense_Map::~Defense_Map
 * Namespace: Defense_Map
 * Signature: void ~Defense_Map(Defense_Map * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Defense_Map::~Defense_Map(Defense_Map *this)

{
  Sortlist_Delete(this->best_cells);
  free(this->def_cells);
  return;
}
