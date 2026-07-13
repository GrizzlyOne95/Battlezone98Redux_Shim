/*
 * Entry: 00551d3e
 * Name: MapList::Name
 * Namespace: MapList
 * Signature: char * Name(MapList * this, ulong param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall MapList::Name(MapList *this,ulong param_1)

{
  char *pcVar1;
  
  if (param_1 < this->s) {
    pcVar1 = (char *)this[1].hPlayerList[param_1 * 5 + 3].unused;
  }
  else {
    pcVar1 = "";
  }
  return pcVar1;
}
