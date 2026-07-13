/*
 * Entry: 005520c5
 * Name: MapList::GetName
 * Namespace: MapList
 * Signature: char * GetName(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall MapList::GetName(MapList *this)

{
  char *pcVar1;
  
  pcVar1 = GetName(this,this->count);
  return pcVar1;
}
