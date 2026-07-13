/*
 * Entry: 0041627e
 * Name: Inst4XMissionClass::Matches
 * Namespace: Inst4XMissionClass
 * Signature: int Matches(Inst4XMissionClass * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Inst4XMissionClass::Matches(Inst4XMissionClass *this,char *param_1)

{
  char cVar1;
  char *_Str2;
  char *pcVar2;
  int iVar3;
  
  _Str2 = *(char **)&this->field_0x4;
  pcVar2 = _Str2;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar3 = _strnicmp(param_1,_Str2,(int)pcVar2 - (int)(_Str2 + 1));
  return (uint)(iVar3 == 0);
}
