/*
 * Entry: 0040198d
 * Name: CheckBoundary
 * Namespace: Global
 * Signature: void CheckBoundary(GameObject * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CheckBoundary(GameObject *param_1,float param_2)

{
  VECTOR_3D *pVVar1;
  float fVar2;
  VECTOR_2D VVar3;
  float *pfVar4;
  int unaff_EBX;
  VECTOR_2D VVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float local_10;
  
  pfVar4 = (float *)(**(code **)(*(int *)(unaff_EBX + 0x20) + 0xc))();
  fVar8 = *pfVar4;
  fVar2 = pfVar4[2];
  if ((((fVar8 < edgeMinX) || (edgeMaxX < fVar8)) || (fVar2 < edgeMinZ)) || (edgeMaxZ < fVar2)) {
    fVar6 = Clamp(fVar8,edgeMinX,edgeMaxX);
    fVar7 = Clamp(fVar2,edgeMinZ,edgeMaxZ);
    VVar5.z = fVar7;
    VVar5.x = fVar6;
    VVar3.z = fVar2;
    VVar3.x = fVar8;
    VVar5 = Vec2D_Subtract(VVar5,VVar3);
    pVVar1 = (VECTOR_3D *)(unaff_EBX + 0x120);
    pVVar1->x = fVar6 * (float)param_1 * 10.0 + pVVar1->x;
    local_10 = VVar5.z;
    *(float *)(unaff_EBX + 0x128) = local_10 * (float)param_1 * 10.0 + *(float *)(unaff_EBX + 0x128)
    ;
    fVar8 = VecLen(*pVVar1);
    *(float *)(unaff_EBX + 0x110) = fVar8;
    if (fVar8 <= 0.0) {
      fVar8 = 1e+30;
    }
    else {
      fVar8 = 1.0 / fVar8;
    }
    *(float *)(unaff_EBX + 0x114) = fVar8;
  }
  return;
}
