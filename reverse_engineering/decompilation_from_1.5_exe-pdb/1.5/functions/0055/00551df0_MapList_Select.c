/*
 * Entry: 00551df0
 * Name: MapList::Select
 * Namespace: MapList
 * Signature: char * Select(MapList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall MapList::Select(MapList *this,char *param_1)

{
  HWND__ *pHVar1;
  int iVar2;
  
  this->count = 0;
  iVar2 = FindIndex(this,param_1);
  if (-1 < iVar2) {
    pHVar1 = this[1].hPlayerList;
    this->count = iVar2;
    param_1 = (char *)pHVar1[iVar2 * 5 + 3].unused;
  }
  return param_1;
}
