/*
 * Entry: 0047e89f
 * Name: ModeList::FindMode
 * Namespace: ModeList
 * Signature: int FindMode(ModeList * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ModeList::FindMode(ModeList *this,int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (this->modeList[iVar1] == param_1) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0xb);
  return -1;
}
