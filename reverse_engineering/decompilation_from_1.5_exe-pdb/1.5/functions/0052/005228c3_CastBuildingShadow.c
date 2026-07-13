/*
 * Entry: 005228c3
 * Name: CastBuildingShadow
 * Namespace: Global
 * Signature: void CastBuildingShadow(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CastBuildingShadow(tagENTITY *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  byte extraout_AL;
  SPHERE *pSVar4;
  int extraout_EAX;
  int extraout_EAX_00;
  uint extraout_EAX_01;
  int extraout_EAX_02;
  byte *pbVar5;
  float *pfVar6;
  uint uVar7;
  int unaff_ESI;
  int unaff_EDI;
  int iVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  float fVar14;
  SPHERE local_24;
  float local_14;
  float local_10;
  int local_c;
  float local_8;
  
  if ((((DumpTerrain != 0) || ((UserProfilePtr->graphicDetail).shadow == '\0')) ||
      (fVar9 = (float10)Sun_Light.y, (float10)0.999 < fVar9)) || (fVar9 < (float10)0.001)) {
    return;
  }
  fVar10 = (float10)Sun_Light.z;
  fVar11 = (float10)Sun_Light.x;
  fVar13 = fVar11 * fVar11 + fVar10 * fVar10;
  fVar12 = (float10)fpatan(fVar9,SQRT(fVar13));
  local_8 = (float)fVar12;
  fVar10 = (float10)fpatan(fVar10,fVar11);
  local_14 = (float)fVar10;
  local_10 = (float)(SQRT(fVar13) / fVar9);
  pSVar4 = Entity_WorldSphere(&local_24,param_1);
  fVar1 = (pSVar4->origin).x;
  fVar2 = (pSVar4->origin).y;
  fVar3 = (pSVar4->origin).z;
  _ftol2_sse();
  _ftol2_sse();
  local_c = extraout_EAX_00;
  _ftol2_sse();
  _ftol2_sse();
  iVar8 = extraout_EAX;
  if (extraout_EAX < GridMinX) {
    iVar8 = GridMinX;
  }
  if (GridMaxX < local_c) {
    local_c = GridMaxX;
  }
  uVar7 = extraout_EAX_01;
  if ((int)extraout_EAX_01 < GridMinZ) {
    uVar7 = GridMinZ;
  }
  local_10 = (float)extraout_EAX_02;
  if (GridMaxZ < extraout_EAX_02) {
    local_10 = (float)GridMaxZ;
  }
  memset(shadowClipPlane,0,0x50);
  shadowClipPlane[4].surf_normal.x = Sun_Light.x;
  shadowClipPlane[4].surf_normal.y = Sun_Light.y;
  shadowClipPlane[4].surf_normal.z = Sun_Light.z;
  fVar9 = (float10)fsin((float10)local_8);
  fVar10 = (float10)fcos((float10)local_14 + (float10)3.1415927);
  shadowClipPlane[2].surf_normal.x = (float)(fVar10 * fVar9);
  fVar10 = (float10)fcos((float10)local_8);
  shadowClipPlane[2].surf_normal.y = (float)fVar10;
  fVar11 = (float10)fsin((float10)local_14 + (float10)3.1415927);
  shadowClipPlane[2].surf_normal.z = (float)(fVar11 * fVar9);
  shadowClipPlane[2].dist = (float)(((float10)(param_1->bBox).max.y - (float10)fVar2) * fVar10);
  fVar9 = (float10)fcos((float10)1.5707964 - (float10)local_14);
  shadowClipPlane[3].surf_normal.x = (float)fVar9;
  shadowClipPlane[3].surf_normal.y = 0.0;
  fVar10 = (float10)fsin((float10)1.5707964 - (float10)local_14);
  shadowClipPlane[3].surf_normal.z = (float)fVar10;
  shadowClipPlane[3].dist = (param_1->bBox).max.x - fVar1;
  fVar14 = (param_1->bBox).max.z - fVar3;
  if (shadowClipPlane[3].dist < fVar14) {
    shadowClipPlane[3].dist = fVar14;
  }
  shadowClipPlane[0].surf_normal.x = (float)-fVar9;
  shadowClipPlane[0].surf_normal.y = 0.0;
  shadowClipPlane[0].surf_normal.z = (float)-fVar10;
  shadowClipPlane[0].dist = fVar1 - (param_1->bBox).min.x;
  fVar14 = fVar3 - (param_1->bBox).min.z;
  if (shadowClipPlane[0].dist < fVar14) {
    shadowClipPlane[0].dist = fVar14;
  }
  if ((int)uVar7 <= (int)local_10) {
    do {
      if (iVar8 <= local_c) {
        local_24.radius = (float)(int)uVar7 * 10.0 - fVar3;
        local_14 = (float)uVar7;
        local_8 = (float)iVar8;
        do {
          local_24.origin.y = (float)(int)local_8 * 10.0 - fVar1;
          fVar14 = GetTerrainHeight((int)local_8,uVar7);
          pfVar6 = &shadowClipPlane[0].surf_normal.y;
          do {
            if (pfVar6[2] <
                *pfVar6 * (fVar14 * 10.0 - fVar2) +
                ((VECTOR_3D *)(pfVar6 + -1))->x * local_24.origin.y + pfVar6[1] * local_24.radius)
            goto LAB_00522ba3;
            pfVar6 = pfVar6 + 4;
          } while ((int)pfVar6 < 0xc4525c);
          pbVar5 = GetNormalPtr(unaff_EDI,unaff_ESI);
          local_14 = (float)(uint)*pbVar5;
          _ftol2();
          *pbVar5 = extraout_AL;
LAB_00522ba3:
          local_8 = (float)((int)local_8 + 1);
        } while ((int)local_8 <= local_c);
      }
      uVar7 = uVar7 + 1;
    } while ((int)uVar7 <= (int)local_10);
  }
  return;
}
