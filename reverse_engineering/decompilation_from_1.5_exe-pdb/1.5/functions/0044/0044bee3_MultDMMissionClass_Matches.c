/*
 * Entry: 0044bee3
 * Name: MultDMMissionClass::Matches
 * Namespace: MultDMMissionClass
 * Signature: int Matches(MultDMMissionClass * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall MultDMMissionClass::Matches(MultDMMissionClass *this,char *param_1)

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
  if ((iVar3 != 0) && (iVar3 = _strnicmp(param_1,"mult01",6), iVar3 != 0)) {
    iVar3 = _strnicmp(param_1,"mult03",6);
    return (uint)(iVar3 == 0);
  }
  return 1;
}
