/*
 * Entry: 004fcf5a
 * Name: DrawGroundPoly
 * Namespace: Global
 * Signature: int DrawGroundPoly(CAMERA * param_1, VECTOR_3D * param_2, float param_3, float param_4, TEXTURE * param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
DrawGroundPoly(CAMERA *param_1,VECTOR_3D *param_2,float param_3,float param_4,TEXTURE *param_5,
              int param_6)

{
  float fVar1;
  float fVar2;
  uint6 uVar3;
  ulonglong uVar4;
  ushort *puVar5;
  uint uVar6;
  long lVar7;
  int iVar8;
  long unaff_ESI;
  VECTOR_3D *pVVar9;
  POINT_3D *unaff_EDI;
  POINT_3D local_390;
  float local_378;
  float fStack_374;
  float fStack_370;
  float local_36c;
  float local_368;
  undefined4 local_364;
  float local_360;
  float fStack_35c;
  float fStack_358;
  float local_354;
  float local_350;
  undefined4 local_34c;
  double local_90;
  double local_88;
  VECTOR_3D *local_80;
  float local_7c;
  float local_74;
  float local_6c;
  float local_68;
  float local_60;
  undefined8 local_58;
  VECTOR_3D local_50;
  VECTOR_3D local_44;
  VECTOR_3D local_38;
  VECTOR_3D local_2c;
  float local_20;
  float local_1c;
  VECTOR_3D *local_18;
  float local_14;
  float local_10;
  undefined8 local_c;
  
  local_10 = param_2->x - param_3 * 0.5;
  local_14 = param_2->z - param_4 * 0.5;
  if ((param_3 < 1e-05) || (param_4 < 1e-05)) {
    iVar8 = 0;
  }
  else {
    local_20 = 1.0 / param_3;
    local_1c = 1.0 / param_4;
    fVar2 = (float)Float2Int;
    local_c = (double)(local_10 * Terrain.Grid_Scale + 0.5 + fVar2);
    local_58 = (double)(Terrain.Grid_Scale * local_14 + 0.5 + fVar2);
    fVar1 = local_10 + param_3;
    param_3 = (float)((int)(float)local_58 + -1);
    local_90 = (double)(fVar1 * Terrain.Grid_Scale + 0.5 + fVar2);
    local_88 = (double)(Terrain.Grid_Scale * (local_14 + param_4) + 0.5 + fVar2);
    if ((int)param_3 < local_88._0_4_) {
      local_80 = (VECTOR_3D *)((int)local_c + -1);
      param_4 = (float)local_58;
      do {
        if ((int)local_80 < local_90._0_4_) {
          local_6c = (float)(int)param_3;
          local_58 = (double)CONCAT44((float)(int)param_4,(float)local_58);
          pVVar9 = local_80;
          param_2 = local_80;
          do {
            param_2 = (VECTOR_3D *)((int)&param_2->x + 1);
            local_50.x = (float)(int)pVVar9 * Terrain.Grid_Size;
            local_50.z = Terrain.Grid_Size * local_6c;
            local_18 = pVVar9;
            puVar5 = GetZonePtr((int)pVVar9,(int)param_3);
            uVar3 = CONCAT24(*puVar5,(int)local_c) & 0xfffffffffff;
            local_c = (double)(ulonglong)uVar3;
            uVar4 = (ulonglong)local_c;
            local_c._4_4_ = (uint)(ushort)(uVar3 >> 0x20);
            local_50.y = (float)local_c._4_4_ * 0.1 + 0.1;
            local_68 = (local_50.x - local_10) * local_20;
            local_7c = (local_50.z - local_14) * local_1c;
            local_38.x = (float)(int)param_2 * Terrain.Grid_Size;
            local_38.z = Terrain.Grid_Size * local_58._4_4_;
            local_c = (double)uVar4;
            puVar5 = GetZonePtr((int)param_2,(int)param_4);
            uVar3 = CONCAT24(*puVar5,(int)local_c) & 0xfffffffffff;
            local_c = (double)(ulonglong)uVar3;
            uVar4 = (ulonglong)local_c;
            local_c._4_4_ = (uint)(ushort)(uVar3 >> 0x20);
            local_38.y = (float)local_c._4_4_ * 0.1 + 0.1;
            local_60 = (local_38.x - local_10) * local_20;
            local_74 = (local_38.z - local_14) * local_1c;
            local_44.x = local_38.x;
            local_44.z = local_50.z;
            local_c = (double)uVar4;
            puVar5 = GetZonePtr((int)param_2,(int)param_3);
            uVar3 = CONCAT24(*puVar5,(int)local_c) & 0xfffffffffff;
            local_c = (double)(ulonglong)uVar3;
            uVar4 = (ulonglong)local_c;
            local_c._4_4_ = (uint)(ushort)(uVar3 >> 0x20);
            local_44.y = (float)local_c._4_4_ * 0.1 + 0.1;
            local_2c.x = local_50.x;
            local_2c.z = local_38.z;
            local_c = (double)uVar4;
            puVar5 = GetZonePtr((int)pVVar9,(int)param_4);
            uVar3 = CONCAT24(*puVar5,(int)local_c) & 0xfffffffffff;
            local_c = (double)(ulonglong)uVar3;
            uVar4 = (ulonglong)local_c;
            local_c._4_4_ = (uint)(ushort)(uVar3 >> 0x20);
            local_2c.y = (float)local_c._4_4_ * 0.1 + 0.1;
            local_c = (double)uVar4;
            Vector_Transform(&local_50,&local_50,4,&param_1->Matrix);
            uVar6 = FacesIn(&local_50,&local_44,&local_38,&local_2c);
            local_390.Texel.field2_0x8.luma = 1.0;
            local_364 = 0x3f800000;
            local_c = (double)CONCAT44(uVar6,(int)local_c);
            local_34c = 0x3f800000;
            if ((uVar6 & 1) != 0) {
              local_390.Vector.x = local_50.x;
              local_390.Vector.y = local_50.y;
              local_390.Vector.z = local_50.z;
              local_378 = local_44.x;
              fStack_374 = local_44.y;
              fStack_370 = local_44.z;
              local_360 = local_38.x;
              fStack_35c = local_38.y;
              fStack_358 = local_38.z;
              local_390.Texel.u = local_68;
              local_36c = local_60;
              local_354 = local_60;
              local_390.Texel.v = local_7c;
              local_368 = local_7c;
              local_350 = local_74;
              lVar7 = UV_Clip_Polygon(&local_390,unaff_EDI,unaff_ESI);
              if (0 < lVar7) {
                if (useD3D == 0) {
                  __Camera_Software_Draw_polygon__
                            (param_1,&local_390,lVar7,(POLYGON_SKIN)param_5,param_6);
                }
                else {
                  __Camera_Hardware_Draw_polygon__
                            (param_1,&local_390,lVar7,(POLYGON_SKIN)param_5,param_6);
                }
              }
            }
            if (((ulonglong)local_c & 0x200000000) != 0) {
              local_390.Vector.x = local_50.x;
              local_390.Vector.y = local_50.y;
              local_390.Vector.z = local_50.z;
              local_378 = local_38.x;
              fStack_374 = local_38.y;
              fStack_370 = local_38.z;
              local_360 = local_2c.x;
              fStack_35c = local_2c.y;
              fStack_358 = local_2c.z;
              local_390.Texel.u = local_68;
              local_36c = local_60;
              local_354 = local_68;
              local_390.Texel.v = local_7c;
              local_368 = local_74;
              local_350 = local_74;
              lVar7 = UV_Clip_Polygon(&local_390,unaff_EDI,unaff_ESI);
              if (0 < lVar7) {
                if (useD3D == 0) {
                  __Camera_Software_Draw_polygon__
                            (param_1,&local_390,lVar7,(POLYGON_SKIN)param_5,param_6);
                }
                else {
                  __Camera_Hardware_Draw_polygon__
                            (param_1,&local_390,lVar7,(POLYGON_SKIN)param_5,param_6);
                }
              }
            }
            pVVar9 = (VECTOR_3D *)((int)&local_18->x + 1);
          } while ((int)pVVar9 < local_90._0_4_);
        }
        param_3 = (float)((int)param_3 + 1);
        param_4 = (float)((int)param_4 + 1);
      } while ((int)param_3 < local_88._0_4_);
    }
    iVar8 = 1;
  }
  return iVar8;
}
