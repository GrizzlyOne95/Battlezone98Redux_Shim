/*
 * Entry: 0045dd01
 * Name: SetTeamNum
 * Namespace: Global
 * Signature: void SetTeamNum(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetTeamNum(int param_1,int param_2)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObject::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    (**(code **)(pGVar1->_padding_ + 8))(param_2);
  }
  return;
}
