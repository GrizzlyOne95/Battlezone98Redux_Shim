/*
 * Entry: 004cbc04
 * Name: EditTerrain::DrawGridVertex
 * Namespace: EditTerrain
 * Signature: float DrawGridVertex(EditTerrain * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall EditTerrain::DrawGridVertex(EditTerrain *this,VECTOR_3D *param_1)

{
  long lVar1;
  float fVar2;
  CAMERA *pCVar3;
  float fVar4;
  long *plVar5;
  tagPOINT tVar6;
  VECTOR_3D local_ec [4];
  _func___cdecl_void *local_b8;
  undefined1 local_80 [12];
  float local_74;
  FLOAT2INT local_70;
  long local_68 [6];
  long local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  long *local_20;
  float local_1c;
  float local_18;
  float local_14;
  CAMERA *local_10;
  float local_c;
  float local_8;
  
  local_14 = spriteZ;
  spriteZ = spriteZ + 0.5;
  if ((this->commandMenu->icon[this->commandDown].cmd != 0xc) &&
     ((this->brushWidth != 0 || (this->brushDepth != 0)))) {
    WorldToGrid(this,&local_70,(FLOAT2INT *)(local_80 + 8),param_1);
    fVar4 = (float)(local_70.i - this->brushWidth / 2);
    local_1c = (float)(this->brushWidth + (int)fVar4);
    fVar2 = (float)(local_80._8_4_ - this->brushDepth / 2);
    local_70._4_4_ = this->brushDepth + (int)fVar2;
    local_8 = fVar2;
    if ((int)fVar2 <= (int)local_70._4_4_) {
      do {
        local_c = fVar4;
        if ((int)fVar4 <= (int)local_1c) {
          local_74 = (float)(int)local_8 * 10.0;
          do {
            GetGridXYZ(local_ec,(float)(int)local_c * 10.0,local_74);
            local_20 = local_68;
            local_10 = (CAMERA *)local_ec;
            local_18 = 1.26117e-44;
            do {
              tVar6 = WorldToScreen(this,(VECTOR_3D *)local_80,local_10);
              lVar1 = ((long *)tVar6.x)[1];
              local_10 = (CAMERA *)&local_10->Const_y;
              *local_20 = *(long *)tVar6.x;
              local_20[1] = lVar1;
              local_20 = local_20 + 2;
              local_18 = (float)((int)local_18 + -1);
            } while (local_18 != 0.0);
            Graphic_Line(DisplayInterface::currentBuffer,(long)local_48,(long)local_44,
                         (long)local_40,(long)local_3c,DisplayInterface::colorRed,SOLID_PIXELS);
            Graphic_Line(DisplayInterface::currentBuffer,(long)local_48,(long)local_44,
                         (long)local_28,(long)local_24,DisplayInterface::colorRed,SOLID_PIXELS);
            Graphic_Line(DisplayInterface::currentBuffer,(long)local_48,(long)local_44,
                         (long)local_30,(long)local_2c,DisplayInterface::colorRed,SOLID_PIXELS);
            if (local_c == fVar4) {
              Graphic_Line(DisplayInterface::currentBuffer,(long)local_48,(long)local_44,local_50,
                           (long)local_4c,DisplayInterface::colorRed,SOLID_PIXELS);
              Graphic_Line(DisplayInterface::currentBuffer,(long)local_48,(long)local_44,local_68[0]
                           ,local_68[1],DisplayInterface::colorRed,SOLID_PIXELS);
            }
            if (local_8 == fVar2) {
              Graphic_Line(DisplayInterface::currentBuffer,(long)local_48,(long)local_44,local_68[2]
                           ,local_68[3],DisplayInterface::colorRed,SOLID_PIXELS);
              Graphic_Line(DisplayInterface::currentBuffer,(long)local_48,(long)local_44,local_68[0]
                           ,local_68[1],DisplayInterface::colorRed,SOLID_PIXELS);
            }
            local_c = (float)((int)local_c + 1);
          } while ((int)local_c <= (int)local_1c);
        }
        local_8 = (float)((int)local_8 + 1);
      } while ((int)local_8 <= (int)local_70._4_4_);
    }
  }
  GetGridXYZ(local_ec,param_1->x,param_1->z);
  plVar5 = local_68;
  pCVar3 = (CAMERA *)local_ec;
  param_1 = (VECTOR_3D *)0x9;
  do {
    tVar6 = WorldToScreen(this,(VECTOR_3D *)local_80,pCVar3);
    lVar1 = ((long *)tVar6.x)[1];
    *plVar5 = *(long *)tVar6.x;
    plVar5[1] = lVar1;
    pCVar3 = (CAMERA *)&pCVar3->Const_y;
    plVar5 = plVar5 + 2;
    param_1 = (VECTOR_3D *)((int)&param_1[-1].z + 3);
  } while (param_1 != (VECTOR_3D *)0x0);
  spriteZ = local_14 + 0.4;
  Graphic_Line(DisplayInterface::currentBuffer,(long)local_48,(long)local_44,local_50,(long)local_4c
               ,DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,(long)local_48,(long)local_44,local_68[0],local_68[1]
               ,DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,(long)local_48,(long)local_44,local_68[2],local_68[3]
               ,DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,(long)local_48,(long)local_44,(long)local_40,
               (long)local_3c,DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,(long)local_48,(long)local_44,(long)local_28,
               (long)local_24,DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,(long)local_48,(long)local_44,(long)local_30,
               (long)local_2c,DisplayInterface::colorWhite,SOLID_PIXELS);
  spriteZ = local_14;
  return (float)local_b8;
}
