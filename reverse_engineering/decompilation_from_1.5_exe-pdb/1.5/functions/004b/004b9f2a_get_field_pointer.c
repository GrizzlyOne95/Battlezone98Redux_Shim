/*
 * Entry: 004b9f2a
 * Name: get_field_pointer
 * Namespace: Global
 * Signature: FIELD_DESC * get_field_pointer(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FIELD_DESC * __cdecl get_field_pointer(char *param_1)

{
  int iVar1;
  FIELD_DESC *pFVar2;
  uint uVar3;
  
  uVar3 = 0;
  pFVar2 = control_name;
  do {
    iVar1 = _stricmp(pFVar2->name,param_1);
    if (iVar1 == 0) {
      return control_name + uVar3;
    }
    uVar3 = uVar3 + 1;
    pFVar2 = pFVar2 + 1;
  } while (uVar3 < 0x6a);
  return (FIELD_DESC *)0x0;
}
