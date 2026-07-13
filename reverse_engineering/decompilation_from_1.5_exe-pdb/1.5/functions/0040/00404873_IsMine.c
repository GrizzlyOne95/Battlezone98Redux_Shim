/*
 * Entry: 00404873
 * Name: IsMine
 * Namespace: Global
 * Signature: bool IsMine(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsMine(GameObject *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)param_1->_padding_)();
  iVar1 = *(int *)(iVar1 + 0x20);
  if ((((iVar1 != 0x464c4152) && (iVar1 != 0x4d474e54)) && (iVar1 != 0x4d494e45)) &&
     ((iVar1 != 0x50524f58 && (iVar1 != 0x57504e4d)))) {
    return false;
  }
  return true;
}
