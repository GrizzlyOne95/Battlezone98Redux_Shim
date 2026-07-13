/*
 * Entry: 0045e159
 * Name: IsInfo
 * Namespace: Global
 * Signature: bool IsInfo(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsInfo(char *param_1)

{
  bool bVar1;
  GameObject *pGVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  pGVar2 = InfoDisplay::CurrentInfoDisplay(&infoDisplay);
  if (pGVar2 == (GameObject *)0x0) {
    bVar1 = false;
  }
  else {
    local_c = 0;
    local_8 = 0;
    strncpy((char *)&local_c,param_1,8);
    iVar3 = (**(code **)pGVar2->_padding_)();
    if ((*(int *)(iVar3 + 0x38) == local_c) && (*(int *)(iVar3 + 0x3c) == local_8)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
