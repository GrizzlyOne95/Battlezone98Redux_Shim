/*
 * Entry: 0045f535
 * Name: GetDistance
 * Namespace: Global
 * Signature: float GetDistance(int param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GetDistance(int param_1,char *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  GameObject *pGVar3;
  AiPath *pAVar4;
  int iVar5;
  float *pfVar6;
  
  pGVar3 = GameObjectHandle::GetObj(param_1);
  if (pGVar3 == (GameObject *)0x0) {
    fVar1 = 1e+30;
  }
  else {
    pAVar4 = AiPath::Find(param_2);
    if (pAVar4 == (AiPath *)0x0) {
      fVar1 = 1e+30;
    }
    else {
      iVar5 = Clamp(param_3,0,pAVar4->pointCount + -1);
      fVar1 = pAVar4->points[iVar5].x;
      fVar2 = pAVar4->points[iVar5].z;
      pfVar6 = (float *)(**(code **)(pGVar3->_padding_ + 0xc))();
      fVar1 = *pfVar6 - fVar1;
      fVar2 = pfVar6[2] - fVar2;
      fVar1 = SQRT(fVar2 * fVar2 + fVar1 * fVar1);
    }
  }
  return fVar1;
}
