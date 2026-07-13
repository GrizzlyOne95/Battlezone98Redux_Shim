/*
 * Entry: 004d577f
 * Name: PathDisplay::DrawObject
 * Namespace: PathDisplay
 * Signature: void DrawObject(PathDisplay * this, GameObject * param_1, bool param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
PathDisplay::DrawObject(PathDisplay *this,GameObject *param_1,bool param_2,long param_3)

{
  float *pfVar1;
  SPHERE *pSVar2;
  int iVar3;
  POLYGON_SKIN PVar4;
  long extraout_EAX;
  long extraout_EAX_00;
  long extraout_EAX_01;
  long extraout_EAX_02;
  long extraout_EAX_03;
  long extraout_EAX_04;
  long extraout_EAX_05;
  long extraout_EAX_06;
  long extraout_EAX_07;
  long extraout_EAX_08;
  long extraout_EAX_09;
  long extraout_EAX_10;
  long extraout_EAX_11;
  long extraout_EAX_12;
  long extraout_EAX_13;
  long extraout_EAX_14;
  long lVar5;
  long extraout_EAX_15;
  long extraout_EAX_16;
  char *pcVar6;
  GameObject *unaff_EDI;
  int *piVar7;
  POINT_3D *pPVar8;
  bool bVar9;
  float fVar10;
  long lVar11;
  long lVar12;
  long *plVar13;
  long lVar14;
  float *pfVar15;
  GameObject **ppGVar16;
  BITMAP_OPER BVar17;
  long *plVar18;
  POINT_3D local_84;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  float local_24;
  float local_20;
  long local_1c;
  float local_18;
  float local_14;
  int local_10;
  int local_c;
  char local_5;
  
  local_24 = spriteZ;
  if (param_2) {
    spriteZ = 0.4;
  }
  else {
    spriteZ = 1.0;
  }
  piVar7 = &param_1->_padding_;
  pfVar1 = (float *)(**(code **)(*piVar7 + 0xc))();
  local_14 = param_1->collisionRadius;
  pSVar2 = GameObject::GetSphere(param_1);
  local_18 = pSVar2->radius;
  local_5 = param_2;
  fVar10 = Min(local_14,local_18);
  if (fVar10 * this->scale <= 4.0) {
    WorldToScreen(this,*pfVar1,pfVar1[2],local_14,(long *)&local_20,&local_c,&local_10,&local_1c);
    Graphic_Rect_Filled(DisplayInterface::currentBuffer,(long)local_20,local_c,local_10,local_1c,
                        param_3,SOLID_PIXELS);
    BVar17 = SOLID_PIXELS;
    lVar5 = GameObject::GetColor(param_1);
    Graphic_Rect_Filled(DisplayInterface::currentBuffer,(int)local_20 + 1,local_c + 1,local_10 + -1,
                        local_1c + -1,lVar5,BVar17);
  }
  else {
    iVar3 = (**(code **)*piVar7)();
    local_84.Vector.x = *(float *)(iVar3 + 0x114);
    local_84.Vector.y = *(float *)(iVar3 + 0x118);
    local_1c = 4;
    local_84.Vector.z = *(float *)(iVar3 + 0x11c);
    local_84.Texel.u = 0.0;
    local_84.Texel.v = 0.0;
    local_84.Texel.field2_0x8.luma = 0.0;
    local_6c = *(undefined4 *)(iVar3 + 0x120);
    local_68 = *(undefined4 *)(iVar3 + 0x118);
    local_64 = *(undefined4 *)(iVar3 + 0x11c);
    local_60 = 0;
    uStack_5c = 0;
    uStack_58 = 0;
    local_54 = *(undefined4 *)(iVar3 + 0x120);
    local_50 = *(undefined4 *)(iVar3 + 0x118);
    local_4c = *(undefined4 *)(iVar3 + 0x128);
    local_48 = 0;
    uStack_44 = 0;
    uStack_40 = 0;
    local_3c = *(float *)(iVar3 + 0x114);
    local_38 = *(undefined4 *)(iVar3 + 0x118);
    local_34 = *(undefined4 *)(iVar3 + 0x128);
    local_30 = 0;
    uStack_2c = 0;
    local_20 = 1.0 / spriteZ;
    uStack_28 = 0;
    pPVar8 = &local_84;
    do {
      Vector_Transform(&pPVar8->Vector,&pPVar8->Vector,1,&param_1->obj->transform);
      (**(code **)(this->_padding_ + 0x20))();
      (pPVar8->Vector).x = (float)local_10;
      local_1c = local_1c + -1;
      bVar9 = local_1c != 0;
      (pPVar8->Vector).y = (float)local_c;
      (pPVar8->Vector).z = local_20;
      (pPVar8->Texel).field2_0x8.luma = 1.0;
      pPVar8 = pPVar8 + 1;
    } while (bVar9);
    PVar4.Color = GameObject::GetColor(param_1);
    if (useD3D == 0) {
      __Camera_Software_Draw_polygon__(&View_Record.MainCam,&local_84,4,PVar4,8);
    }
    else {
      __Camera_Hardware_Draw_polygon__(&View_Record.MainCam,&local_84,4,PVar4,8);
    }
    BVar17 = SOLID_PIXELS;
    lVar14 = param_3;
    _ftol2_sse();
    lVar5 = extraout_EAX;
    _ftol2_sse();
    lVar12 = extraout_EAX_00;
    _ftol2_sse();
    lVar11 = extraout_EAX_01;
    _ftol2_sse();
    Graphic_Line(DisplayInterface::currentBuffer,extraout_EAX_02,lVar11,lVar12,lVar5,lVar14,BVar17);
    BVar17 = SOLID_PIXELS;
    lVar14 = param_3;
    _ftol2_sse();
    lVar5 = extraout_EAX_03;
    _ftol2_sse();
    lVar12 = extraout_EAX_04;
    _ftol2_sse();
    lVar11 = extraout_EAX_05;
    _ftol2_sse();
    Graphic_Line(DisplayInterface::currentBuffer,extraout_EAX_06,lVar11,lVar12,lVar5,lVar14,BVar17);
    BVar17 = SOLID_PIXELS;
    lVar14 = param_3;
    _ftol2_sse();
    lVar5 = extraout_EAX_07;
    _ftol2_sse();
    lVar12 = extraout_EAX_08;
    _ftol2_sse();
    lVar11 = extraout_EAX_09;
    _ftol2_sse();
    Graphic_Line(DisplayInterface::currentBuffer,extraout_EAX_10,lVar11,lVar12,lVar5,lVar14,BVar17);
    BVar17 = SOLID_PIXELS;
    lVar14 = param_3;
    _ftol2_sse();
    lVar5 = extraout_EAX_11;
    _ftol2_sse();
    lVar12 = extraout_EAX_12;
    _ftol2_sse();
    lVar11 = extraout_EAX_13;
    _ftol2_sse();
    Graphic_Line(DisplayInterface::currentBuffer,extraout_EAX_14,lVar11,lVar12,lVar5,lVar14,BVar17);
    (**(code **)(this->_padding_ + 0x20))();
    BVar17 = SOLID_PIXELS;
    lVar5 = GameObject::GetColor(param_1);
    lVar14 = 0x10;
    floor((double)(this->scale * local_18 + 0.5));
    _ftol2_sse();
    Graphic_Circle(DisplayInterface::currentBuffer,local_10,local_c,extraout_EAX_15,lVar14,lVar5,
                   BVar17);
    BVar17 = SOLID_PIXELS;
    lVar14 = 0x10;
    lVar5 = param_3;
    floor((double)(this->scale * local_14 + 0.5));
    _ftol2_sse();
    Graphic_Circle(DisplayInterface::currentBuffer,local_10,local_c,extraout_EAX_16,lVar14,lVar5,
                   BVar17);
    if ((this->controlMode == CONTROL_OBJECT) ||
       ((this->controlMode == CONTROL_TASK && (param_1->aiProcess != (AiProcess *)0x0)))) {
      local_5 = '\x01';
    }
  }
  if (param_1 == GameObject::userObject) {
    local_5 = '\x01';
  }
  if (local_5 != '\0') {
    plVar18 = &param_3;
    ppGVar16 = &param_1;
    pfVar15 = &local_20;
    plVar13 = &local_1c;
    fVar10 = Max(local_14,local_18);
    WorldToScreen(this,*pfVar1,pfVar1[2],fVar10,plVar13,(long *)pfVar15,(long *)ppGVar16,plVar18);
    if (param_2 == false) {
      spriteZ = 0.2;
    }
    else {
      spriteZ = 0.15;
    }
    pcVar6 = GetObjectName(unaff_EDI);
    Graphic_Text(DisplayInterface::currentBuffer,((int)&param_1->_padding_ + local_1c) / 2,
                 (int)local_20 + -2,(long *)&param_1,&param_3,pcVar6,DisplayInterface::textFont,
                 DisplayInterface::colorWhite,DisplayInterface::colorBlack,
                 (param_2 != false) - 1 & 2,1,2);
  }
  spriteZ = local_24;
  return;
}
