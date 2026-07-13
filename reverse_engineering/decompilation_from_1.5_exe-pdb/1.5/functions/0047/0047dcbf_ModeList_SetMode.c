/*
 * Entry: 0047dcbf
 * Name: ModeList::SetMode
 * Namespace: ModeList
 * Signature: void SetMode(ModeList * this, int param_1, int param_2, bool param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ModeList::SetMode(ModeList *this,int param_1,int param_2,bool param_3)

{
  uint uVar1;
  
  if ((uint)param_1 < 0xb) {
    if ((this->activeSlot == param_1) && (this->modeList[param_1] != param_2)) {
      this->activeSlot = -1;
    }
    this->modeList[param_1] = param_2;
    uVar1 = 1 << ((byte)param_1 & 0x1f);
    if (param_3) {
      uVar1 = uVar1 | this->enabledMask;
    }
    else {
      uVar1 = ~uVar1 & this->enabledMask;
    }
    this->enabledMask = uVar1;
  }
  return;
}
