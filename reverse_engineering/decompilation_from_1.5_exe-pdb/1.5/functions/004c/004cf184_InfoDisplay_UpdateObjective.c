/*
 * Entry: 004cf184
 * Name: InfoDisplay::UpdateObjective
 * Namespace: InfoDisplay
 * Signature: void UpdateObjective(InfoDisplay * this, char * param_1, long param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
InfoDisplay::UpdateObjective(InfoDisplay *this,char *param_1,long param_2,float param_3)

{
  int iVar1;
  int iVar2;
  MessageInfo *_Str1;
  float fVar3;
  
  iVar2 = 0;
  if (0 < this->objectiveCount) {
    _Str1 = this->objectiveMessage;
    do {
      iVar1 = _strnicmp(_Str1->name,param_1,0xe);
      if (iVar1 == 0) {
        _Str1->color = param_2;
        fVar3 = Get_TimeLocal();
        this->objectiveLast = fVar3 + 5.0;
        return;
      }
      iVar2 = iVar2 + 1;
      _Str1 = _Str1 + 1;
    } while (iVar2 < this->objectiveCount);
  }
  return;
}
