/*
 * Entry: 004d2395
 * Name: MapRadar::Render
 * Namespace: MapRadar
 * Signature: void Render(MapRadar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapRadar::Render(MapRadar *this)

{
  tagRECT *ptVar1;
  _OBJ76 *p_Var2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  tagPOINT tVar6;
  tagPOINT tVar7;
  VECTOR_3D VVar8;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar9;
  GameObject *pGVar10;
  bool bVar11;
  char cVar12;
  int iVar13;
  long extraout_EAX;
  long extraout_EAX_00;
  VECTOR_3D *pVVar14;
  GameObject **ppGVar15;
  float *pfVar16;
  int iVar17;
  float fVar18;
  long *plVar19;
  MAT_3D *pMVar20;
  float fVar21;
  long lVar22;
  int *piVar23;
  VECTOR_2D VVar24;
  tagPOINT tVar25;
  double dVar26;
  int iVar27;
  long lVar28;
  long lVar29;
  int iVar30;
  VECTOR_3D local_e8;
  undefined1 local_dc [12];
  float local_d0;
  double local_cc;
  int local_c4;
  int local_c0;
  vector<GameObject_*,std::allocator<GameObject_*>_> *local_bc;
  float local_b8;
  GameObject *local_b4;
  double local_b0;
  long local_a8;
  VECTOR_3D local_a4;
  float local_98;
  float local_94;
  undefined4 local_90;
  float local_8c [2];
  long local_84;
  float local_80;
  float local_7c;
  long local_78;
  GameObject *local_74;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_70;
  long local_68;
  long local_64;
  int local_60;
  long local_5c;
  long local_58;
  long local_54;
  long local_50;
  long local_4c;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_48;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  long local_2c;
  long local_28;
  MAT_3D *local_24;
  MAT_3D *local_20;
  VECTOR_3D *local_1c;
  char local_15;
  GameObject *local_14;
  char local_d;
  float local_c;
  char local_8;
  char local_7;
  char local_6;
  char local_5;
  
  if (((useDisplayInterface != 0) && (hudFlags == 0)) &&
     (local_74 = GameObject::userObject, GameObject::userObject != (GameObject *)0x0)) {
    local_a8 = GameObject::userTeamNumber;
    local_b4 = GameObject::GetObj(GameObject::userObject->targetHandle);
    ptVar1 = &this->viewRect;
    ptVar1->left = 10;
    lVar22 = Device.Viewport.Height;
    iVar13 = Device.Viewport.Height + -10;
    (this->viewRect).bottom = iVar13;
    (this->viewRect).top = lVar22 + -0x8b;
    (this->viewRect).right = 0x89;
    _ftol2_sse();
    (this->screenConst).x = extraout_EAX;
    local_24 = (MAT_3D *)(lVar22 + -0x8a + iVar13);
    _ftol2_sse();
    (this->screenConst).y = extraout_EAX_00;
    local_34 = spriteZ;
    spriteZ = spriteZ + 0.01;
    tVar25.y = DisplayInterface::mousePos.y;
    tVar25.x = DisplayInterface::mousePos.x;
    iVar13 = InsideRect(tVar25,ptVar1);
    if ((iVar13 != 0) &&
       (DisplayInterface::cursorIndex = CURSOR.index, command_controls.cmd_hold[0] != '\0')) {
      tVar6.y = DisplayInterface::mousePos.x;
      tVar6.x = (long)&local_b0;
      VVar24 = MapToWorld(this,tVar6);
      OverView::SetPosition((OverView *)&overView,*(VECTOR_2D *)VVar24.x);
      command_controls.cmd_hold[0] = '\0';
    }
    iVar13 = (this->viewRect).top;
    Clipped_Rect_Filled(DisplayInterface::currentBuffer,ptVar1->left + -2,iVar13 + -2,
                        (this->viewRect).right + 2,iVar13 + -1,DisplayInterface::colorBlack,
                        SOLID_PIXELS);
    Clipped_Rect_Filled(DisplayInterface::currentBuffer,ptVar1->left + -2,(this->viewRect).top,
                        ptVar1->left + -1,(this->viewRect).bottom,DisplayInterface::colorBlack,
                        SOLID_PIXELS);
    iVar13 = (this->viewRect).right;
    Clipped_Rect_Filled(DisplayInterface::currentBuffer,iVar13 + 1,(this->viewRect).top,iVar13 + 2,
                        (this->viewRect).bottom,DisplayInterface::colorBlack,SOLID_PIXELS);
    Clipped_Rect_Filled(DisplayInterface::currentBuffer,ptVar1->left + -2,(this->viewRect).top + -1,
                        (this->viewRect).right + 2,(this->viewRect).bottom,
                        DisplayInterface::colorBlack,SOLID_PIXELS);
    D3IniFlags = D3IniFlags | 0x800;
    DrawSprite(DisplayInterface::currentBuffer,this->mapIndex,ptVar1->left,(this->viewRect).top,0);
    D3IniFlags = D3IniFlags & 0xfffff7ff;
    if (View_Record.Current_View == OVER_VIEW) {
      local_40 = (float)DisplayInterface::currentCamera->View_Pyramid[0].x;
      local_30 = 5.60519e-45;
      local_3c = (float)DisplayInterface::currentCamera->View_Pyramid[0].y;
      local_38 = (float)DisplayInterface::currentCamera->View_Pyramid[0].z;
      local_98 = 1.0 / DisplayInterface::currentCamera->Const_x;
      local_a4.x = (DisplayInterface::currentCamera->Left - DisplayInterface::currentCamera->Orig_x)
                   * local_98;
      local_8c[1] = 1.0 / DisplayInterface::currentCamera->Const_y;
      local_a4.y = (DisplayInterface::currentCamera->Bottom -
                   DisplayInterface::currentCamera->Orig_y) * local_8c[1];
      local_a4.z = 1.0;
      local_20 = &DisplayInterface::currentCamera->Matrix;
      local_98 = (DisplayInterface::currentCamera->Right - DisplayInterface::currentCamera->Orig_x)
                 * local_98;
      local_90 = 0x3f800000;
      local_24 = (MAT_3D *)&local_68;
      local_1c = &local_a4;
      local_8c[1] = (DisplayInterface::currentCamera->Top - DisplayInterface::currentCamera->Orig_y)
                    * local_8c[1];
      local_84 = 0x3f800000;
      local_78 = 0x3f800000;
      local_c = local_3c - overView.viewCenter.y;
      local_94 = local_a4.y;
      local_8c[0] = local_98;
      local_80 = local_a4.x;
      local_7c = local_8c[1];
      do {
        pVVar14 = Vector_Unrotate(&local_e8,local_1c,local_20);
        local_d0 = pVVar14->x;
        local_cc = *(double *)&pVVar14->y;
        VVar3.y = local_3c;
        VVar3.x = local_40;
        VVar3.z = local_38;
        pVVar14 = AddMultVectors((VECTOR_3D *)local_dc,VVar3,-(local_c / pVVar14->y),*pVVar14);
        VVar4.y = pVVar14->x;
        VVar4.x = (float)&local_b0;
        VVar4.z = pVVar14->y;
        tVar25 = WorldToMap(this,VVar4);
        lVar22 = ((long *)tVar25.x)[1];
        local_1c = local_1c + 1;
        *(long *)local_24 = *(long *)tVar25.x;
        *(long *)((int)local_24 + 4) = lVar22;
        local_24 = (MAT_3D *)((int)local_24 + 8);
        local_30 = (float)((int)local_30 + -1);
      } while (local_30 != 0.0);
      spriteZ = local_34 + 0.005;
      Graphic_Line(DisplayInterface::currentBuffer,local_68,local_64,local_60,local_5c,
                   DisplayInterface::colorWhite,SOLID_PIXELS);
      Graphic_Line(DisplayInterface::currentBuffer,local_60,local_5c,local_58,local_54,
                   DisplayInterface::colorWhite,SOLID_PIXELS);
      Graphic_Line(DisplayInterface::currentBuffer,local_58,local_54,local_50,local_4c,
                   DisplayInterface::colorWhite,SOLID_PIXELS);
      Graphic_Line(DisplayInterface::currentBuffer,local_50,local_4c,local_68,local_64,
                   DisplayInterface::colorWhite,SOLID_PIXELS);
    }
    local_24 = (MAT_3D *)controlPanel.currentItem;
    spriteZ = local_34;
    local_60 = -1;
    local_5c = 0xffffffff;
    local_58 = 0xffffffff;
    local_54 = 0xffffffff;
    local_50 = 0xffffffff;
    local_4c = 0xffffffff;
    local_8c[0] = (float)CONNECTOR_POS.y;
    local_8c[1] = (float)CONNECTOR_POS.y;
    local_84 = CONNECTOR_POS.y;
    local_80 = (float)CONNECTOR_POS.y;
    local_7c = (float)CONNECTOR_POS.y;
    local_78 = CONNECTOR_POS.y;
    local_b8 = Get_TimeLocal();
    TimeStep();
    pvVar9 = GameObject::objectList;
    local_bc = GameObject::objectList;
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_48,GameObject::objectList->_Myfirst,
               (_Container_base_aux *)GameObject::objectList);
    local_70._padding_ = local_48._padding_;
    local_70._Myptr = local_48._Myptr;
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_48,pvVar9->_Mylast,(_Container_base_aux *)pvVar9);
    bVar11 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                       (&local_70,&local_48);
    lVar22 = CONNECTOR_POS.x;
    while (CONNECTOR_POS.x = lVar22, !bVar11) {
      ppGVar15 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                           (&local_70);
      local_14 = *ppGVar15;
      if (0.0 < local_14->illumination) {
        pfVar16 = (float *)(**(code **)(local_14->_padding_ + 0xc))();
        local_e8.x = *pfVar16;
        local_e8.y = pfVar16[1];
        local_e8.z = pfVar16[2];
        VVar8.y = *pfVar16;
        VVar8.x = (float)&local_2c;
        VVar8.z = pfVar16[1];
        WorldToMap(this,VVar8);
        tVar7.y = local_28;
        tVar7.x = local_2c;
        iVar13 = InsideRect(tVar7,&this->viewRect);
        if (iVar13 != 0) {
          iVar13 = local_14->teamSlot;
          piVar23 = &local_14->_padding_;
          iVar17 = (**(code **)(*piVar23 + 4))();
          local_5 = iVar17 == local_a8;
          local_d = local_14->isObjective;
          local_7 = local_14 == local_b4;
          iVar17 = (**(code **)*piVar23)();
          if (((*(int *)(iVar17 + 0x28) == 5) ||
              (iVar17 = (**(code **)*piVar23)(), *(int *)(iVar17 + 0x28) == 7)) ||
             (iVar17 = (**(code **)*piVar23)(), *(int *)(iVar17 + 0x28) == 3)) {
LAB_004d2883:
            local_15 = '\x01';
          }
          else {
            iVar17 = (**(code **)*piVar23)();
            local_15 = '\0';
            if (*(int *)(iVar17 + 0x28) == 4) goto LAB_004d2883;
          }
          local_30 = local_14->enemyShot;
          if ((local_5 == '\0') || (local_6 = '\x01', local_30 + 2.0 <= local_b8)) {
            local_6 = '\0';
          }
          if ((local_5 == '\0') || (local_8 = '\x01', local_14->isSelected == false)) {
            local_8 = '\0';
          }
          iVar17 = -1;
          local_c = -NAN;
          local_20 = (MAT_3D *)0xffffffff;
          pVVar14 = (VECTOR_3D *)DisplayInterface::colorRed;
          if (local_6 == '\0') {
            local_dc._4_8_ = (undefined8)(local_14->illumination * 15.0 + (float)Float2Int);
            lVar22 = GameObject::GetColor(local_14);
            pVVar14 = (VECTOR_3D *)(uint)DisplayInterface::colorRamp[local_dc._4_4_][lVar22];
          }
          local_1c = pVVar14;
          if (((local_5 != '\0') && (local_14 != local_74)) && (nextBeep < local_30)) {
            StartGASEvent("cgrowl.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
            nextBeep = local_30 + 1.0;
          }
          pGVar10 = local_14;
          if (controlPanel.menuMode == MENU_TYPE_PANEL) {
            if (((local_5 != '\0') && (local_6 != '\0')) && (-1 < iVar13)) {
              pMVar20 = (MAT_3D *)0x0;
              plVar19 = &UNIT_TYPE[0].maxSlot;
              do {
                if ((((<unnamed_type_UNIT_TYPE> *)(plVar19 + -1))->minSlot <= iVar13) &&
                   (iVar13 <= *plVar19)) {
                  lVar22 = MODE_BUTTON_RECT[(int)pMVar20].left;
                  fVar18 = (float)((MODE_BUTTON_RECT[(int)pMVar20].bottom +
                                   MODE_BUTTON_RECT[(int)pMVar20].top) / 2);
                  iVar17 = 0;
                  lVar28 = stateColor[0];
                  local_20 = pMVar20;
                  if ((int)fVar18 < (int)local_8c[0]) {
                    local_8c[0] = fVar18;
                  }
                  goto LAB_004d2c9b;
                }
                pMVar20 = (MAT_3D *)((int)&pMVar20->right_x + 1);
                plVar19 = plVar19 + 4;
              } while (pMVar20 < (MAT_3D *)0x8);
            }
          }
          else if (controlPanel.menuMode == MENU_UNIT_PANEL) {
            if ((((local_5 != '\0') && (-1 < (int)local_24)) && (local_24 < (MAT_3D *)0x8)) &&
               ((UNIT_TYPE[(int)local_24].minSlot <= iVar13 &&
                (iVar13 <= UNIT_TYPE[(int)local_24].maxSlot)))) {
              fVar18 = (float)(iVar13 - UNIT_TYPE[(int)local_24].minSlot);
              local_20 = local_24;
              if (local_6 == '\0') {
                if (fVar18 == (float)controlPanel.menuItem) {
LAB_004d2b15:
                  local_20 = local_24;
                  iVar17 = 1;
                  local_c = fVar18;
                }
                else {
                  local_c = fVar18;
                  if (local_8 == '\0') {
                    cVar12 = (**(code **)(local_14->_padding_ + 0x38))();
                    if ((cVar12 == '\0') || (pGVar10->isCargo != false)) {
                      iVar17 = 5;
                    }
                    else {
                      iVar17 = 3;
                    }
                  }
                  else {
                    iVar17 = 2;
                  }
                }
              }
              else {
LAB_004d2b09:
                local_20 = local_24;
                iVar17 = 0;
                local_c = fVar18;
              }
LAB_004d2a78:
              lVar22 = MODE_BUTTON_RECT[(int)fVar18].left;
              fVar18 = (float)((MODE_BUTTON_RECT[(int)fVar18].bottom +
                               MODE_BUTTON_RECT[(int)fVar18].top) / 2);
              if ((int)fVar18 < (int)local_8c[iVar17]) {
                local_8c[iVar17] = fVar18;
              }
              Graphic_Line(DisplayInterface::currentBuffer,lVar22,(long)fVar18,CONNECTOR_POS.x,
                           (long)fVar18,stateColor[iVar17],SOLID_PIXELS);
            }
          }
          else if (controlPanel.menuMode == MENU_MODE_PANEL) {
            if ((((local_5 != '\0') && (-1 < (int)local_24)) && (local_24 < (MAT_3D *)0x8)) &&
               ((UNIT_TYPE[(int)local_24].minSlot <= iVar13 &&
                (iVar13 <= UNIT_TYPE[(int)local_24].maxSlot)))) {
              local_c = (float)(iVar13 - UNIT_TYPE[(int)local_24].minSlot);
              local_20 = local_24;
              if (local_6 == '\0') {
                if (local_8 == '\0') goto LAB_004d2cb2;
                iVar17 = 2;
              }
              else {
                iVar17 = 0;
              }
              lVar22 = 10;
              fVar18 = 1.96182e-44;
              if (0xe < (int)local_8c[iVar17]) {
                local_8c[iVar17] = 1.96182e-44;
              }
              lVar28 = stateColor[iVar17];
LAB_004d2c9b:
              Clipped_Line(DisplayInterface::currentBuffer,lVar22,(long)fVar18,CONNECTOR_POS.x,
                           (long)fVar18,lVar28,SOLID_PIXELS);
            }
          }
          else if (controlPanel.menuMode == MENU_NAV_PANEL) {
            if (((local_5 != '\0') && (-1 < (int)local_24)) &&
               ((local_24 < (MAT_3D *)0x8 &&
                ((UNIT_TYPE[(int)local_24].minSlot <= iVar13 &&
                 (iVar13 <= UNIT_TYPE[(int)local_24].maxSlot)))))) {
              fVar18 = (float)(iVar13 - UNIT_TYPE[(int)local_24].minSlot);
              local_20 = local_24;
              if (local_6 != '\0') goto LAB_004d2b09;
              if (fVar18 == (float)controlPanel.menuItem) goto LAB_004d2b15;
              iVar17 = (local_7 == '\0') + 2;
              local_c = fVar18;
              goto LAB_004d2a78;
            }
          }
          else if (controlPanel.menuMode == MENU_TARGET_PANEL) {
            if (local_5 == '\0') {
              iVar13 = GameObject::GetHandle(local_14);
              fVar18 = 0.0;
              if (0 < controlPanel.targetNum) {
                do {
                  if (controlPanel.targetList[(int)fVar18] == iVar13) {
                    local_c = fVar18;
                    if (-1 < (int)fVar18) {
                      if (fVar18 == (float)controlPanel.menuItem) {
                        iVar17 = 1;
                      }
                      else {
                        iVar17 = (uint)(local_7 == '\0') * 2 + 2;
                      }
                      lVar22 = MODE_BUTTON_RECT[(int)fVar18].left;
                      fVar18 = (float)((MODE_BUTTON_RECT[(int)fVar18].bottom +
                                       MODE_BUTTON_RECT[(int)fVar18].top) / 2);
                      if ((int)fVar18 < (int)local_8c[iVar17]) {
                        local_8c[iVar17] = fVar18;
                      }
                      Graphic_Line(DisplayInterface::currentBuffer,lVar22,(long)fVar18,
                                   CONNECTOR_POS.x,(long)fVar18,stateColor[iVar17],SOLID_PIXELS);
                      goto LAB_004d2a1e;
                    }
                    break;
                  }
                  fVar18 = (float)((int)fVar18 + 1);
                } while ((int)fVar18 < controlPanel.targetNum);
              }
            }
            else {
LAB_004d2a28:
              iVar13 = GameObject::GetHandle(local_14);
              fVar21 = 0.0;
              fVar18 = local_c;
              if (0 < controlPanel.targetNum) {
                do {
                  fVar18 = fVar21;
                  if (controlPanel.targetList[(int)fVar21] == iVar13) break;
                  fVar21 = (float)((int)fVar21 + 1);
                  fVar18 = local_c;
                } while ((int)fVar21 < controlPanel.targetNum);
              }
              local_c = fVar18;
              if (-1 < (int)local_c) {
                fVar18 = local_c;
                if (local_c == (float)controlPanel.menuItem) {
                  iVar17 = 1;
                }
                else {
                  iVar17 = (local_7 == '\0') + 2;
                }
                goto LAB_004d2a78;
              }
            }
          }
          else if (controlPanel.menuMode == MENU_DEFENSE_PANEL) {
LAB_004d2a1e:
            if (local_5 != '\0') goto LAB_004d2a28;
          }
LAB_004d2cb2:
          lVar28 = local_28;
          lVar22 = local_2c;
          if (local_14 == local_74) {
            Graphic_Rect_Filled(DisplayInterface::currentBuffer,local_2c + -1,local_28 + -1,
                                local_2c + 1,local_28 + 1,(long)local_1c,SOLID_PIXELS);
            p_Var2 = local_14->obj;
            local_40 = (p_Var2->transform).front_x;
            local_3c = (p_Var2->transform).front_y;
            local_38 = (p_Var2->transform).front_z;
            dVar26 = rsqrt((double)(local_40 * local_40 + local_38 * local_38));
            local_b0 = (double)local_40 * dVar26 * 10.0 + Float2Int;
            local_cc = Float2Int + (double)local_38 * dVar26 * 10.0;
            VVar5.y = local_e8.x;
            VVar5.x = (float)&local_c4;
            VVar5.z = local_e8.y;
            WorldToMap(this,VVar5);
            Graphic_Line(DisplayInterface::currentBuffer,local_b0._0_4_ + local_c4,
                         local_c0 - local_cc._0_4_,local_c4,local_c0,DisplayInterface::colorWhite,
                         SOLID_PIXELS);
          }
          else {
            if (iVar17 < 0) {
              iVar13 = local_2c;
              iVar17 = local_28;
              iVar27 = local_2c;
              iVar30 = local_28;
              if (local_15 == '\0') {
                iVar13 = local_2c + -1;
                iVar17 = local_28 + -1;
                iVar27 = local_2c + 1;
                iVar30 = local_28 + 1;
              }
              Graphic_Rect_Filled(DisplayInterface::currentBuffer,iVar13,iVar17,iVar27,iVar30,
                                  (long)local_1c,SOLID_PIXELS);
              if ((local_d == '\0') && (local_7 == '\0')) goto LAB_004d2e7c;
              lVar29 = 3;
            }
            else {
              if ((&local_60)[iVar17] < local_2c) {
                (&local_60)[iVar17] = local_2c;
              }
              lVar28 = stateColor[iVar17];
              spriteZ = local_34 + 0.005;
              Graphic_Line(DisplayInterface::currentBuffer,local_2c,CONNECTOR_POS.y,local_2c,
                           local_28,lVar28,SOLID_PIXELS);
              spriteZ = local_34;
              if ((int)local_c < 0) {
                if (-1 < (int)local_20) {
                  iVar13 = UNIT_TYPE[(int)local_20].index;
                  goto LAB_004d2df8;
                }
              }
              else {
                iVar13 = MAP_NUMBER[(int)local_c].index;
LAB_004d2df8:
                Foreground_Color = lVar28;
                DrawSprite(DisplayInterface::currentBuffer,iVar13,lVar22,local_28,0x250005);
              }
              if ((local_d == '\0') && (local_7 == '\0')) goto LAB_004d2e7c;
              lVar29 = 6;
              lVar28 = local_28;
            }
            Graphic_Diamond(DisplayInterface::currentBuffer,lVar22,lVar28,lVar29,(long)local_1c,
                            ONE_THIRD_TRANSLUCENT_PIXELS);
          }
        }
      }
LAB_004d2e7c:
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_70)
      ;
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_48,local_bc->_Mylast,(_Container_base_aux *)local_bc);
      bVar11 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                         (&local_70,&local_48);
      lVar22 = CONNECTOR_POS.x;
    }
    iVar13 = 0;
    do {
      iVar17 = *(int *)((int)&local_60 + iVar13);
      if (lVar22 < iVar17) {
        Clipped_Line(DisplayInterface::currentBuffer,lVar22,CONNECTOR_POS.y,iVar17,CONNECTOR_POS.y,
                     *(long *)((int)stateColor + iVar13),SOLID_PIXELS);
        lVar22 = iVar17;
      }
      iVar13 = iVar13 + 4;
    } while (iVar13 < 0x18);
    iVar17 = 0;
    iVar13 = CONNECTOR_POS.y;
    do {
      iVar27 = *(int *)((int)local_8c + iVar17);
      if (iVar27 < iVar13) {
        Clipped_Line(DisplayInterface::currentBuffer,CONNECTOR_POS.x,iVar27,CONNECTOR_POS.x,iVar13,
                     *(long *)((int)stateColor + iVar17),SOLID_PIXELS);
        iVar13 = iVar27;
      }
      iVar17 = iVar17 + 4;
    } while (iVar17 < 0x18);
  }
  return;
}
