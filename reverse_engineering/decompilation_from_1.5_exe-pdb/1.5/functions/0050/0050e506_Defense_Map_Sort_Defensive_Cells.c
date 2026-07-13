/*
 * Entry: 0050e506
 * Name: Defense_Map::Sort_Defensive_Cells
 * Namespace: Defense_Map
 * Signature: void Sort_Defensive_Cells(Defense_Map * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Defense_Map::Sort_Defensive_Cells(Defense_Map *this)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  Sortlist_Clear(this->best_cells);
  iVar3 = 0;
  if (this->height != '\0') {
    uVar1 = (uint)this->width;
    do {
      iVar4 = 0;
      if (uVar1 != 0) {
        do {
          iVar2 = (uint)this->width * iVar3;
          Sortlist_Add_Data(this->best_cells,(void *)(iVar2 + iVar4),
                            (double)(int)this->def_cells[iVar4 + iVar2]);
          uVar1 = (uint)this->width;
          iVar4 = iVar4 + 1;
        } while (iVar4 < (int)uVar1);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (int)(uint)this->height);
  }
  return;
}
