/*
 * Entry: 0046189d
 * Name: ClearScrapAround
 * Namespace: Global
 * Signature: void ClearScrapAround(float param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClearScrapAround(float param_1,int param_2)

{
  GameObject *pGVar1;
  VECTOR_3D *pVVar2;
  
  pGVar1 = GameObjectHandle::GetObj(param_2);
  if (pGVar1 != (GameObject *)0x0) {
    pVVar2 = (VECTOR_3D *)(**(code **)(pGVar1->_padding_ + 0xc))();
    ClearScrapAround(param_1,pVVar2);
  }
  return;
}
