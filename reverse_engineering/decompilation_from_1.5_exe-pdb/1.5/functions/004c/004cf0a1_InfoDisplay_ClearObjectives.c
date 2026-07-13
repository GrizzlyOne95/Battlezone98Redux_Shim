/*
 * Entry: 004cf0a1
 * Name: InfoDisplay::ClearObjectives
 * Namespace: InfoDisplay
 * Signature: void ClearObjectives(InfoDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall InfoDisplay::ClearObjectives(InfoDisplay *this)

{
  MessageInfo *pMVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  char **ppcVar5;
  float fVar6;
  
  iVar4 = 0;
  if (0 < this->objectiveCount) {
    ppcVar5 = &this->objectiveMessage[0].text;
    do {
      pMVar1 = (MessageInfo *)(ppcVar5 + -4);
      pcVar2 = (char *)(ppcVar5 + -3);
      pMVar1->name[0] = '\0';
      pMVar1->name[1] = '\0';
      pMVar1->name[2] = '\0';
      pMVar1->name[3] = '\0';
      pcVar3 = (char *)(ppcVar5 + -2);
      pcVar2[0] = '\0';
      pcVar2[1] = '\0';
      pcVar2[2] = '\0';
      pcVar2[3] = '\0';
      pcVar3[0] = '\0';
      pcVar3[1] = '\0';
      pcVar3[2] = '\0';
      pcVar3[3] = '\0';
      *(char *)((int)(ppcVar5 + -1) + 0) = '\0';
      *(char *)((int)(ppcVar5 + -1) + 1) = '\0';
      if (*ppcVar5 != (char *)0x0) {
        free(*ppcVar5);
        *ppcVar5 = (char *)0x0;
      }
      ppcVar5[1] = (char *)0x0;
      iVar4 = iVar4 + 1;
      ppcVar5 = ppcVar5 + 6;
    } while (iVar4 < this->objectiveCount);
  }
  this->objectiveCount = 0;
  fVar6 = Get_TimeLocal();
  this->objectiveLast = fVar6;
  return;
}
