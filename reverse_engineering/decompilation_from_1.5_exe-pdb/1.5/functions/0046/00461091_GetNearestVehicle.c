/*
 * Entry: 00461091
 * Name: GetNearestVehicle
 * Namespace: Global
 * Signature: int GetNearestVehicle(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetNearestVehicle(int param_1)

{
  GameObject *pGVar1;
  VECTOR_3D *pVVar2;
  int iVar3;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    pVVar2 = (VECTOR_3D *)(**(code **)(pGVar1->_padding_ + 0xc))();
    iVar3 = GetNearestVehicle(pVVar2,pGVar1);
    return iVar3;
  }
  return 0;
}
