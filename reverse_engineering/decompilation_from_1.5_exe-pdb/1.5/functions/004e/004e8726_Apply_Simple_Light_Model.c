/*
 * Entry: 004e8726
 * Name: Apply_Simple_Light_Model
 * Namespace: Global
 * Signature: void Apply_Simple_Light_Model(VECTOR_3D * param_1, float * param_2, _GEOMETRY * param_3, MAT_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Apply_Simple_Light_Model(VECTOR_3D *param_1,float *param_2,_GEOMETRY *param_3,MAT_3D *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int in_EAX;
  VECTOR_3D *pVVar4;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int iVar5;
  float *pfVar6;
  float *in_ECX;
  float *pfVar7;
  int iVar8;
  VECTOR_3D local_2c;
  float local_20;
  float local_1c;
  float local_18;
  undefined8 local_14;
  float *local_c;
  float *local_8;
  
  iVar8 = *(int *)(in_EAX + 8);
  local_14._4_4_ = iVar8;
  if (((byte)LODInfo.flags & 0x44) == 0) {
    pfVar6 = *(float **)(in_EAX + 0x10);
    local_c = in_ECX;
    local_8 = in_ECX;
    pVVar4 = Vector_Unrotate(&local_2c,&Sun_Light,(MAT_3D *)param_2);
    local_20 = pVVar4->x;
    local_1c = pVVar4->y;
    local_18 = pVVar4->z;
    if (useD3D == 0) {
      if (0 < local_14._4_4_) {
        pfVar7 = &param_1->z;
        do {
          fVar2 = (-(local_20 * *pfVar6) - pfVar6[1] * local_1c) - pfVar6[2] * local_18;
          fVar1 = *pfVar7;
          pfVar7 = pfVar7 + 3;
          fVar3 = carAmbient;
          if (0.01 < fVar2) {
            fVar3 = carAmbient + (1.0 - carAmbient) * fVar2;
          }
          fVar3 = fVar3 * TerrainIntensity;
          local_14._0_4_ = SUB84((double)(fVar1 + (float)Float2Int),0);
          if (FogDirection == 0) {
            fVar3 = fVar3 * fogTable[(int)local_14];
          }
          else {
            fVar3 = (1.0 - fVar3) * fogTable[(int)local_14] + fVar3;
          }
          *local_c = fVar3;
          local_14._4_4_ = local_14._4_4_ + -1;
          pfVar6 = pfVar6 + 3;
          local_c = local_c + 1;
        } while (0 < local_14._4_4_);
      }
    }
    else {
      _ftol2_sse();
      if (0 < local_14._4_4_) {
        pfVar7 = &param_1->z;
        iVar8 = local_14._4_4_;
        local_c = (float *)extraout_EAX;
        do {
          fVar1 = *pfVar7;
          pfVar7 = pfVar7 + 3;
          local_14 = (double)(fVar1 + (float)Float2Int);
          if ((-(local_20 * *pfVar6) - pfVar6[1] * local_1c) - pfVar6[2] * local_18 <= 0.01) {
            *local_8 = (float)(fogTable256[(int)local_14] * 0x100 + (int)local_c);
          }
          else {
            _ftol2_sse();
            *local_8 = (float)(fogTable256[(int)local_14] * 0x100 - extraout_EAX_00);
          }
          local_8 = local_8 + 1;
          iVar8 = iVar8 + -1;
          pfVar6 = pfVar6 + 3;
        } while (0 < iVar8);
      }
    }
  }
  else if (useD3D == 0) {
    fVar1 = TerrainIntensity;
    if (((byte)LODInfo.flags & 0x40) != 0) {
      fVar1 = ShadowLuma * TerrainIntensity;
    }
    if (FogDirection == 0) {
      if (0 < iVar8) {
        pfVar6 = &param_1->z;
        do {
          fVar2 = *pfVar6;
          pfVar6 = pfVar6 + 3;
          local_14._0_4_ = SUB84((double)(fVar2 + (float)Float2Int),0);
          *in_ECX = fogTable[(int)local_14] * fVar1;
          in_ECX = in_ECX + 1;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
    }
    else if (0 < iVar8) {
      pfVar6 = &param_1->z;
      do {
        fVar2 = *pfVar6;
        pfVar6 = pfVar6 + 3;
        local_14._0_4_ = SUB84((double)(fVar2 + (float)Float2Int),0);
        *in_ECX = fogTable[(int)local_14] * (1.0 - fVar1) + fVar1;
        in_ECX = in_ECX + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
  }
  else {
    if (((byte)LODInfo.flags & 0x40) == 0) {
      iVar5 = 0xff;
    }
    else {
      _ftol2_sse();
      iVar5 = extraout_EAX_01;
    }
    if (0 < iVar8) {
      pfVar6 = &param_1->z;
      do {
        fVar1 = *pfVar6;
        pfVar6 = pfVar6 + 3;
        local_14._0_4_ = SUB84((double)(fVar1 + (float)Float2Int),0);
        *in_ECX = (float)(fogTable256[(int)local_14] * 0x100 + iVar5);
        in_ECX = in_ECX + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
  }
  return;
}
