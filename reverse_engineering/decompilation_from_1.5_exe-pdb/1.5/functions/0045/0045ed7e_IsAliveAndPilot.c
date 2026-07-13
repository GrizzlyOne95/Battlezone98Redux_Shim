/*
 * Entry: 0045ed7e
 * Name: IsAliveAndPilot
 * Namespace: Global
 * Signature: bool IsAliveAndPilot(int * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsAliveAndPilot(int *param_1)

{
  GameObject *pGVar1;
  int iVar2;
  
  if (*param_1 == 0) {
    return false;
  }
  pGVar1 = GameObjectHandle::GetObj(*param_1);
  if (pGVar1 != (GameObject *)0x0) {
    iVar2 = (**(code **)(pGVar1->_padding_ + 0x30))();
    if ((*(int *)(iVar2 + 0xac) != 1) && (*(int *)(iVar2 + 0xac) != 6)) {
      return true;
    }
    if (pGVar1->aiProcess != (AiProcess *)0x0) {
      return pGVar1->curPilot != (GameObjectClass *)0x0;
    }
  }
  *param_1 = 0;
  return false;
}
