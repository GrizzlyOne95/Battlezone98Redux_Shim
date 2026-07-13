/*
 * Entry: 0045ed14
 * Name: IsValid
 * Namespace: Global
 * Signature: bool IsValid(int * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsValid(int *param_1)

{
  GameObject *pGVar1;
  
  if (*param_1 != 0) {
    pGVar1 = GameObjectHandle::GetObj(*param_1);
    if (pGVar1 != (GameObject *)0x0) {
      return true;
    }
    *param_1 = 0;
  }
  return false;
}
