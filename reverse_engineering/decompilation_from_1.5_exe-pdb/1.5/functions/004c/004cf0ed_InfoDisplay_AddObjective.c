/*
 * Entry: 004cf0ed
 * Name: InfoDisplay::AddObjective
 * Namespace: InfoDisplay
 * Signature: void AddObjective(InfoDisplay * this, char * param_1, long param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
InfoDisplay::AddObjective(InfoDisplay *this,char *param_1,long param_2,float param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  long lVar4;
  void *pvVar5;
  float fVar6;
  
  iVar2 = this->objectiveCount;
  this->objectiveLast = param_3 + this->objectiveLast;
  pcVar3 = param_1;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)this + ((iVar2 * 0x18 + 0xc) - (int)param_1)] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  this->objectiveMessage[iVar2].text = (char *)0x0;
  lVar4 = GetItemSize(param_1);
  if (0 < lVar4) {
    pcVar3 = malloc(lVar4 + 1);
    this->objectiveMessage[iVar2].text = pcVar3;
    pvVar5 = UseItem(param_1);
    memcpy(this->objectiveMessage[iVar2].text,pvVar5,lVar4);
    this->objectiveMessage[iVar2].text[lVar4] = '\0';
    UnlockItem(param_1);
    this->objectiveMessage[iVar2].color = param_2;
    fVar6 = Get_TimeLocal();
    this->objectiveCount = this->objectiveCount + 1;
    this->objectiveLast = fVar6 + 5.0;
  }
  return;
}
