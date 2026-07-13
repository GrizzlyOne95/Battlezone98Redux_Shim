/*
 * Entry: 004cae2f
 * Name: EditTerrain::DrawBrushShape
 * Namespace: EditTerrain
 * Signature: void DrawBrushShape(EditTerrain * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall EditTerrain::DrawBrushShape(EditTerrain *this,int param_1)

{
  int *piVar1;
  long lVar2;
  long extraout_EAX;
  long extraout_EAX_00;
  long extraout_EAX_01;
  long extraout_EAX_02;
  float extraout_EAX_03;
  long extraout_EAX_04;
  int iVar3;
  int iVar4;
  float (*pafVar5) [64];
  char *pcVar6;
  double dVar7;
  long local_d0 [4];
  long local_c0;
  long local_bc;
  float local_b8;
  long local_b4;
  long local_b0;
  long local_ac;
  long local_a8;
  long local_a4;
  long local_a0;
  long local_9c;
  long local_98;
  long local_94;
  long local_90;
  long local_8c;
  long local_80;
  undefined8 local_7c;
  float local_74;
  float local_70;
  float local_6c;
  int local_68;
  float local_64;
  int local_60;
  float (*local_5c) [64];
  float (*local_58) [64];
  int local_54;
  float (*local_50) [64];
  int local_4c;
  char local_48 [64];
  uint local_8;
  
  local_8 = __security_cookie ^ (int)&local_7c + 4U;
  local_70 = spriteZ;
  spriteZ = spriteZ + 0.3;
  Clipped_Rect_Filled(DisplayInterface::currentBuffer,(this->brushRect).left,(this->brushRect).top,
                      (this->brushRect).right,(this->brushRect).bottom,DisplayInterface::colorGrey,
                      SOLID_PIXELS);
  if (param_1 == 0xd) {
    _ftol2_sse();
    pcVar6 = "Width=%2d";
LAB_004caf1c:
    sprintf(local_48,pcVar6);
  }
  else {
    if (param_1 == 0xe) {
      dVar7 = (double)this->brushY;
      pcVar6 = "Height=%.1f";
    }
    else if (param_1 == 0xf) {
      dVar7 = (double)this->brushInc;
      pcVar6 = "Incr=%.1f";
    }
    else {
      if (param_1 == 0x13) {
        _ftol2_sse();
        pcVar6 = "Depth=%2d";
        goto LAB_004caf1c;
      }
      if (param_1 != 0x14) goto LAB_004caf29;
      dVar7 = (double)this->brushSD;
      pcVar6 = "Bell width=%.2f";
    }
    sprintf(local_48,pcVar6,dVar7);
  }
LAB_004caf29:
  lVar2 = Font_Get_String_Length(Default_Font,local_48);
  spriteZ = local_70 + 0.2;
  this->textDX = lVar2;
  iVar3 = (this->brushRect).top;
  Clipped_Rect_Filled(DisplayInterface::currentBuffer,(this->brushRect).left + 2,iVar3 + 2,
                      (this->brushRect).right + -2,iVar3 + 4 + this->textDY,this->textBG,
                      SOLID_PIXELS);
  Font_Set_Foreground(Default_Font,this->textFG);
  spriteZ = local_70 + 0.1;
  local_6c = spriteZ;
  Font_Print_String(Default_Font,DisplayInterface::currentBuffer,(this->brushRect).left + 4,
                    (this->brushRect).top + 4,local_48);
  iVar3 = this->brushDX;
  local_4c = (this->brushRect).left + 3;
  iVar4 = (this->brushDY - this->textDY) + -6;
  local_54 = iVar4;
  _ftol2_sse();
  local_7c = (double)local_54;
  local_4c = (this->brushRect).bottom + -3;
  local_64 = (float)extraout_EAX;
  _ftol2_sse();
  local_54 = 0;
  local_74 = (float)(this->brushWidth * (iVar3 + -6));
  local_5c = (float (*) [64])-(int)local_74;
  iVar4 = this->brushDepth * iVar4;
  pafVar5 = (float (*) [64])-iVar4;
  local_60 = 3;
  do {
    local_50 = pafVar5;
    _ftol2_sse();
    local_58 = local_5c;
    local_50 = (float (*) [64])0x3;
    local_4c = extraout_EAX_00;
    do {
      _ftol2_sse();
      local_d0[local_54 * 2] = extraout_EAX_01;
      local_d0[local_54 * 2 + 1] = local_4c;
      local_58 = (float (*) [64])((int)*local_58 + (int)local_74);
      local_54 = local_54 + 1;
      local_50 = (float (*) [64])((int)local_50 + -1);
    } while (local_50 != (float (*) [64])0x0);
    pafVar5 = (float (*) [64])((int)*pafVar5 + iVar4);
    local_60 = local_60 + -1;
  } while (local_60 != 0);
  local_50 = pafVar5;
  _ftol2_sse();
  spriteZ = local_6c;
  Graphic_Line(DisplayInterface::currentBuffer,local_d0[2],local_d0[3],local_98,local_94,
               DisplayInterface::colorGrey,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,(long)local_b8,local_b4,local_a8,local_a4,
               DisplayInterface::colorGrey,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_d0[0],local_d0[1],local_c0,local_bc,
               DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_c0,local_bc,local_90,local_8c,
               DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_90,local_8c,local_a0,local_9c,
               DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_a0,local_9c,local_d0[0],local_d0[1],
               DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_b0,local_ac,(long)local_64,extraout_EAX_02,
               DisplayInterface::colorWhite,SOLID_PIXELS);
  if (1 < this->brushDepth) {
    piVar1 = &this->brushWidth;
    if (1 < *piVar1) {
      if (((this->brushSD != this->bellSD) || (this->bellWidth != *piVar1)) ||
         (this->bellDepth != this->brushDepth)) {
        CreateBell(this);
      }
      local_6c = local_b8;
      local_4c = local_b4;
      local_54 = 0;
      if (-1 < this->brushDepth) {
        local_50 = this->bell;
        do {
          local_60 = 0;
          if (-1 < *piVar1) {
            local_74 = (float)(int)local_b8;
            local_68 = local_a8 - (int)local_b8;
            local_5c = (float (*) [64])0x0;
            local_58 = local_50;
            do {
              _ftol2_sse();
              local_64 = extraout_EAX_03;
              _ftol2_sse();
              local_80 = extraout_EAX_04;
              Graphic_Line(DisplayInterface::currentBuffer,(long)local_6c,local_4c,(long)local_64,
                           extraout_EAX_04,DisplayInterface::colorWhite,SOLID_PIXELS);
              local_6c = local_64;
              local_58 = (float (*) [64])(*local_58 + 1);
              local_4c = local_80;
              local_5c = (float (*) [64])((int)*local_5c + local_68);
              local_60 = local_60 + 1;
            } while (local_60 <= *piVar1);
          }
          local_54 = local_54 + 1;
          local_50 = local_50 + 1;
        } while (local_54 <= this->brushDepth);
      }
    }
  }
  piVar1 = &this->brushDX;
  DrawBoxOutline(this,DisplayInterface::currentBuffer,(this->brushRect).left,(this->brushRect).top,
                 (float)*piVar1,DisplayInterface::colorWhite);
  local_68 = *piVar1 + -2;
  DrawBoxOutline(this,DisplayInterface::currentBuffer,(this->brushRect).left + 1,
                 (this->brushRect).top + 1,(float)local_68,DisplayInterface::colorGrey);
  local_68 = *piVar1 + -4;
  DrawBoxOutline(this,DisplayInterface::currentBuffer,(this->brushRect).left + 2,
                 (this->brushRect).top + 2,(float)local_68,DisplayInterface::colorWhite);
  iVar3 = (this->brushRect).top + 2;
  Graphic_Line(DisplayInterface::currentBuffer,(this->brushRect).left + 2,iVar3,
               (this->brushRect).right + -2,iVar3,DisplayInterface::colorBlack,SOLID_PIXELS);
  iVar3 = (this->brushRect).left + 2;
  Graphic_Line(DisplayInterface::currentBuffer,iVar3,(this->brushRect).top + 2,iVar3,
               (this->brushRect).bottom + -2,DisplayInterface::colorBlack,SOLID_PIXELS);
  lVar2 = (this->brushRect).bottom;
  Graphic_Line(DisplayInterface::currentBuffer,(this->brushRect).right,lVar2,(this->brushRect).left,
               lVar2,DisplayInterface::colorBlack,SOLID_PIXELS);
  lVar2 = (this->brushRect).right;
  Graphic_Line(DisplayInterface::currentBuffer,lVar2,(this->brushRect).top,lVar2,
               (this->brushRect).bottom,DisplayInterface::colorBlack,SOLID_PIXELS);
  spriteZ = local_70;
  return;
}
