/*
 * Entry: 0045ecc0
 * Name: IsOdf
 * Namespace: Global
 * Signature: bool IsOdf(int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsOdf(int param_1,char *param_2)

{
  bool bVar1;
  GameObject *pGVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  pGVar2 = GameObjectHandle::GetObj(param_1);
  if (pGVar2 == (GameObject *)0x0) {
    bVar1 = false;
  }
  else {
    local_c = 0;
    local_8 = 0;
    strncpy((char *)&local_c,param_2,8);
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
