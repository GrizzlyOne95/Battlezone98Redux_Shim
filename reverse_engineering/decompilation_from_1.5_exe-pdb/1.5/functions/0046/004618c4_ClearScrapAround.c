/*
 * Entry: 004618c4
 * Name: ClearScrapAround
 * Namespace: Global
 * Signature: void ClearScrapAround(float param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClearScrapAround(float param_1,char *param_2,int param_3)

{
  AiPath *pAVar1;
  int iVar2;
  VECTOR_3D local_10;
  
  pAVar1 = AiPath::Find(param_2);
  if (pAVar1 != (AiPath *)0x0) {
    iVar2 = Clamp(param_3,0,pAVar1->pointCount + -1);
    local_10.x = pAVar1->points[iVar2].x;
    local_10.z = pAVar1->points[iVar2].z;
    local_10.y = 0.0;
    ClearScrapAround(param_1,&local_10);
  }
  return;
}
