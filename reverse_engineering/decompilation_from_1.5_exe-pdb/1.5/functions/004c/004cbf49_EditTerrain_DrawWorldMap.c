/*
 * Entry: 004cbf49
 * Name: EditTerrain::DrawWorldMap
 * Namespace: EditTerrain
 * Signature: void DrawWorldMap(EditTerrain * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::DrawWorldMap(EditTerrain *this)

{
  tagRECT *ptVar1;
  int *piVar2;
  int iVar3;
  _GRAPHIC_BUFFER *p_Var4;
  long extraout_EAX;
  long extraout_EAX_00;
  long extraout_EAX_01;
  long extraout_EAX_02;
  long extraout_EAX_03;
  long extraout_EAX_04;
  long extraout_EAX_05;
  long extraout_EAX_06;
  int iVar5;
  int iVar6;
  float10 extraout_ST0;
  POINT_3D local_b4;
  float local_9c;
  float local_98;
  float local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  float local_84;
  float local_80;
  float local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  float local_6c;
  float local_68;
  float local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  tagPOINT local_54 [4];
  int local_34;
  int local_30;
  undefined1 local_2c [8];
  float local_24;
  int local_20;
  float local_1c;
  int local_18;
  int local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_1c = spriteZ;
  spriteZ = spriteZ + 0.3;
  piVar2 = &this->mapDX;
  iVar6 = *piVar2;
  iVar5 = ((DisplayInterface::currentBuffer->Pane).x1 - (DisplayInterface::currentBuffer->Pane).x0)
          - iVar6;
  ptVar1 = &this->mapRect;
  ptVar1->left = iVar5 + -0x10;
  iVar3 = this->mapDY;
  (this->mapRect).right = iVar5 + -0x11 + iVar6;
  iVar6 = ((DisplayInterface::currentBuffer->Pane).y1 - (DisplayInterface::currentBuffer->Pane).y0)
          - iVar3;
  (this->mapRect).top = iVar6 + -0x10;
  (this->mapRect).bottom = iVar6 + -0x11 + iVar3;
  if (useD3D == 0) {
    Graphic_Copy_Bitmap(DisplayInterface::currentBuffer,&this->gbMap,ptVar1->left,
                        (this->mapRect).top,SOLID_PIXELS);
  }
  else {
    local_b4.Vector.z = 1.0 / spriteZ;
    local_b4.Vector.x = (float)ptVar1->left;
    local_b4.Vector.y = (float)(this->mapRect).top;
    local_b4.Texel.u = 0.0;
    local_b4.Texel.v = 0.0;
    local_b4.Texel.field2_0x8.luma = 1.0;
    local_9c = (float)(this->mapRect).right;
    local_90 = 0x3f800000;
    local_88 = 0x3f800000;
    local_8c = 0;
    local_80 = (float)(this->mapRect).bottom;
    local_78 = 0x3f800000;
    local_74 = 0x3f800000;
    local_70 = 0x3f800000;
    local_5c = 0x3f800000;
    local_58 = 0x3f800000;
    local_60 = 0;
    local_98 = local_b4.Vector.y;
    local_94 = local_b4.Vector.z;
    local_84 = local_9c;
    local_7c = local_b4.Vector.z;
    local_6c = local_b4.Vector.x;
    local_68 = local_80;
    local_64 = local_b4.Vector.z;
    Draw_D3D_Poly(&local_b4,4,(POLYGON_SKIN)this->txMap,4);
  }
  local_8 = (float)(this->mapRect).right;
  spriteZ = local_1c + 0.2;
  local_c = (float)(this->mapRect).bottom;
  local_10 = (float)ptVar1->left;
  local_30 = (this->mapRect).top;
  local_14 = *piVar2 + 6;
  local_24 = (float)(local_30 + -3);
  local_34 = (int)local_10 + -3;
  DrawBoxOutline(this,DisplayInterface::currentBuffer,local_34,(int)local_24,(float)local_14,
                 DisplayInterface::colorWhite);
  local_20 = local_30 + -1;
  local_14 = (int)local_10 + -1;
  local_18 = *piVar2 + 2;
  DrawBoxOutline(this,DisplayInterface::currentBuffer,local_14,local_20,(float)local_18,
                 DisplayInterface::colorWhite);
  local_18 = *piVar2 + 4;
  DrawBoxOutline(this,DisplayInterface::currentBuffer,(int)local_10 + -2,local_30 + -2,
                 (float)local_18,DisplayInterface::colorGrey);
  Graphic_Line(DisplayInterface::currentBuffer,local_14,local_20,(int)local_8 + 1,local_20,
               DisplayInterface::colorBlack,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_14,local_20,local_14,(int)local_c + 1,
               DisplayInterface::colorBlack,SOLID_PIXELS);
  local_18 = (int)local_c + 3;
  local_8 = (float)((int)local_8 + 3);
  Graphic_Line(DisplayInterface::currentBuffer,local_34,local_18,(long)local_8,local_18,
               DisplayInterface::colorBlack,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,(long)local_8,(long)local_24,(long)local_8,local_18,
               DisplayInterface::colorBlack,SOLID_PIXELS);
  p_Var4 = DisplayInterface::currentCamera->Buffer;
  local_54[0].x = (p_Var4->Pane).x1 - (p_Var4->Pane).x0 >> 1;
  local_54[0].y = (p_Var4->Pane).y1 - (p_Var4->Pane).y0 >> 1;
  iVar6 = ScreenToWorld(this,(VECTOR_3D *)local_2c,local_54,DisplayInterface::currentCamera);
  if (iVar6 != 0) {
    local_8 = (float)local_2c._0_4_ - this->worldExtents[0].x;
    local_c = local_24 - this->worldExtents[0].z;
    local_10 = (1.0 / this->worldDX) * (float)*piVar2 * TerrainVisibilityRange * 0.25;
    _ftol2_sse();
    (this->dragRect).left = extraout_EAX;
    _ftol2_sse();
    (this->dragRect).top = extraout_EAX_00;
    _ftol2_sse();
    (this->dragRect).right = extraout_EAX_01;
    _ftol2_sse();
    spriteZ = local_1c + 0.1;
    (this->dragRect).bottom = extraout_EAX_02;
    DrawBoxOutline(this,DisplayInterface::currentBuffer,(this->dragRect).left,(this->dragRect).top,
                   (float)extraout_ST0,DisplayInterface::colorWhite);
    join_0x00000008_0x00000000_ = SinCos(this->Yaw);
    _ftol2_sse();
    local_54[0].x = extraout_EAX_03;
    _ftol2_sse();
    local_54[0].y = extraout_EAX_04;
    _ftol2_sse();
    _ftol2_sse();
    Graphic_Line(DisplayInterface::currentBuffer,local_54[0].x,local_54[0].y,extraout_EAX_05,
                 extraout_EAX_06,DisplayInterface::colorWhite,SOLID_PIXELS);
  }
  spriteZ = local_1c;
  return;
}
