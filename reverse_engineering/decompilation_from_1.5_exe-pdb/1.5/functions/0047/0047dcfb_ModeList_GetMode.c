/*
 * Entry: 0047dcfb
 * Name: ModeList::GetMode
 * Namespace: ModeList
 * Signature: int GetMode(ModeList * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ModeList::GetMode(ModeList *this,int param_1)

{
  int iVar1;
  
  if ((uint)param_1 < 0xb) {
    iVar1 = this->modeList[param_1];
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}
