/*
 * Entry: 0045f84a
 * Name: IsSelected
 * Namespace: Global
 * Signature: bool IsSelected(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsSelected(int param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObject::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return false;
  }
  return pGVar1->isSelected;
}
