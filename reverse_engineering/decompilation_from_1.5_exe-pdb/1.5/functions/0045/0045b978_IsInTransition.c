/*
 * Entry: 0045b978
 * Name: IsInTransition
 * Namespace: Global
 * Signature: bool IsInTransition(Craft * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsInTransition(Craft *param_1)

{
  char cVar1;
  
  cVar1 = (**(code **)(param_1->_padding_ + 100))();
  if (cVar1 == '\0') {
    cVar1 = (**(code **)(param_1->_padding_ + 0x68))();
    if (cVar1 == '\0') {
      return true;
    }
  }
  return false;
}
