/*
 * Entry: 00551d18
 * Name: MapList::OptionsType
 * Namespace: MapList
 * Signature: MapOptionsType OptionsType(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MapOptionsType __thiscall MapList::OptionsType(MapList *this)

{
  char cVar1;
  uint uVar2;
  MapTypeInfo *pMVar3;
  
  cVar1 = Type(this);
  uVar2 = 0;
  pMVar3 = mapTypeInfo;
  do {
    if (cVar1 == pMVar3->type) {
      return mapTypeInfo[uVar2].options;
    }
    uVar2 = uVar2 + 1;
    pMVar3 = pMVar3 + 1;
  } while (uVar2 < 5);
  return MAP_OPTIONS_DEATHMATCH;
}
