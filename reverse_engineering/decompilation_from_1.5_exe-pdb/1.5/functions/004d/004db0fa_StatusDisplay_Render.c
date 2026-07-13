/*
 * Entry: 004db0fa
 * Name: StatusDisplay::Render
 * Namespace: StatusDisplay
 * Signature: void Render(StatusDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall StatusDisplay::Render(StatusDisplay *this)

{
  float fVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  Carrier *this_00;
  OBJECT_CLASS_T OVar5;
  WeaponClass *pWVar6;
  ulong uVar7;
  float fVar8;
  PANE *pPVar9;
  GameObject *pGVar10;
  _GRAPHIC_BUFFER *p_Var11;
  long lVar12;
  long lVar13;
  int iVar14;
  _OBJ76 *p_Var15;
  Weapon *pWVar16;
  long lVar17;
  int iVar18;
  uint uVar19;
  uint uVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  float10 fVar24;
  int iVar25;
  uint local_54;
  int local_48;
  int local_40;
  int local_3c;
  uint local_38;
  int local_30;
  char *local_2c;
  int local_28;
  uint local_24;
  _OBJ76 **local_1c;
  bool local_11;
  int local_10;
  int local_c;
  uint local_8;
  
  lVar13 = Device.Viewport.Height;
  lVar12 = Device.Viewport.Width;
  pGVar10 = GameObject::userObject;
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar23 = 0;
  if (GameObject::userObject != (GameObject *)0x0) {
    local_10 = Device.Viewport.Width + -0xb5;
    this_00 = GameObject::userObject->carrier;
    iVar21 = Device.Viewport.Height + -0x5d;
    iVar14 = Device.Viewport.Width + -0x74;
    if (this_00 == (Carrier *)0x0) {
      local_54 = 0;
      local_38 = 0;
    }
    else {
      local_54 = this_00->selected;
      local_38 = this_00->enabled;
    }
    uVar19 = GameObject::userObject->curAmmo;
    local_30 = 0;
    local_24 = 0;
    local_28 = 0;
    local_c = iVar21;
    local_1c = (_OBJ76 **)this_00;
    do {
      fVar1 = spriteZ;
      local_1c = ((Carrier *)local_1c)->hardpoint;
      if (400 < Device.Viewport.Width) {
        spriteZ = spriteZ + 0.001;
        Clipped_Rect_Filled(DisplayInterface::currentBuffer,lVar12 + -0x75,iVar23 + 0x19 + iVar21,
                            lVar12 + -0x10,iVar23 + 0x23 + iVar21,DisplayInterface::colorBlack,
                            SOLID_PIXELS);
      }
      if (this_00 == (Carrier *)0x0) {
        p_Var15 = (_OBJ76 *)0x0;
      }
      else {
        p_Var15 = *local_1c;
      }
      if (((p_Var15 == (_OBJ76 *)0x0) || (OVar5 = p_Var15->class_id, (int)OVar5 < 0x46)) ||
         (0x4a < (int)OVar5)) {
        local_3c = 0;
      }
      else {
        local_3c = (&RING_MAPS[4].fraction)[OVar5 * 2];
      }
      spriteZ = fVar1;
      if (this_00 == (Carrier *)0x0) {
        pWVar16 = (Weapon *)0x0;
      }
      else {
        pWVar16 = Carrier::GetWeapon(this_00,local_28);
      }
      if (pWVar16 == (Weapon *)0x0) {
        local_40 = 0;
        local_2c = (char *)0x0;
LAB_004db22c:
        lVar17 = 0;
      }
      else {
        pWVar6 = pWVar16->weaponClass;
        local_40 = pWVar6->wpnNameIndex;
        local_2c = pWVar6->wpnName;
        if ((pWVar6->sig == 0x44495350) || (uVar7 = pWVar6->sig, uVar7 == 0x5244524c)) {
          if (pWVar16->ordnanceClass == (OrdnanceClass *)0x0) goto LAB_004db22c;
          lVar17 = *(long *)(pWVar16->ordnanceClass->shotSound + 9);
        }
        else if (((uVar7 == 0x49524546) || (uVar7 == 0x52444d50)) || (uVar7 == 0x54525850)) {
          lVar17 = pWVar6[1]._padding_;
        }
        else {
          if (pWVar16->ordnanceClass == (OrdnanceClass *)0x0) goto LAB_004db22c;
          lVar17 = pWVar16->ordnanceClass->ammoCost;
        }
      }
      if ((int)(uVar19 ^ 0x33333333) < lVar17) {
        local_24 = local_24 | 1 << ((byte)local_28 & 0x1f);
      }
      uVar20 = 1 << ((byte)local_28 & 0x1f);
      if ((local_54 & uVar20) == 0) {
        lVar17 = DisplayInterface::colorGreen;
        if ((local_38 & ~local_24 & uVar20) == 0) {
          lVar17 = DisplayInterface::colorGrey;
        }
      }
      else {
        local_30 = local_30 + lVar17;
        lVar17 = DisplayInterface::colorWhite;
        if ((local_38 & ~local_24 & uVar20) != 0) {
          lVar17 = DisplayInterface::colorYellow;
        }
      }
      Foreground_Color = lVar17;
      if (local_3c != 0) {
        DrawSprite(DisplayInterface::currentBuffer,local_3c,lVar12 + -0x73,iVar23 + 0x1b + iVar21,5)
        ;
      }
      if (local_40 == 0) {
        if (local_2c != (char *)0x0) {
          Font_Set_Foreground(Default_Font,lVar17);
          Font_Print_String(Default_Font,DisplayInterface::currentBuffer,lVar12 + -0x68,
                            iVar23 + 0x1a + iVar21,local_2c);
        }
      }
      else {
        DrawSprite(DisplayInterface::currentBuffer,local_40,lVar12 + -0x68,iVar23 + 0x1a + iVar21,5)
        ;
      }
      local_28 = local_28 + 1;
      iVar23 = iVar23 + 0xc;
    } while (iVar23 < 0x3c);
    if ((local_24 == 0) || (local_11 = true, local_24 != local_38)) {
      local_11 = false;
    }
    if ((this->ammoDepleted == false) && (local_11 != false)) {
      BettyVoice::AmmoWarning(&bettyVoice,pGVar10);
    }
    this->ammoDepleted = local_11;
    fVar24 = (float10)(**(code **)(pGVar10->_padding_ + 0x1c))();
    if ((this->hullDepleted == false) && (fVar24 < (float10)0.25)) {
      BettyVoice::HullWarning(&bettyVoice,pGVar10);
    }
    this->hullDepleted = fVar24 < (float10)0.25;
    fVar1 = spriteZ;
    lVar17 = (DisplayInterface::currentBuffer->Pane).x0;
    lVar2 = (DisplayInterface::currentBuffer->Pane).y0;
    lVar3 = (DisplayInterface::currentBuffer->Pane).x1;
    lVar4 = (DisplayInterface::currentBuffer->Pane).y1;
    if (400 < Device.Viewport.Width) {
      D3IniFlags = D3IniFlags | 0x800;
      spriteZ = spriteZ + 0.001;
      DrawSprite(DisplayInterface::currentBuffer,this->statusLeftIndex,local_10,iVar21,1);
      iVar25 = 1;
      iVar23 = GetSpriteWidth(this->statusLeftIndex);
      DrawSprite(DisplayInterface::currentBuffer,this->statusRightIndex,iVar23 + local_10,iVar21,
                 iVar25);
      D3IniFlags = D3IniFlags & 0xfffff7ff;
    }
    iVar23 = local_10 + 5;
    iVar25 = local_c + 0x4a;
    iVar22 = lVar13 + -0x4c;
    iVar21 = local_10 + 0x23;
    spriteZ = fVar1;
    Foreground_Color = GetHealthColor(this->hullRatio);
    DrawSprite(DisplayInterface::currentBuffer,this->hullTitleIndex,iVar21,lVar13 + -0x56,0x20005);
    fVar1 = this->hullRatio;
    fVar8 = (float)Float2Int;
    (DisplayInterface::currentBuffer->Pane).x0 = iVar23;
    local_48 = SUB84((double)((1.0 - fVar1) * (float)((iVar25 - iVar22) + 1) + fVar8),0);
    (DisplayInterface::currentBuffer->Pane).y0 = local_48 + iVar22;
    (DisplayInterface::currentBuffer->Pane).x1 = iVar21;
    (DisplayInterface::currentBuffer->Pane).y1 = iVar25;
    DrawSprite(DisplayInterface::currentBuffer,this->hullGaugeIndex,0,-local_48,0x200005);
    iVar21 = local_10;
    p_Var11 = DisplayInterface::currentBuffer;
    pPVar9 = &DisplayInterface::currentBuffer->Pane;
    (DisplayInterface::currentBuffer->Pane).x0 = lVar17;
    pPVar9->y0 = lVar2;
    (p_Var11->Pane).x1 = lVar3;
    (p_Var11->Pane).y1 = lVar4;
    iVar23 = local_10 + 0x2a;
    iVar18 = local_10 + 0x37;
    Foreground_Color = DisplayInterface::colorBlue;
    DrawSprite(DisplayInterface::currentBuffer,this->ammoTitleIndex,iVar23,lVar13 + -0x56,5);
    fVar1 = this->ammoRatio;
    fVar8 = (float)Float2Int;
    (DisplayInterface::currentBuffer->Pane).x0 = iVar23;
    local_48 = SUB84((double)((1.0 - fVar1) * (float)((iVar25 - iVar22) + 1) + fVar8),0);
    (DisplayInterface::currentBuffer->Pane).y0 = iVar22 + local_48;
    (DisplayInterface::currentBuffer->Pane).x1 = iVar18;
    (DisplayInterface::currentBuffer->Pane).y1 = iVar25;
    DrawSprite(DisplayInterface::currentBuffer,this->ammoGaugeIndex,0,-local_48,0x200001);
    p_Var11 = DisplayInterface::currentBuffer;
    pPVar9 = &DisplayInterface::currentBuffer->Pane;
    (DisplayInterface::currentBuffer->Pane).x0 = lVar17;
    pPVar9->y0 = lVar2;
    (p_Var11->Pane).x1 = lVar3;
    (p_Var11->Pane).y1 = lVar4;
    if (0 < local_30) {
      Font_Set_Foreground(Default_Font,DisplayInterface::colorWhite);
      sprintf((char *)&local_10,"%4d",
              (int)((longlong)
                    (CONCAT44((int)(pGVar10->curAmmo ^ 0x33333333U) >> 0x1f,pGVar10->curAmmo) ^
                    0x33333333) / (longlong)local_30));
      local_1c = (_OBJ76 **)(lVar13 + -0x56);
      iVar23 = IsJapanese();
      if (iVar23 != 0) {
        iVar14 = lVar12 + -0x5e;
        local_1c = (_OBJ76 **)(lVar13 + -0x52);
      }
      Font_Print_String(Default_Font,DisplayInterface::currentBuffer,iVar14,(long)local_1c,
                        (char *)&local_10);
    }
    fVar1 = 0.0;
    uVar19 = pGVar10->maxAmmo ^ 0x33333333;
    if (uVar19 != 0) {
      fVar1 = (float)local_30 / (float)(int)uVar19;
    }
    fVar1 = this->ammoRatio - fVar1;
    if (0.0 < fVar1) {
      local_48 = SUB84((double)(fVar1 * (float)((iVar22 - iVar25) + 1) + (float)iVar25 +
                               (float)Float2Int),0);
      Clipped_Rect_Filled(DisplayInterface::currentBuffer,iVar21 + 0x32,local_48,iVar18,local_48,
                          DisplayInterface::colorWhite,SOLID_PIXELS);
      Clipped_Rect_Filled(DisplayInterface::currentBuffer,iVar21 + 0x34,local_48 + 1,iVar18,
                          local_48 + 1,DisplayInterface::colorWhite,SOLID_PIXELS);
      Clipped_Rect_Filled(DisplayInterface::currentBuffer,iVar21 + 0x36,local_48 + 2,iVar18,
                          local_48 + 2,DisplayInterface::colorWhite,SOLID_PIXELS);
    }
  }
  return;
}
