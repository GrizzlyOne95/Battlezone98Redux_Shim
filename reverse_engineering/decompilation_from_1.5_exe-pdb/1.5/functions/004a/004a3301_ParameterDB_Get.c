/*
 * Entry: 004a3301
 * Name: ParameterDB::Get
 * Namespace: ParameterDB
 * Signature: bool Get(ParameterDB * this, uint param_1, uint param_2, bool * param_3, bool param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
ParameterDB::Get(ParameterDB *this,uint param_1,uint param_2,bool *param_3,bool param_4)

{
  char cVar1;
  char *pcVar2;
  bool bVar3;
  
  pcVar2 = Get(this,param_1,param_2);
  if (pcVar2 == (char *)0x0) {
    if (param_3 != (bool *)0x0) {
      *param_3 = param_4;
    }
    return false;
  }
  if (param_3 == (bool *)0x0) {
    return true;
  }
  cVar1 = *pcVar2;
  if (cVar1 < 'Z') {
    if (cVar1 == 'Y') goto LAB_004a3356;
    if (cVar1 == '0') {
LAB_004a335b:
      *param_3 = false;
      return true;
    }
    if (cVar1 == '1') goto LAB_004a3356;
    if ((cVar1 == 'F') || (cVar1 == 'N')) goto LAB_004a335b;
    bVar3 = cVar1 == 'T';
  }
  else {
    if ((cVar1 == 'f') || (cVar1 == 'n')) goto LAB_004a335b;
    if (cVar1 == 't') goto LAB_004a3356;
    bVar3 = cVar1 == 'y';
  }
  if (!bVar3) {
    *param_3 = param_4;
    return true;
  }
LAB_004a3356:
  *param_3 = true;
  return true;
}
