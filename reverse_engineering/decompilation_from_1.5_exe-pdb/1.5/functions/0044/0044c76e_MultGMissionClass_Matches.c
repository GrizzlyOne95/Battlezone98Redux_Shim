/*
 * Entry: 0044c76e
 * Name: MultGMissionClass::Matches
 * Namespace: MultGMissionClass
 * Signature: int Matches(MultGMissionClass * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall MultGMissionClass::Matches(MultGMissionClass *this,char *param_1)

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
