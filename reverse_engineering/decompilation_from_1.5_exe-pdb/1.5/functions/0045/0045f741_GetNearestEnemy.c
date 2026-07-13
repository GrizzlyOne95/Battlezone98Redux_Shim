/*
 * Entry: 0045f741
 * Name: GetNearestEnemy
 * Namespace: Global
 * Signature: int GetNearestEnemy(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetNearestEnemy(int param_1)

{
  GameObject *pGVar1;
  float *pfVar2;
  int iVar3;
  VECTOR_3D local_10;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    iVar3 = 0;
  }
  else {
    pfVar2 = (float *)(**(code **)(pGVar1->_padding_ + 0xc))();
    local_10.x = *pfVar2;
    local_10.y = pfVar2[1];
    local_10.z = pfVar2[2];
    iVar3 = GetNearestEnemy(&local_10,pGVar1);
  }
  return iVar3;
}
