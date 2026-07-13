/*
 * Entry: 004fcaea
 * Name: DrawGroundSprite
 * Namespace: Global
 * Signature: int DrawGroundSprite(CAMERA * param_1, VECTOR_3D * param_2, float param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
DrawGroundSprite(CAMERA *param_1,VECTOR_3D *param_2,float param_3,int param_4,int param_5)

{
  float fVar1;
  uint6 uVar2;
  ulonglong uVar3;
  SPRITE *pSVar4;
  int iVar5;
  ushort *puVar6;
  uint uVar7;
  long lVar8;
  float *pfVar9;
  long lVar10;
  long unaff_EBX;
  int unaff_ESI;
  VECTOR_3D *pVVar11;
  POINT_3D *unaff_EDI;
  POINT_3D local_3a0;
  float local_388;
  float fStack_384;
  float fStack_380;
  float local_37c;
  float local_378;
  float local_370;
  float fStack_36c;
  float fStack_368;
  float local_364;
  float local_360;
  double local_a0;
  double local_98;
  float local_90;
  float local_8c;
  float local_84;
  undefined8 local_7c;
  float local_74;
  float local_6c;
  VECTOR_3D *local_64;
  VECTOR_3D local_60;
  VECTOR_3D local_54;
  VECTOR_3D local_48;
  VECTOR_3D local_3c;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  VECTOR_3D *local_1c;
  float local_18;
  float local_14;
  POLYGON_SKIN local_10;
  undefined8 local_c;
  
  pVVar11 = param_2;
  local_24 = param_2->x - param_3;
  local_2c = param_2->z - param_3;
  if ((param_4 < 0) || (spriteTableSize <= param_4)) {
    pSVar4 = spriteTable;
  }
  else {
    pSVar4 = spriteTable + param_4;
  }
  Colored_Light_RGBA = colorTable[pSVar4->flags & 0xf];
  local_10.Texture =
       GetSpriteTextureUV(param_4,&local_18,&local_20,(float *)&param_2,(float *)&param_4);
  local_30 = (float)param_2 - local_18;
  local_28 = (float)param_4 - local_20;
  if (1e-05 <= param_3) {
    local_14 = 0.5 / param_3;
    Set_Rounding(unaff_ESI);
    fVar1 = (float)Float2Int;
    local_c = (double)((pVVar11->x - param_3) * Terrain.Grid_Scale + fVar1);
    local_7c = (double)((pVVar11->z - param_3) * Terrain.Grid_Scale + fVar1);
    local_a0 = (double)((pVVar11->x + param_3) * Terrain.Grid_Scale + fVar1);
    local_98 = (double)(Terrain.Grid_Scale * (pVVar11->z + param_3) + fVar1);
    Set_Rounding(unaff_ESI);
    param_3 = (float)((int)local_7c + -1);
    if ((int)param_3 <= local_98._0_4_) {
      local_64 = (VECTOR_3D *)((int)local_c + -1);
      param_4 = (int)local_7c;
      do {
        if ((int)local_64 <= local_a0._0_4_) {
          local_90 = (float)(int)param_3;
          local_7c = (double)CONCAT44((float)param_4,(int)local_7c);
          pVVar11 = local_64;
          param_2 = local_64;
          do {
            param_2 = (VECTOR_3D *)((int)&param_2->x + 1);
            local_60.x = (float)(int)pVVar11 * Terrain.Grid_Size;
            local_60.z = Terrain.Grid_Size * local_90;
            local_1c = pVVar11;
            puVar6 = GetZonePtr((int)pVVar11,(int)param_3);
            uVar2 = CONCAT24(*puVar6,(int)local_c) & 0xfffffffffff;
            local_c = (double)(ulonglong)uVar2;
            uVar3 = (ulonglong)local_c;
            local_c._4_4_ = (uint)(ushort)(uVar2 >> 0x20);
            local_60.y = (float)local_c._4_4_ * 0.1 + 0.1;
            local_74 = (local_60.x - local_24) * local_14;
            local_8c = (local_60.z - local_2c) * local_14;
            local_48.x = (float)(int)param_2 * Terrain.Grid_Size;
            local_48.z = Terrain.Grid_Size * local_7c._4_4_;
            local_c = (double)uVar3;
            puVar6 = GetZonePtr((int)param_2,param_4);
            uVar2 = CONCAT24(*puVar6,(int)local_c) & 0xfffffffffff;
            local_c = (double)(ulonglong)uVar2;
            uVar3 = (ulonglong)local_c;
            local_c._4_4_ = (uint)(ushort)(uVar2 >> 0x20);
            local_48.y = (float)local_c._4_4_ * 0.1 + 0.1;
            local_6c = (local_48.x - local_24) * local_14;
            local_84 = (local_48.z - local_2c) * local_14;
            local_54.x = local_48.x;
            local_54.z = local_60.z;
            local_c = (double)uVar3;
            puVar6 = GetZonePtr((int)param_2,(int)param_3);
            uVar2 = CONCAT24(*puVar6,(int)local_c) & 0xfffffffffff;
            local_c = (double)(ulonglong)uVar2;
            uVar3 = (ulonglong)local_c;
            local_c._4_4_ = (uint)(ushort)(uVar2 >> 0x20);
            local_54.y = (float)local_c._4_4_ * 0.1 + 0.1;
            local_3c.x = local_60.x;
            local_3c.z = local_48.z;
            local_c = (double)uVar3;
            puVar6 = GetZonePtr((int)pVVar11,param_4);
            uVar2 = CONCAT24(*puVar6,(int)local_c) & 0xfffffffffff;
            local_c = (double)(ulonglong)uVar2;
            uVar3 = (ulonglong)local_c;
            local_c._4_4_ = (uint)(ushort)(uVar2 >> 0x20);
            local_3c.y = (float)local_c._4_4_ * 0.1 + 0.1;
            local_c = (double)uVar3;
            Vector_Transform(&local_60,&local_60,4,&param_1->Matrix);
            uVar7 = FacesIn(&local_60,&local_54,&local_48,&local_3c);
            local_c = (double)CONCAT44(uVar7,(int)local_c);
            if ((uVar7 & 1) != 0) {
              local_3a0.Vector.x = local_60.x;
              local_3a0.Vector.y = local_60.y;
              local_3a0.Vector.z = local_60.z;
              local_388 = local_54.x;
              fStack_384 = local_54.y;
              fStack_380 = local_54.z;
              local_370 = local_48.x;
              fStack_36c = local_48.y;
              fStack_368 = local_48.z;
              local_3a0.Texel.u = local_74;
              local_37c = local_6c;
              local_364 = local_6c;
              local_3a0.Texel.v = local_8c;
              local_378 = local_8c;
              local_360 = local_84;
              lVar8 = UV_Clip_Polygon(&local_3a0,unaff_EDI,unaff_EBX);
              if (0 < lVar8) {
                pfVar9 = &local_3a0.Texel.v;
                lVar10 = lVar8;
                do {
                  lVar10 = lVar10 + -1;
                  ((TEXEL *)(pfVar9 + -1))->u = ((TEXEL *)(pfVar9 + -1))->u * local_30 + local_18;
                  *pfVar9 = *pfVar9 * local_28 + local_20;
                  ((TEXEL_u_8 *)(pfVar9 + 1))->luma = 1.0;
                  pfVar9 = pfVar9 + 6;
                } while (0 < lVar10);
                if (useD3D == 0) {
                  __Camera_Software_Draw_polygon__
                            (param_1,&local_3a0,lVar8,local_10,
                             BitmapOper2PolyType[param_5 & 7] | 0x10U);
                }
                else {
                  __Camera_Hardware_Draw_polygon__
                            (param_1,&local_3a0,lVar8,local_10,
                             BitmapOper2PolyType[param_5 & 7] | 0x10U);
                }
              }
            }
            if (((ulonglong)local_c & 0x200000000) != 0) {
              local_3a0.Vector.x = local_60.x;
              local_3a0.Vector.y = local_60.y;
              local_3a0.Vector.z = local_60.z;
              local_388 = local_48.x;
              fStack_384 = local_48.y;
              fStack_380 = local_48.z;
              local_370 = local_3c.x;
              fStack_36c = local_3c.y;
              fStack_368 = local_3c.z;
              local_3a0.Texel.u = local_74;
              local_37c = local_6c;
              local_364 = local_74;
              local_3a0.Texel.v = local_8c;
              local_378 = local_84;
              local_360 = local_84;
              lVar8 = UV_Clip_Polygon(&local_3a0,unaff_EDI,unaff_EBX);
              if (0 < lVar8) {
                pfVar9 = &local_3a0.Texel.v;
                lVar10 = lVar8;
                do {
                  lVar10 = lVar10 + -1;
                  ((TEXEL *)(pfVar9 + -1))->u = ((TEXEL *)(pfVar9 + -1))->u * local_30 + local_18;
                  *pfVar9 = *pfVar9 * local_28 + local_20;
                  ((TEXEL_u_8 *)(pfVar9 + 1))->luma = 1.0;
                  pfVar9 = pfVar9 + 6;
                } while (0 < lVar10);
                if (useD3D == 0) {
                  __Camera_Software_Draw_polygon__
                            (param_1,&local_3a0,lVar8,local_10,
                             BitmapOper2PolyType[param_5 & 7] | 0x10U);
                }
                else {
                  __Camera_Hardware_Draw_polygon__
                            (param_1,&local_3a0,lVar8,local_10,
                             BitmapOper2PolyType[param_5 & 7] | 0x10U);
                }
              }
            }
            pVVar11 = (VECTOR_3D *)((int)&local_1c->x + 1);
          } while ((int)pVVar11 <= local_a0._0_4_);
        }
        param_3 = (float)((int)param_3 + 1);
        param_4 = param_4 + 1;
      } while ((int)param_3 <= local_98._0_4_);
    }
    Colored_Light_RGBA = 0xffffff;
    iVar5 = 1;
  }
  else {
    iVar5 = 0;
  }
  return iVar5;
}
