/*
 * Entry: 005520d1
 * Name: MapList::GetMaxPlayers
 * Namespace: MapList
 * Signature: int GetMaxPlayers(MapList * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall MapList::GetMaxPlayers(MapList *this,int param_1)

{
  int iVar1;
  
  if ((param_1 < 0) || ((int)this->s <= param_1)) {
    iVar1 = 2;
  }
  else {
    iVar1 = this[1].hPlayerList[param_1 * 5 + 2].unused;
  }
  return iVar1;
}
