/*
 * Entry: 00461205
 * Name: GetNearestBuilding
 * Namespace: Global
 * Signature: int GetNearestBuilding(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetNearestBuilding(int param_1)

{
  GameObject *pGVar1;
  VECTOR_3D *pVVar2;
  int iVar3;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    pVVar2 = (VECTOR_3D *)(**(code **)(pGVar1->_padding_ + 0xc))();
    iVar3 = GetNearestBuilding(pVVar2,pGVar1);
    return iVar3;
  }
  return 0;
}
