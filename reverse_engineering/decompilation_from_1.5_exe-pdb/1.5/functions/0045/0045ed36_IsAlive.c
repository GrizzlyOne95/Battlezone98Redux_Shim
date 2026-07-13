/*
 * Entry: 0045ed36
 * Name: IsAlive
 * Namespace: Global
 * Signature: bool IsAlive(int * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsAlive(int *param_1)

{
  GameObject *pGVar1;
  int iVar2;
  
  if (*param_1 == 0) {
    return false;
  }
  pGVar1 = GameObjectHandle::GetObj(*param_1);
  if (pGVar1 != (GameObject *)0x0) {
    iVar2 = (**(code **)(pGVar1->_padding_ + 0x30))();
    if (((*(int *)(iVar2 + 0xac) != 1) && (*(int *)(iVar2 + 0xac) != 6)) ||
       (pGVar1->aiProcess != (AiProcess *)0x0)) {
      return true;
    }
  }
  *param_1 = 0;
  return false;
}
