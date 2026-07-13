/*
 * Entry: 00415c98
 * Name: Inst03MissionClass::Matches
 * Namespace: Inst03MissionClass
 * Signature: int Matches(Inst03MissionClass * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Inst03MissionClass::Matches(Inst03MissionClass *this,char *param_1)

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
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = _strnicmp(param_1,"play",4);
    iVar3 = -(uint)(iVar3 != 0);
  }
  return iVar3 + 1;
}
