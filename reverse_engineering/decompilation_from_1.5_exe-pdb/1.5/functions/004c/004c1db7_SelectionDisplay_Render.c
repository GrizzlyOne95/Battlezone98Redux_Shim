/*
 * Entry: 004c1db7
 * Name: SelectionDisplay::Render
 * Namespace: SelectionDisplay
 * Signature: void Render(SelectionDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall SelectionDisplay::Render(SelectionDisplay *this)

{
  GameObject *pGVar1;
  _OBJ76 *p_Var2;
  Carrier *this_00;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  PANE *pPVar8;
  _GRAPHIC_BUFFER *p_Var9;
  SelectionDisplay *pSVar10;
  bool bVar11;
  GameObject **ppGVar12;
  float *pfVar13;
  int iVar14;
  SPHERE *pSVar15;
  VECTOR_3D *pVVar16;
  undefined4 extraout_EAX;
  Weapon *pWVar17;
  uint uVar18;
  int iVar19;
  long lVar20;
  int iVar21;
  int *piVar22;
  float10 fVar23;
  tagPOINT tVar24;
  tagPOINT tVar25;
  float fVar26;
  char *pcVar27;
  float fVar28;
  VECTOR_3D local_140;
  VECTOR_3D local_134;
  float local_128;
  float fStack_124;
  float fStack_120;
  VECTOR_3D local_11c;
  VECTOR_3D local_110;
  VECTOR_3D local_104;
  PANE local_f8;
  long local_e8 [2];
  long local_e0;
  double local_dc;
  long local_d4 [2];
  int local_cc;
  double local_c8;
  double local_c0;
  VECTOR_3D local_b8;
  int local_ac;
  int local_a8;
  float local_a4;
  GameObject *local_a0;
  int local_9c;
  int local_98;
  int local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  float local_74;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_70;
  uint local_68;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_64;
  int local_58;
  GameObject *local_54;
  tagPOINT local_50;
  float local_48;
  GameObject *local_44;
  SelectionDisplay *local_40;
  long local_3c;
  char local_35;
  int local_34;
  float local_30;
  long local_28;
  char *local_24;
  float local_20;
  char local_1c;
  char local_1b;
  char local_1a;
  char local_19;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&local_7c;
  local_54 = GameObject::userObject;
  if (GameObject::userObject != (GameObject *)0x0) {
    local_40 = this;
    local_a0 = GameObject::GetObj(GameObject::userObject->targetHandle);
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_64,GameObject::objectList->_Myfirst,
               (_Container_base_aux *)GameObject::objectList);
    local_70._padding_ = local_64._padding_;
    local_70._Myptr = local_64._Myptr;
    while( true ) {
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_64,GameObject::objectList->_Mylast,
                 (_Container_base_aux *)GameObject::objectList);
      bVar11 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                         (&local_70,&local_64);
      if (bVar11) break;
      ppGVar12 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                           (&local_70);
      pGVar1 = *ppGVar12;
      local_44 = pGVar1;
      if ((pGVar1 != local_54) || (View_Record.Current_View == OVER_VIEW)) {
        bVar11 = GameObject::FriendP(local_54,pGVar1);
        if ((!bVar11) || (local_1a = '\x01', pGVar1->isSelected == false)) {
          local_1a = '\0';
        }
        local_1b = pGVar1->isObjective;
        local_48 = pGVar1->playerShot;
        local_19 = pGVar1 == local_a0;
        fVar26 = Get_TimeLocal();
        local_1c = fVar26 < local_48 + 2.0;
        local_34 = local_44->nameIndex;
        local_24 = local_44->name;
        pfVar13 = (float *)(**(code **)(local_44->_padding_ + 0xc))();
        local_b8.x = *pfVar13;
        local_b8.y = pfVar13[1];
        local_b8.z = pfVar13[2];
        local_50 = WorldToScreen(&local_b8,DisplayInterface::currentCamera,&local_74);
        local_28 = local_50.y;
        iVar19 = local_50.x;
        local_3c = GameObject::GetColor(local_44);
        pGVar1 = local_44;
        local_30 = (float)local_40->colorMap[local_3c];
        iVar14 = (DisplayInterface::currentBuffer->Pane).x1;
        local_20 = 0.0;
        local_58 = ((DisplayInterface::currentBuffer->Pane).y0 + 1 +
                   (DisplayInterface::currentBuffer->Pane).y1) / 2;
        iVar21 = ((DisplayInterface::currentBuffer->Pane).x0 + 1 + iVar14) / 2;
        uVar18 = iVar21 - iVar19 >> 0x1f;
        local_48 = (float)((iVar21 - iVar19 ^ uVar18) - uVar18);
        iVar14 = (iVar14 - (DisplayInterface::currentBuffer->Pane).x0) + 1;
        if (((int)(iVar14 + (iVar14 >> 0x1f & 7U)) >> 3 <= (int)local_48) ||
           (local_35 = '\x01', uVar18 = local_58 - local_50.y >> 0x1f,
           iVar14 = ((DisplayInterface::currentBuffer->Pane).y1 -
                    (DisplayInterface::currentBuffer->Pane).y0) + 1,
           (int)(iVar14 + (iVar14 >> 0x1f & 3U)) >> 2 <=
           (int)((local_58 - local_50.y ^ uVar18) - uVar18))) {
          local_35 = '\0';
        }
        if ((((local_1b == '\0') && (local_19 == '\0')) && (local_1a == '\0')) && (local_1c == '\0')
           ) {
          if (((local_74 < 0.0) || (local_50.x < (DisplayInterface::currentBuffer->Pane).x0)) ||
             (((DisplayInterface::currentBuffer->Pane).x1 < local_50.x ||
              ((local_50.y < (DisplayInterface::currentBuffer->Pane).y0 ||
               ((DisplayInterface::currentBuffer->Pane).y1 < local_50.y)))))) {
            local_20 = 1.4013e-45;
          }
        }
        else {
          if (local_50.y < (DisplayInterface::currentBuffer->Pane).y0) {
            iVar19 = ((local_50.x - iVar21) * local_58) / (local_58 - local_50.y);
            local_20 = 2.8026e-45;
            local_28 = (DisplayInterface::currentBuffer->Pane).y0;
LAB_004c1ff8:
            iVar19 = iVar19 + iVar21;
          }
          else if ((DisplayInterface::currentBuffer->Pane).y1 < local_50.y) {
            iVar19 = ((local_50.x - iVar21) * local_58) / (local_50.y - local_58);
            local_20 = 4.2039e-45;
            local_28 = (DisplayInterface::currentBuffer->Pane).y1;
            goto LAB_004c1ff8;
          }
          iVar14 = (DisplayInterface::currentBuffer->Pane).x0;
          if (iVar19 < iVar14) {
            local_20 = 5.60519e-45;
            iVar21 = ((local_28 - local_58) * iVar21) / (iVar21 - iVar19);
            iVar19 = iVar14;
          }
          else {
            iVar14 = (DisplayInterface::currentBuffer->Pane).x1;
            if (iVar19 <= iVar14) goto LAB_004c203f;
            local_20 = 7.00649e-45;
            iVar21 = ((local_28 - local_58) * iVar21) / (iVar19 - iVar21);
            iVar19 = iVar14;
          }
          local_28 = iVar21 + local_58;
        }
LAB_004c203f:
        lVar20 = local_28;
        if (local_20 == 0.0) {
          pSVar15 = GameObject::GetSphere(local_44);
          local_20 = pSVar15->radius;
          local_c0 = (double)(local_20 * local_74 + (float)Float2Int);
          if ((View_Record.Current_View == OVER_VIEW) && (0.0 < pGVar1->illumination)) {
            local_c8 = (double)(pGVar1->illumination * 15.0 + (float)Float2Int);
            local_68 = (uint)DisplayInterface::colorRamp[local_c8._0_4_][local_3c];
            local_48 = (float)((local_c0._0_4_ >> 1) + 2);
            if (0x17 < (int)local_48) {
              local_48 = 3.36312e-44;
            }
            p_Var2 = local_44->obj;
            local_128 = (p_Var2->transform).front_x;
            fStack_124 = (p_Var2->transform).front_y;
            fStack_120 = (p_Var2->transform).front_z;
            VVar7.x = (p_Var2->transform).front_x;
            VVar7.y = (p_Var2->transform).front_y;
            VVar7.z = (p_Var2->transform).front_z;
            VVar3.y = local_b8.y;
            VVar3.x = local_b8.x;
            VVar3.z = local_b8.z;
            pVVar16 = AddMultVectors(&local_140,VVar3,local_20,VVar7);
            local_104.x = pVVar16->x;
            local_104.y = pVVar16->y;
            local_104.z = pVVar16->z;
            VVar4.y = local_b8.y;
            VVar4.x = local_b8.x;
            VVar4.z = local_b8.z;
            VVar5.y = fStack_124;
            VVar5.x = local_128;
            VVar5.z = fStack_120;
            pVVar16 = AddMultVectors(&local_134,VVar4,local_20 + 5.0,VVar5);
            local_11c.x = pVVar16->x;
            local_11c.y = pVVar16->y;
            local_11c.z = pVVar16->z;
            tVar24 = WorldToScreen(&local_104,DisplayInterface::currentCamera,(float *)0x0);
            local_e0 = tVar24.y;
            tVar25 = WorldToScreen(&local_11c,DisplayInterface::currentCamera,(float *)0x0);
            local_20 = spriteZ;
            spriteZ = spriteZ + 1.0;
            Graphic_Line(DisplayInterface::currentBuffer,tVar24.x,local_e0,tVar25.x,tVar25.y,
                         local_68,SOLID_PIXELS);
            Graphic_Circle(DisplayInterface::currentBuffer,iVar19,local_28,local_c0._0_4_,
                           (long)local_48,local_68,SOLID_PIXELS);
            spriteZ = local_20;
          }
          lVar20 = local_3c;
          if ((((local_19 != '\0') || (local_1b != '\0')) || (local_1a != '\0')) ||
             (local_1c != '\0')) {
            Font_Set_Foreground(Default_Font,local_3c);
            pSVar10 = local_40;
            Foreground_Color = lVar20;
            if (local_1a != '\0') {
              DrawSprite(DisplayInterface::currentBuffer,local_40->selectIndex + (int)local_30,
                         iVar19,local_28,0x250004);
            }
            if ((local_19 != '\0') || (local_1c != '\0')) {
              DrawSprite(DisplayInterface::currentBuffer,pSVar10->targetIndex + (int)local_30,iVar19
                         ,local_28,0x250004);
            }
            if (local_1b != '\0') {
              DrawSprite(DisplayInterface::currentBuffer,pSVar10->objectIndex + (int)local_30,iVar19
                         ,local_28,0x250004);
            }
            iVar14 = 0;
            if (((local_19 == '\0') && (local_1a == '\0')) && (local_1b == '\0')) {
LAB_004c2536:
              if (local_1c != '\0') goto LAB_004c253c;
            }
            else {
              if (local_34 == 0) {
                if (local_24 != (char *)0x0) {
                  Font_Get_String_Dimensions(Default_Font,local_24,&local_84,&local_78);
                  Font_Print_String(Default_Font,DisplayInterface::currentBuffer,
                                    iVar19 - local_84 / 2,(local_28 - local_78) + -0x25,local_24);
                  iVar14 = local_78;
                }
              }
              else {
                DrawSprite(DisplayInterface::currentBuffer,local_34,iVar19,local_28 + -0x25,0x290005
                          );
                iVar14 = GetSpriteHeight(local_34);
              }
              if (((local_19 == '\0') && (local_1a == '\0')) && (local_1b == '\0'))
              goto LAB_004c2536;
LAB_004c253c:
              bVar11 = Net::IsNetGame();
              if (bVar11) {
                piVar22 = &local_44->_padding_;
                iVar21 = (**(code **)(*piVar22 + 4))();
                if (0 < iVar21) {
                  iVar21 = (**(code **)(*piVar22 + 4))();
                  if (NetPlayer::netPlayerByTeam[iVar21] != (NetPlayer *)0x0) {
                    pcVar27 = NetPlayer::netPlayerByTeam[iVar21]->playerName;
                    Font_Get_String_Dimensions(Default_Font,pcVar27,&local_90,&local_ac);
                    Font_Print_String(Default_Font,DisplayInterface::currentBuffer,
                                      iVar19 - local_90 / 2,((local_28 - local_ac) - iVar14) + -0x25
                                      ,pcVar27);
                  }
                }
              }
            }
            pVVar16 = (VECTOR_3D *)(**(code **)(local_54->_padding_ + 0xc))();
            VVar6.y = local_b8.y;
            VVar6.x = local_b8.x;
            VVar6.z = local_b8.z;
            Dist3D(*pVVar16,VVar6);
            _ftol2_sse();
            sprintf(local_18,"%dm",extraout_EAX);
            if (((local_1b == '\0') || (local_35 == '\0')) &&
               ((local_19 == '\0' && (local_1a == '\0')))) {
LAB_004c2649:
              if (local_1c == '\0') goto LAB_004c2784;
            }
            else {
              pcVar27 = local_18;
              iVar14 = local_28 + 0x25;
              lVar20 = Font_Get_String_Length(Default_Font,local_18);
              Font_Print_String(Default_Font,DisplayInterface::currentBuffer,
                                (iVar19 - lVar20) + 0x20,iVar14,pcVar27);
              if ((local_19 == '\0') && (local_1a == '\0')) goto LAB_004c2649;
            }
            if (0.0 < local_44->maxHealth) {
              fVar28 = 1.0;
              fVar26 = 0.0;
              fVar23 = (float10)(**(code **)(local_44->_padding_ + 0x1c))();
              local_30 = Clamp((float)fVar23,fVar26,fVar28);
              if (0.25 <= local_30) {
                if (0.5 <= local_30) {
                  local_20 = (float)local_40->gaugeGreen;
                }
                else {
                  local_20 = (float)local_40->gaugeYellow;
                }
              }
              else {
                local_20 = (float)local_40->gaugeRed;
              }
              local_80 = GetSpriteWidth((int)local_20);
              local_7c = GetSpriteHeight((int)local_20);
              local_cc = local_28 - local_7c / 2;
              local_f8.x0 = (DisplayInterface::currentBuffer->Pane).x0;
              local_f8.y0 = (DisplayInterface::currentBuffer->Pane).y0;
              local_f8.x1 = (DisplayInterface::currentBuffer->Pane).x1;
              local_f8.y1 = (DisplayInterface::currentBuffer->Pane).y1;
              iVar14 = (iVar19 - local_80) + -0x25;
              fVar26 = (float)Float2Int;
              (DisplayInterface::currentBuffer->Pane).x0 = iVar14;
              local_dc = (double)((1.0 - local_30) * (float)local_7c + fVar26);
              (DisplayInterface::currentBuffer->Pane).y0 = local_dc._0_4_ + local_cc;
              (DisplayInterface::currentBuffer->Pane).x1 = (iVar19 - local_80) + -0x26 + local_80;
              (DisplayInterface::currentBuffer->Pane).y1 = local_cc + local_7c;
              lVar20 = Clip_Pane(&DisplayInterface::currentBuffer->Pane,&local_f8);
              if (-1 < lVar20) {
                DrawSprite(DisplayInterface::currentBuffer,(int)local_20,
                           iVar14 - (DisplayInterface::currentBuffer->Pane).x0,
                           local_cc - (DisplayInterface::currentBuffer->Pane).y0,0x200004);
              }
              p_Var9 = DisplayInterface::currentBuffer;
              pPVar8 = &DisplayInterface::currentBuffer->Pane;
              (DisplayInterface::currentBuffer->Pane).x0 = local_f8.x0;
              pPVar8->y0 = local_f8.y0;
              (p_Var9->Pane).x1 = local_f8.x1;
              (p_Var9->Pane).y1 = local_f8.y1;
            }
          }
LAB_004c2784:
          if ((((UserProfilePtr->playOption & 0x20) != 0) && (local_19 != '\0')) &&
             (this_00 = local_54->carrier, this_00 != (Carrier *)0x0)) {
            local_48 = (float)this_00->selected;
            local_20 = 0.0;
            do {
              if (((uint)local_48 & 1 << (SUB41(local_20,0) & 0x1f)) != 0) {
                pWVar17 = Carrier::GetWeapon(this_00,(int)local_20);
                (**(code **)(pWVar17->_padding_ + 0x2c))(&local_110,local_44);
                tVar24 = WorldToScreen(&local_110,DisplayInterface::currentCamera,&local_a4);
                if (1.0 < local_a4) {
                  Graphic_Diamond(DisplayInterface::currentBuffer,tVar24.x,tVar24.y,5,local_3c,
                                  SOLID_PIXELS);
                  Graphic_Diamond(DisplayInterface::currentBuffer,tVar24.x,tVar24.y,3,
                                  DisplayInterface::colorWhite,SOLID_PIXELS);
                }
              }
              local_20 = (float)((int)local_20 + 1);
            } while ((int)local_20 < 5);
          }
        }
        else if (local_20 == 2.8026e-45) {
          DrawSprite(DisplayInterface::currentBuffer,local_40->caretIndex[0] + (int)local_30,iVar19,
                     local_28,0x210004);
          if (local_34 == 0) {
            if (local_24 != (char *)0x0) {
              Font_Get_String_Dimensions(Default_Font,local_24,&local_9c,local_e8);
              Font_Set_Foreground(Default_Font,local_3c);
              iVar21 = local_28 + 0x14;
              iVar14 = local_9c;
LAB_004c224b:
              lVar20 = iVar19 - iVar14 / 2;
LAB_004c2252:
              Font_Print_String(Default_Font,DisplayInterface::currentBuffer,lVar20,iVar21,local_24)
              ;
            }
          }
          else {
            iVar21 = 0x210005;
            iVar14 = lVar20 + 0x14;
LAB_004c2095:
            Foreground_Color = local_3c;
            DrawSprite(DisplayInterface::currentBuffer,local_34,iVar19,iVar14,iVar21);
          }
        }
        else if (local_20 == 4.2039e-45) {
          DrawSprite(DisplayInterface::currentBuffer,local_40->caretIndex[3] + (int)local_30,iVar19,
                     local_28,0x290004);
          if (local_34 != 0) {
            iVar21 = 0x290005;
            iVar14 = lVar20 + -0x14;
            goto LAB_004c2095;
          }
          if (local_24 != (char *)0x0) {
            Font_Get_String_Dimensions(Default_Font,local_24,&local_94,&local_8c);
            Font_Set_Foreground(Default_Font,local_3c);
            iVar21 = (local_28 - local_8c) + -0x14;
            iVar14 = local_94;
            goto LAB_004c224b;
          }
        }
        else if (local_20 == 5.60519e-45) {
          DrawSprite(DisplayInterface::currentBuffer,local_40->caretIndex[1] + (int)local_30,iVar19,
                     local_28,0x240004);
          if (local_34 != 0) {
            iVar21 = 0x240005;
            iVar19 = iVar19 + 0x14;
            iVar14 = local_28;
            goto LAB_004c2095;
          }
          if (local_24 != (char *)0x0) {
            Font_Get_String_Dimensions(Default_Font,local_24,local_d4,&local_88);
            Font_Set_Foreground(Default_Font,local_3c);
            iVar21 = local_28 - local_88 / 2;
            lVar20 = iVar19 + 0x14;
            goto LAB_004c2252;
          }
        }
        else if (local_20 == 7.00649e-45) {
          DrawSprite(DisplayInterface::currentBuffer,local_40->caretIndex[2] + (int)local_30,iVar19,
                     local_28,0x260004);
          if (local_34 != 0) {
            iVar21 = 0x260005;
            iVar19 = iVar19 + -0x14;
            iVar14 = local_28;
            goto LAB_004c2095;
          }
          if (local_24 != (char *)0x0) {
            Font_Get_String_Dimensions(Default_Font,local_24,&local_a8,&local_98);
            Font_Set_Foreground(Default_Font,local_3c);
            iVar21 = local_28 - local_98 / 2;
            lVar20 = (iVar19 - local_a8) + -0x14;
            goto LAB_004c2252;
          }
        }
      }
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_70)
      ;
    }
  }
  return;
}
