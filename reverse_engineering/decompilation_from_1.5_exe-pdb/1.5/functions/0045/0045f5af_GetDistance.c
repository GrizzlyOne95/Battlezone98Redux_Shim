/*
 * Entry: 0045f5af
 * Name: GetDistance
 * Namespace: Global
 * Signature: float GetDistance(int param_1, AiPath * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GetDistance(int param_1,AiPath *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  GameObject *pGVar3;
  int iVar4;
  float *pfVar5;
  
  pGVar3 = GameObjectHandle::GetObj(param_1);
  if (pGVar3 == (GameObject *)0x0) {
    fVar1 = 1e+30;
  }
  else if (param_2 == (AiPath *)0x0) {
    fVar1 = 1e+30;
  }
  else {
    iVar4 = Clamp(param_3,0,param_2->pointCount + -1);
    fVar1 = param_2->points[iVar4].x;
    fVar2 = param_2->points[iVar4].z;
    pfVar5 = (float *)(**(code **)(pGVar3->_padding_ + 0xc))();
    fVar1 = *pfVar5 - fVar1;
    fVar2 = pfVar5[2] - fVar2;
    fVar1 = SQRT(fVar2 * fVar2 + fVar1 * fVar1);
  }
  return fVar1;
}
