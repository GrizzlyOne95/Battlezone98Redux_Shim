/*
 * Entry: 00496bf5
 * Name: ModeList::RemoveAllModes
 * Namespace: ModeList
 * Signature: void RemoveAllModes(ModeList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ModeList::RemoveAllModes(ModeList *this)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    SetMode(this,iVar1,0,false);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0xb);
  return;
}
