/*
 * Entry: 005520a2
 * Name: MapList::GetName
 * Namespace: MapList
 * Signature: char * GetName(MapList * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall MapList::GetName(MapList *this,int param_1)

{
  char *pcVar1;
  
  if ((param_1 < 0) || ((int)this->s <= param_1)) {
    pcVar1 = (char *)0x0;
  }
  else {
    pcVar1 = (char *)this[1].hPlayerList[param_1 * 5].unused;
  }
  return pcVar1;
}
