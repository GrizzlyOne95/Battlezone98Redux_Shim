/*
 * Entry: 0046122d
 * Name: GetNearestBuilding
 * Namespace: Global
 * Signature: int GetNearestBuilding(char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetNearestBuilding(char *param_1,int param_2)

{
  AiPath *pAVar1;
  int iVar2;
  VECTOR_3D local_10;
  
  pAVar1 = AiPath::Find(param_1);
  if (pAVar1 == (AiPath *)0x0) {
    iVar2 = 0;
  }
  else {
    iVar2 = Clamp(param_2,0,pAVar1->pointCount + -1);
    local_10.x = pAVar1->points[iVar2].x;
    local_10.z = pAVar1->points[iVar2].z;
    local_10.y = 0.0;
    iVar2 = GetNearestBuilding(&local_10,(GameObject *)0x0);
  }
  return iVar2;
}
