/*
 * Entry: 004c05b7
 * Name: CockpitRadar::Render
 * Namespace: CockpitRadar
 * Signature: void Render(CockpitRadar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitRadar::Render(CockpitRadar *this)

{
  int iVar1;
  VECTOR_3D VVar2;
  _Vector_iterator<RadarItem,std::allocator<RadarItem>_> _Var3;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar4;
  CAMERA *pCVar5;
  GameObject *this_00;
  bool bVar6;
  char cVar7;
  GameObject **ppGVar8;
  RadarItem *pRVar9;
  float *pfVar10;
  int iVar11;
  ulong uVar12;
  long *plVar13;
  VECTOR_3D *pVVar14;
  int extraout_EAX;
  float fVar15;
  uint uVar16;
  int *piVar17;
  long lVar18;
  GameObject *pGVar19;
  float fVar20;
  int iVar21;
  float unaff_EDI;
  uint uVar22;
  float10 fVar23;
  tagPOINT tVar24;
  tagPOINT tVar25;
  double dVar26;
  undefined1 *puVar27;
  undefined1 *puVar28;
  RadarItem *pRVar29;
  float fVar30;
  VECTOR_3D local_1b4;
  VECTOR_3D local_1a8;
  VECTOR_3D local_19c;
  VECTOR_3D local_190;
  VECTOR_3D local_184;
  VECTOR_3D local_178;
  float local_16c;
  float fStack_168;
  float fStack_164;
  float local_160;
  float fStack_15c;
  float fStack_158;
  float local_154;
  float fStack_150;
  float fStack_14c;
  float local_148;
  float fStack_144;
  float fStack_140;
  float local_13c;
  float fStack_138;
  float fStack_134;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  float local_10c;
  float local_108;
  float local_104;
  VECTOR_3D local_100;
  VECTOR_3D local_f4;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0 [7];
  long local_b4 [6];
  _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> local_9c;
  _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> local_94;
  float local_8c;
  float local_88;
  float local_84;
  _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> local_80;
  VECTOR_3D local_78;
  float local_6c;
  undefined8 local_68;
  GameObject *local_60;
  _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> local_5c;
  VECTOR_3D local_54;
  _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> local_48;
  char local_3d;
  GameObject *local_3c;
  char local_35;
  uint local_34;
  float local_30;
  float local_2c;
  char local_26;
  char local_25;
  vector<GameObject_*,std::allocator<GameObject_*>_> *local_24;
  GameObject *local_20;
  _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> local_1c;
  uint local_14;
  char local_10;
  bool local_f;
  char local_e;
  char local_d;
  int local_c;
  char local_6;
  char local_5;
  
  if ((((this->scanner != (Scanner *)0x0) && (this->userObj != (GameObject *)0x0)) &&
      (useDisplayInterface != 0)) && (hudFlags != 0)) {
    TimeStepLocal();
    UpdateRadarData(Device.Viewport.Height);
    pCVar5 = DisplayInterface::currentCamera;
    local_54.x = DisplayInterface::currentCamera->View_Volume[0].surf_normal.z * this->range;
    local_54.z = DisplayInterface::currentCamera->View_Volume[0].surf_normal.x * this->range;
    local_54.y = RADAR_SIN * local_54.z;
    local_54.z = local_54.z * RADAR_COS;
    tVar24 = ConvertPos((VECTOR_3D *)this->range,unaff_EDI);
    local_94._Myptr = (RadarItem *)tVar24.y;
    local_54.x = -(pCVar5->View_Volume[1].surf_normal.z * this->range);
    fVar20 = pCVar5->View_Volume[1].surf_normal.x * this->range;
    local_54.y = -(RADAR_SIN * fVar20);
    local_54.z = -(fVar20 * RADAR_COS);
    tVar25 = ConvertPos((VECTOR_3D *)this->range,unaff_EDI);
    local_48._Myptr = (RadarItem *)tVar25.y;
    Clipped_Line(DisplayInterface::currentBuffer,tVar24.x,(long)local_94._Myptr,RADAR_CENTER.x,
                 RADAR_CENTER.y,10,ALPHA_PIXELS);
    Clipped_Line(DisplayInterface::currentBuffer,tVar25.x,(long)local_48._Myptr,RADAR_CENTER.x,
                 RADAR_CENTER.y,10,ALPHA_PIXELS);
    local_e8 = this->range * (this->mat).right_x;
    local_e4 = (this->mat).up_x * this->range;
    local_e0 = this->range * (this->mat).front_x;
    local_dc = (this->mat).right_z * this->range;
    local_d8 = (this->mat).up_z * this->range;
    local_d4 = (this->mat).front_z * this->range;
    local_d0[0] = -local_e8;
    local_d0[1] = -local_e4;
    local_d0[2] = -local_e0;
    uVar22 = 0;
    local_d0[3] = -local_dc;
    local_d0[4] = -local_d8;
    local_d0[5] = -local_d4;
    do {
      tVar24 = ConvertPos((VECTOR_3D *)this->range,unaff_EDI);
      DrawSprite(DisplayInterface::currentBuffer,*(int *)((int)&COMPASS_DIR[0].index + uVar22),
                 tVar24.x,tVar24.y,0x250001);
      uVar22 = uVar22 + 8;
    } while (uVar22 < 0x20);
    std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::
    _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>
              (&local_80,radarList._Myfirst,(_Container_base_aux *)&radarList);
    pvVar4 = GameObject::objectList;
    local_24 = GameObject::objectList;
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)&local_48,
               GameObject::objectList->_Myfirst,(_Container_base_aux *)GameObject::objectList);
    local_1c = local_48;
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)&local_5c,
               pvVar4->_Mylast,(_Container_base_aux *)pvVar4);
    bVar6 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)
                       &local_1c,
                       (_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)
                       &local_5c);
    while (bVar6 == false) {
      ppGVar8 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                          ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)
                           &local_1c);
      local_20 = *ppGVar8;
      if (0.0 < local_20->illumination) {
        std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::
        _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>
                  (&local_94,radarList._Mylast,(_Container_base_aux *)&radarList);
        bVar6 = std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::operator==
                          (&local_80,&local_94);
        if (bVar6) break;
        local_78.x = (this->userPos).x;
        local_78.y = (this->userPos).y;
        local_78.z = (this->userPos).z;
        pfVar10 = (float *)(**(code **)(local_20->_padding_ + 0xc))();
        local_54.x = *pfVar10;
        local_54.y = pfVar10[1];
        local_54.z = pfVar10[2];
        local_6c = local_54.x - local_78.x;
        local_68 = (double)CONCAT44(local_54.z - local_78.z,local_54.y - local_78.y);
        if (local_20->isObjective == false) {
          iVar11 = (**(code **)(this->userObj->_padding_ + 4))();
          piVar17 = &local_20->_padding_;
          iVar21 = (**(code **)(*piVar17 + 4))();
          if (((iVar21 != iVar11) &&
              (iVar11 = (**(code **)*piVar17)(), *(int *)(iVar11 + 0x28) != 6)) &&
             (iVar11 = (**(code **)*piVar17)(), *(int *)(iVar11 + 0x28) != 1)) {
            if (this->rangeSq <=
                local_6c * local_6c +
                (float)local_68 * (float)local_68 + local_68._4_4_ * local_68._4_4_)
            goto LAB_004c08d5;
          }
        }
        local_48 = (_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>)
                   (double)((local_6c * (this->mat).front_x +
                            (this->mat).front_y * (float)local_68 +
                            (this->mat).front_z * local_68._4_4_) * 65536.0 + (float)Float2Int);
        pRVar9 = std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::operator*
                           (&local_80);
        pRVar9->obj = local_20;
        pRVar9 = std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::operator*
                           (&local_80);
        pRVar9->z = local_48._padding_;
        std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::operator++(&local_80);
      }
LAB_004c08d5:
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++
                ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)&local_1c);
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)&local_5c,
                 local_24->_Mylast,(_Container_base_aux *)local_24);
      bVar6 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                        ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)
                         &local_1c,
                         (_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)
                         &local_5c);
    }
    std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::
    _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>
              (&local_48,radarList._Myfirst,(_Container_base_aux *)&radarList);
    _Var3._4_4_ = local_80._Myptr;
    _Var3._0_4_ = local_80._padding_;
    std::sort<std::_Vector_iterator<RadarItem,std::allocator<RadarItem>_>_>
              ((_Vector_iterator<RadarItem,std::allocator<RadarItem>_>)local_48,_Var3);
    local_60 = (GameObject *)controlPanel.currentItem;
    local_d0[0] = -NAN;
    local_d0[1] = -NAN;
    local_d0[2] = -NAN;
    local_d0[3] = -NAN;
    local_d0[4] = -NAN;
    local_d0[5] = -NAN;
    local_b4[0] = CONNECTOR_POS.y;
    local_b4[1] = CONNECTOR_POS.y;
    local_b4[2] = CONNECTOR_POS.y;
    local_b4[3] = CONNECTOR_POS.y;
    local_b4[4] = CONNECTOR_POS.y;
    local_b4[5] = CONNECTOR_POS.y;
    local_d0[6] = Get_TimeLocal();
    std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::
    _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>
              (&local_5c,radarList._Myfirst,(_Container_base_aux *)&radarList);
    while( true ) {
      bVar6 = std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::operator==
                        (&local_5c,&local_80);
      if (bVar6) break;
      local_94._padding_ = local_5c._padding_;
      local_94._Myptr = local_5c._Myptr;
      std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::operator++(&local_5c);
      pRVar9 = std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::operator*
                         (&local_94);
      local_3c = pRVar9->obj;
      local_130 = (this->userPos).x;
      local_12c = (this->userPos).y;
      local_128 = (this->userPos).z;
      pfVar10 = (float *)(**(code **)(local_3c->_padding_ + 0xc))();
      this_00 = local_3c;
      local_124 = *pfVar10;
      local_120 = pfVar10[1];
      local_11c = pfVar10[2];
      local_8c = local_124 - local_130;
      local_88 = local_120 - local_12c;
      local_84 = local_11c - local_128;
      local_2c = (float)local_3c->teamSlot;
      local_24 = (vector<GameObject_*,std::allocator<GameObject_*>_> *)
                 (local_8c * local_8c + local_88 * local_88 + local_84 * local_84);
      piVar17 = &local_3c->_padding_;
      local_78.x = local_8c;
      local_78.y = local_88;
      local_78.z = local_84;
      iVar11 = (**(code **)(*piVar17 + 4))();
      local_5 = iVar11 == this->userTeam;
      local_35 = this_00->isObjective;
      local_e = this_00 == this->targetObj;
      iVar11 = (**(code **)*piVar17)();
      local_3d = *(int *)(iVar11 + 0x28) == 2;
      iVar11 = (**(code **)*piVar17)();
      if (*(int *)(iVar11 + 0x28) == 5) {
LAB_004c0a5f:
        local_26 = '\x01';
      }
      else {
        iVar11 = (**(code **)this_00->_padding_)();
        local_26 = '\0';
        if (*(int *)(iVar11 + 0x28) == 7) goto LAB_004c0a5f;
      }
      piVar17 = &this_00->_padding_;
      iVar11 = (**(code **)*piVar17)();
      if (*(int *)(iVar11 + 0x28) == 3) {
LAB_004c0a82:
        local_25 = '\x01';
      }
      else {
        iVar11 = (**(code **)*piVar17)();
        local_25 = '\0';
        if (*(int *)(iVar11 + 0x28) == 4) goto LAB_004c0a82;
      }
      local_f = true;
      bVar6 = this->rangeSq <= (float)local_24;
      if (bVar6) {
        local_f = false;
      }
      local_f = !bVar6;
      local_30 = this_00->enemyShot;
      if ((local_5 == '\0') || (this_00->enemyShot + 2.0 <= local_d0[6])) {
        local_d = '\0';
LAB_004c0ae2:
        local_6 = '\0';
      }
      else {
        local_d = '\x01';
        fVar23 = (float10)(**(code **)(*piVar17 + 0x1c))();
        if (fVar23 < (float10)0.0) goto LAB_004c0ae2;
        uVar12 = Get_Time_Long();
        local_6 = '\x01';
        if (-1 < (char)uVar12) goto LAB_004c0ae2;
      }
      if ((local_5 == '\0') || (local_10 = '\x01', this_00->isSelected == false)) {
        local_10 = '\0';
      }
      local_14 = 0xffffffff;
      local_20 = (GameObject *)0xffffffff;
      local_c = -1;
      uVar22 = DisplayInterface::colorRed;
      if (local_6 == '\0') {
        local_68 = (double)(this_00->illumination * 15.0 + (float)Float2Int);
        lVar18 = GameObject::GetColor(this_00);
        uVar22 = (uint)DisplayInterface::colorRamp[(int)(float)local_68][lVar18];
      }
      local_34 = uVar22;
      if (((local_5 != '\0') && (this_00 != this->userObj)) && (nextBeep < local_30)) {
        StartGASEvent("cgrowl.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
        nextBeep = local_30 + 1.0;
      }
      if (controlPanel.menuMode == MENU_TYPE_PANEL) {
        if (((local_5 != '\0') && (local_d != '\0')) && (-1 < (int)local_2c)) {
          pGVar19 = (GameObject *)0x0;
          plVar13 = &UNIT_TYPE_INFO[0].maxSlot;
          do {
            if ((((<unnamed_type_UNIT_TYPE_INFO> *)(plVar13 + -1))->minSlot <= (int)local_2c) &&
               ((int)local_2c <= *plVar13)) {
              if (local_6 == '\0') {
                cVar7 = (**(code **)(this_00->_padding_ + 0x38))();
                if ((cVar7 == '\0') || (local_c = 3, this_00->isCargo != false)) {
                  local_c = 5;
                }
              }
              else {
                local_c = 0;
              }
              iVar11 = MODE_BUTTON_RECT[(int)pGVar19].bottom + MODE_BUTTON_RECT[(int)pGVar19].top;
              local_20 = pGVar19;
              lVar18 = MODE_BUTTON_RECT[(int)pGVar19].left;
              goto LAB_004c0f78;
            }
            pGVar19 = (GameObject *)((int)&pGVar19->_padding_ + 1);
            plVar13 = plVar13 + 4;
          } while (pGVar19 < (GameObject *)0x8);
        }
      }
      else if (controlPanel.menuMode == MENU_UNIT_PANEL) {
        if (((local_5 != '\0') && (-1 < (int)local_60)) && (local_60 < (GameObject *)0x8)) {
          if ((UNIT_TYPE_INFO[(int)local_60].minSlot <= (int)local_2c) &&
             ((int)local_2c <= UNIT_TYPE_INFO[(int)local_60].maxSlot)) {
            uVar22 = (int)local_2c - UNIT_TYPE_INFO[(int)local_60].minSlot;
            local_20 = local_60;
            local_14 = uVar22;
            if (local_6 == '\0') {
              if (uVar22 == controlPanel.menuItem) {
                local_c = 1;
              }
              else if (local_10 == '\0') {
                cVar7 = (**(code **)(this_00->_padding_ + 0x38))();
                if ((cVar7 == '\0') || (local_c = 3, this_00->isCargo != false)) {
                  local_c = 5;
                }
              }
              else {
                local_c = 2;
              }
            }
            else {
              local_c = 0;
            }
LAB_004c0cea:
            lVar18 = MODE_BUTTON_RECT[uVar22].left;
            iVar11 = (MODE_BUTTON_RECT[uVar22].bottom + MODE_BUTTON_RECT[uVar22].top) / 2;
            if (iVar11 < local_b4[local_c]) {
              local_b4[local_c] = iVar11;
            }
            Graphic_Line(DisplayInterface::currentBuffer,lVar18,iVar11,CONNECTOR_POS.x,iVar11,
                         stateColor[local_c],SOLID_PIXELS);
          }
        }
      }
      else if (controlPanel.menuMode == MENU_MODE_PANEL) {
        if (((local_5 != '\0') && (-1 < (int)local_60)) && (local_60 < (GameObject *)0x8)) {
          if ((UNIT_TYPE_INFO[(int)local_60].minSlot <= (int)local_2c) &&
             ((int)local_2c <= UNIT_TYPE_INFO[(int)local_60].maxSlot)) {
            local_20 = local_60;
            local_14 = (int)local_2c - UNIT_TYPE_INFO[(int)local_60].minSlot;
            if (local_6 == '\0') {
              if (local_10 == '\0') {
                if (local_d == '\0') goto LAB_004c0fac;
                cVar7 = (**(code **)(this_00->_padding_ + 0x38))();
                if ((cVar7 == '\0') || (local_c = 3, this_00->isCargo != false)) {
                  local_c = 5;
                }
              }
              else {
                local_c = 2;
              }
            }
            else {
              local_c = 0;
            }
            lVar18 = 10;
            iVar11 = 0x1c;
LAB_004c0f78:
            iVar11 = iVar11 / 2;
            if (iVar11 < local_b4[local_c]) {
              local_b4[local_c] = iVar11;
            }
            Clipped_Line(DisplayInterface::currentBuffer,lVar18,iVar11,CONNECTOR_POS.x,iVar11,
                         stateColor[local_c],SOLID_PIXELS);
          }
        }
      }
      else if (controlPanel.menuMode == MENU_NAV_PANEL) {
        if (((local_5 != '\0') && (-1 < (int)local_60)) && (local_60 < (GameObject *)0x8)) {
          if ((UNIT_TYPE_INFO[(int)local_60].minSlot <= (int)local_2c) &&
             ((int)local_2c <= UNIT_TYPE_INFO[(int)local_60].maxSlot)) {
            local_14 = (int)local_2c - UNIT_TYPE_INFO[(int)local_60].minSlot;
            local_20 = local_60;
            uVar22 = local_14;
            if (local_6 == '\0') {
              if (local_14 == controlPanel.menuItem) {
                local_c = 1;
              }
              else {
                local_c = (local_e == '\0') + 2;
              }
            }
            else {
              local_c = 0;
            }
            goto LAB_004c0cea;
          }
        }
      }
      else if (controlPanel.menuMode == MENU_TARGET_PANEL) {
        if (local_5 == '\0') {
          iVar11 = GameObject::GetHandle(this_00);
          uVar22 = 0;
          if (0 < controlPanel.targetNum) {
            do {
              if (controlPanel.targetList[uVar22] == iVar11) {
                local_14 = uVar22;
                if (-1 < (int)uVar22) {
                  if (uVar22 == controlPanel.menuItem) {
                    local_c = 1;
                  }
                  else {
                    local_c = (uint)(local_e == '\0') * 2 + 2;
                  }
                  lVar18 = MODE_BUTTON_RECT[uVar22].left;
                  iVar11 = (MODE_BUTTON_RECT[uVar22].bottom + MODE_BUTTON_RECT[uVar22].top) / 2;
                  if (iVar11 < local_b4[local_c]) {
                    local_b4[local_c] = iVar11;
                  }
                  Graphic_Line(DisplayInterface::currentBuffer,lVar18,iVar11,CONNECTOR_POS.x,iVar11,
                               stateColor[local_c],SOLID_PIXELS);
                  goto LAB_004c0c5e;
                }
                break;
              }
              uVar22 = uVar22 + 1;
            } while ((int)uVar22 < controlPanel.targetNum);
          }
        }
        else {
LAB_004c0c68:
          iVar11 = GameObject::GetHandle(this_00);
          uVar22 = 0;
          if (0 < controlPanel.targetNum) {
            do {
              if (controlPanel.targetList[uVar22] == iVar11) {
                local_14 = uVar22;
                break;
              }
              uVar22 = uVar22 + 1;
            } while ((int)uVar22 < controlPanel.targetNum);
          }
          if (-1 < (int)local_14) {
            uVar22 = local_14;
            if (local_6 == '\0') {
              if (local_14 == controlPanel.menuItem) {
                local_c = 1;
              }
              else if (local_e == '\0') {
                cVar7 = (**(code **)(this_00->_padding_ + 0x38))();
                uVar22 = local_14;
                if ((cVar7 == '\0') || (local_c = 3, this_00->isCargo != false)) {
                  local_c = 5;
                }
              }
              else {
                local_c = 2;
              }
            }
            else {
              local_c = 0;
            }
            goto LAB_004c0cea;
          }
        }
      }
      else if (controlPanel.menuMode == MENU_DEFENSE_PANEL) {
LAB_004c0c5e:
        if (local_5 != '\0') goto LAB_004c0c68;
      }
LAB_004c0fac:
      if (local_f == false) {
        fVar20 = local_8c;
        fVar15 = local_88;
        fVar30 = local_84;
        dVar26 = rsqrt((double)(float)local_24);
        VVar2.y = fVar15;
        VVar2.x = fVar20;
        VVar2.z = fVar30;
        pVVar14 = ScaleVector(&local_178,(float)dVar26 * this->range,VVar2);
        local_78.x = pVVar14->x;
        local_78.y = pVVar14->y;
        local_78.z = pVVar14->z;
        pVVar14 = Vector_Unrotate(&local_190,&local_78,&this->mat);
        local_160 = pVVar14->x;
        fStack_15c = pVVar14->y;
        fStack_158 = pVVar14->z;
        local_1c = (_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>)
                   ConvertPos((VECTOR_3D *)this->range,unaff_EDI);
      }
      else {
        pVVar14 = Vector_Unrotate(&local_1b4,&local_78,&this->mat);
        local_148 = pVVar14->x;
        fStack_144 = pVVar14->y;
        fStack_140 = pVVar14->z;
        local_1c = (_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>)
                   ConvertPos((VECTOR_3D *)this->range,unaff_EDI);
        local_9c = local_1c;
        pfVar10 = (float *)(**(code **)(local_3c->_padding_ + 0xc))();
        local_54.x = *pfVar10;
        local_54.y = pfVar10[1];
        local_54.z = pfVar10[2];
        local_114 = Terrain_FindFloor((double)local_54.x,(double)local_54.z);
        local_10c = (this->userPos).x;
        local_108 = (this->userPos).y;
        local_104 = (this->userPos).z;
        local_118 = local_54.x - local_10c;
        local_114 = local_114 - local_108;
        local_110 = local_54.z - local_104;
        local_54.x = local_118;
        local_54.y = local_114;
        local_54.z = local_110;
        pVVar14 = Vector_Unrotate(&local_19c,&local_54,&this->mat);
        local_16c = pVVar14->x;
        fStack_168 = pVVar14->y;
        fStack_164 = pVVar14->z;
        tVar24 = ConvertPos((VECTOR_3D *)this->range,unaff_EDI);
        uVar22 = local_9c._padding_ - tVar24.x;
        uVar16 = (int)uVar22 >> 0x1f;
        if ((2 < (int)((uVar22 ^ uVar16) - uVar16)) ||
           (uVar22 = (int)local_9c._Myptr - tVar24.y, uVar16 = (int)uVar22 >> 0x1f,
           2 < (int)((uVar22 ^ uVar16) - uVar16))) {
          local_24 = (vector<GameObject_*,std::allocator<GameObject_*>_> *)spriteZ;
          spriteZ = spriteZ + 0.005;
          Graphic_Line(DisplayInterface::currentBuffer,tVar24.x,tVar24.y,local_9c._padding_,
                       (long)local_9c._Myptr,DisplayInterface::colorWhite,TRANSPARENT_PIXELS);
          spriteZ = (float)local_24;
        }
      }
      iVar11 = local_c;
      pRVar9 = local_1c._Myptr;
      fVar20 = (float)local_1c._padding_;
      if (local_3c == this->userObj) {
        iVar21 = 0x250004;
        fVar15 = (float)local_1c._padding_;
        pRVar29 = local_1c._Myptr;
        _ftol2_sse();
        iVar11 = RADAR_PING[extraout_EAX].index;
LAB_004c1232:
        DrawSprite(DisplayInterface::currentBuffer,iVar11,(int)fVar15,(int)pRVar29,iVar21);
      }
      else {
        if (-1 < local_c) {
          if ((int)local_d0[local_c] < local_1c._padding_) {
            local_d0[local_c] = (float)local_1c._padding_;
          }
          local_24 = (vector<GameObject_*,std::allocator<GameObject_*>_> *)stateColor[iVar11];
          pRVar9 = local_1c._Myptr;
          local_30 = spriteZ;
          spriteZ = spriteZ + 0.005;
          Graphic_Line(DisplayInterface::currentBuffer,(long)fVar20,CONNECTOR_POS.y,(long)fVar20,
                       (long)local_1c._Myptr,(long)local_24,SOLID_PIXELS);
          spriteZ = local_30;
          if ((int)local_14 < 0) {
            if ((int)local_20 < 0) goto LAB_004c14a7;
            iVar11 = UNIT_TYPE_INFO[(int)local_20].index;
          }
          else {
            iVar11 = RADAR_NUMBER[local_14].index;
          }
          iVar21 = 0x250005;
          Foreground_Color = (long)local_24;
          fVar15 = fVar20;
          pRVar29 = pRVar9;
          goto LAB_004c1232;
        }
        if (local_f == false) {
          if ((_S2 & 1) == 0) {
            _S2 = _S2 | 1;
            fVar23 = (float10)fcos((float10)0.05000000074505806);
            scaleCos = (float)(fVar23 * (float10)0.925);
          }
          if ((_S2 & 2) == 0) {
            _S2 = _S2 | 2;
            fVar23 = (float10)fsin((float10)0.05000000074505806);
            scaleSin = (float)(fVar23 * (float10)0.925);
          }
          local_30 = local_78.x * scaleCos;
          local_24 = (vector<GameObject_*,std::allocator<GameObject_*>_> *)(local_78.z * scaleSin);
          local_f4.x = local_30 - (float)local_24;
          local_f4.y = local_78.y;
          local_20 = (GameObject *)(local_78.z * scaleCos);
          local_2c = scaleSin * local_78.x;
          local_f4.z = local_2c + (float)local_20;
          pVVar14 = Vector_Unrotate(&local_1a8,&local_f4,&this->mat);
          local_154 = pVVar14->x;
          fStack_150 = pVVar14->y;
          fStack_14c = pVVar14->z;
          local_48 = (_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>)
                     ConvertPos((VECTOR_3D *)this->range,unaff_EDI);
          local_100.x = (float)local_24 + local_30;
          local_100.y = local_78.y;
          local_100.z = (float)local_20 - local_2c;
          pVVar14 = Vector_Unrotate(&local_184,&local_100,&this->mat);
          local_13c = pVVar14->x;
          fStack_138 = pVVar14->y;
          fStack_134 = pVVar14->z;
          tVar24 = ConvertPos((VECTOR_3D *)this->range,unaff_EDI);
          Graphic_Line(DisplayInterface::currentBuffer,local_1c._padding_,(long)local_1c._Myptr,
                       local_48._padding_,(long)local_48._Myptr,local_34,SOLID_PIXELS);
          Graphic_Line(DisplayInterface::currentBuffer,local_1c._padding_,(long)local_1c._Myptr,
                       tVar24.x,tVar24.y,local_34,SOLID_PIXELS);
          fVar20 = (float)local_1c._padding_;
          pRVar9 = local_1c._Myptr;
        }
        else if ((local_5 == '\0') || (0x2b < (int)local_2c - 1U)) {
          if ((local_3d == '\0') && ((local_26 != '\0' || (local_25 != '\0')))) {
            puVar28 = (undefined1 *)((int)&(local_1c._Myptr)->obj + 1);
            iVar11 = local_1c._padding_ + 1;
            puVar27 = (undefined1 *)((int)&local_1c._Myptr[-1].z + 3);
            iVar21 = local_1c._padding_ + -1;
          }
          else {
            puVar28 = (undefined1 *)((int)&(local_1c._Myptr)->obj + 2);
            iVar11 = local_1c._padding_ + 2;
            puVar27 = (undefined1 *)((int)&local_1c._Myptr[-1].z + 2);
            iVar21 = local_1c._padding_ + -2;
          }
          Graphic_Rect_Filled(DisplayInterface::currentBuffer,iVar21,(long)puVar27,iVar11,
                              (long)puVar28,local_34,SOLID_PIXELS);
        }
        else {
          local_14 = 0;
          fVar15 = local_2c;
          do {
            if ((*(int *)((int)&UNIT_TYPE_INFO[0].minSlot + local_14) <= (int)fVar15) &&
               ((int)fVar15 <= *(int *)((int)&UNIT_TYPE_INFO[0].maxSlot + local_14))) {
              if (local_d == '\0') {
                if ((int)local_60 < 0) {
                  cVar7 = (**(code **)(local_3c->_padding_ + 0x38))();
                  if ((cVar7 != '\0') && (local_3c->isCargo == false)) {
                    iVar11 = 3;
                    goto LAB_004c1414;
                  }
                }
                iVar11 = 5;
              }
              else {
                iVar11 = 0;
              }
LAB_004c1414:
              Foreground_Color = stateColor[iVar11];
              DrawSprite(DisplayInterface::currentBuffer,
                         *(int *)((int)&UNIT_TYPE_INFO[0].index + local_14),(int)fVar20,(int)pRVar9,
                         0x250005);
              fVar15 = local_2c;
            }
            local_14 = local_14 + 0x10;
          } while (local_14 < 0x80);
        }
      }
LAB_004c14a7:
      if ((local_35 != '\0') || (local_e != '\0')) {
        Graphic_Diamond(DisplayInterface::currentBuffer,(long)fVar20,(long)pRVar9,6,local_34,
                        ONE_THIRD_TRANSLUCENT_PIXELS);
      }
    }
    iVar21 = 0;
    iVar11 = CONNECTOR_POS.x;
    do {
      iVar1 = *(int *)((int)local_d0 + iVar21);
      if (iVar11 < iVar1) {
        Clipped_Line(DisplayInterface::currentBuffer,iVar11,CONNECTOR_POS.y,iVar1,CONNECTOR_POS.y,
                     *(long *)((int)stateColor + iVar21),SOLID_PIXELS);
        iVar11 = iVar1;
      }
      iVar21 = iVar21 + 4;
    } while (iVar21 < 0x18);
    iVar21 = 0;
    iVar11 = CONNECTOR_POS.y;
    do {
      iVar1 = *(int *)((int)local_b4 + iVar21);
      if (iVar1 < iVar11) {
        Clipped_Line(DisplayInterface::currentBuffer,CONNECTOR_POS.x,iVar1,CONNECTOR_POS.x,iVar11,
                     *(long *)((int)stateColor + iVar21),SOLID_PIXELS);
        iVar11 = iVar1;
      }
      iVar21 = iVar21 + 4;
    } while (iVar21 < 0x18);
  }
  return;
}
