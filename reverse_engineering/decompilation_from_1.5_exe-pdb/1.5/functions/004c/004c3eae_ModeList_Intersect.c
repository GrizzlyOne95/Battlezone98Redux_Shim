/*
 * Entry: 004c3eae
 * Name: ModeList::Intersect
 * Namespace: ModeList
 * Signature: void Intersect(ModeList * this, ModeList * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ModeList::Intersect(ModeList *this,ModeList *param_1)

{
  uint uVar1;
  ModeList *pMVar2;
  int iVar3;
  
  iVar3 = 0xb;
  pMVar2 = this;
  do {
    if (pMVar2->modeList[0] != *(int *)(((int)param_1 - (int)this) + (int)pMVar2)) {
      pMVar2->modeList[0] = 0;
    }
    pMVar2 = (ModeList *)(pMVar2->modeList + 1);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  this->enabledMask = this->enabledMask & param_1->enabledMask;
  uVar1 = this->activeSlot;
  if (uVar1 == param_1->activeSlot) {
    if (uVar1 < 0xb) {
      iVar3 = this->modeList[uVar1];
    }
    else {
      iVar3 = 0;
    }
    if (iVar3 != 0) {
      return;
    }
  }
  this->activeSlot = -1;
  return;
}
