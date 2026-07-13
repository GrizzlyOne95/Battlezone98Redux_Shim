/*
 * Entry: 0045f4aa
 * Name: GetDistance
 * Namespace: Global
 * Signature: float GetDistance(int param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GetDistance(int param_1,VECTOR_3D *param_2)

{
  float fVar1;
  float fVar2;
  GameObject *pGVar3;
  float *pfVar4;
  
  pGVar3 = GameObjectHandle::GetObj(param_1);
  if (pGVar3 == (GameObject *)0x0) {
    return 1e+30;
  }
  pfVar4 = (float *)(**(code **)(pGVar3->_padding_ + 0xc))();
  fVar1 = *pfVar4 - param_2->x;
  fVar2 = pfVar4[2] - param_2->z;
  return SQRT(fVar2 * fVar2 + fVar1 * fVar1);
}
