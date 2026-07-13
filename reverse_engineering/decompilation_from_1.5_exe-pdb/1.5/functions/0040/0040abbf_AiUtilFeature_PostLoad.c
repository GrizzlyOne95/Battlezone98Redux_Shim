/*
 * Entry: 0040abbf
 * Name: AiUtilFeature::PostLoad
 * Namespace: AiUtilFeature
 * Signature: void PostLoad(AiUtilFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiUtilFeature::PostLoad(AiUtilFeature *this)

{
  AiPath *pAVar1;
  VECTOR_2D *pVVar2;
  int iVar3;
  
  pAVar1 = AiPath::Find("edge_path");
  if (pAVar1 == (AiPath *)0x0) {
    edgeMinX = TerMinX + 30.0;
    edgeMaxX = TerMaxX - 30.0;
    edgeMinZ = TerMinZ + 30.0;
    edgeMaxZ = TerMaxZ - 30.0;
  }
  else {
    iVar3 = pAVar1->pointCount;
    edgeMaxX = -1e+30;
    edgeMinZ = 1e+30;
    edgeMinX = 1e+30;
    edgeMaxZ = edgeMaxX;
    if (0 < iVar3) {
      pVVar2 = pAVar1->points;
      do {
        if (pVVar2->x < edgeMinX) {
          edgeMinX = pVVar2->x;
        }
        if (edgeMaxX < pVVar2->x) {
          edgeMaxX = pVVar2->x;
        }
        if (pVVar2->z < edgeMinZ) {
          edgeMinZ = pVVar2->z;
        }
        if (edgeMaxZ < pVVar2->z) {
          edgeMaxZ = pVVar2->z;
        }
        pVVar2 = pVVar2 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  LabelConnectedRegions();
  ProcessBuildings();
  memset(blocks,0,0x460);
  ReloadPathing();
  return;
}
