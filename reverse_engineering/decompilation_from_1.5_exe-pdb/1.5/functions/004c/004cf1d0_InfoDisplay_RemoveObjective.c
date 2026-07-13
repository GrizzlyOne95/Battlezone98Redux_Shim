/*
 * Entry: 004cf1d0
 * Name: InfoDisplay::RemoveObjective
 * Namespace: InfoDisplay
 * Signature: void RemoveObjective(InfoDisplay * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall InfoDisplay::RemoveObjective(InfoDisplay *this,char *param_1)

{
  int iVar1;
  int iVar2;
  MessageInfo *pMVar3;
  
  iVar2 = 0;
  if (0 < this->objectiveCount) {
    pMVar3 = this->objectiveMessage;
    do {
      iVar1 = _strnicmp(pMVar3->name,param_1,0xe);
      if (iVar1 == 0) {
        if (pMVar3->text != (char *)0x0) {
          free(pMVar3->text);
          pMVar3->text = (char *)0x0;
        }
        this->objectiveCount = this->objectiveCount + -1;
        if (iVar2 < this->objectiveCount) {
          memmove(this->objectiveMessage + iVar2,this->objectiveMessage + iVar2 + 1,
                  (this->objectiveCount - iVar2) * 0x18);
        }
        pMVar3 = this->objectiveMessage + this->objectiveCount;
        for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
          pMVar3->name[0] = '\0';
          pMVar3->name[1] = '\0';
          pMVar3->name[2] = '\0';
          pMVar3->name[3] = '\0';
          pMVar3 = (MessageInfo *)(pMVar3->name + 4);
        }
        return;
      }
      iVar2 = iVar2 + 1;
      pMVar3 = pMVar3 + 1;
    } while (iVar2 < this->objectiveCount);
  }
  return;
}
