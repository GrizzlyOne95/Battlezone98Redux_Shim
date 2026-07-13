/*
 * Entry: 0050e463
 * Name: Defense_Map::Reset_Defensive_Map
 * Namespace: Defense_Map
 * Signature: void Reset_Defensive_Map(Defense_Map * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Defense_Map::Reset_Defensive_Map(Defense_Map *this)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  if (this->height != '\0') {
    uVar1 = (uint)this->width;
    do {
      iVar2 = 0;
      if (uVar1 != 0) {
        do {
          this->def_cells[iVar2 + uVar1 * iVar3] = '\0';
          uVar1 = (uint)this->width;
          iVar2 = iVar2 + 1;
        } while (iVar2 < (int)uVar1);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (int)(uint)this->height);
  }
  return;
}
