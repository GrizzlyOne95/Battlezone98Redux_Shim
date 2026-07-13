/*
 * Entry: 004cfa53
 * Name: InfoDisplay::Render
 * Namespace: InfoDisplay
 * Signature: void Render(InfoDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall InfoDisplay::Render(InfoDisplay *this)

{
  int iVar1;
  VECTOR_3D *pVVar2;
  long lVar3;
  long unaff_EBX;
  tagPOINT *unaff_ESI;
  int iVar4;
  int iVar5;
  char **ppcVar6;
  long *plVar7;
  tagPOINT *unaff_EDI;
  float fVar8;
  CAMERA *pCVar9;
  GameObject *pGVar10;
  float *pfVar11;
  long local_38;
  int local_34;
  tagPOINT local_28;
  int local_20;
  int local_1c;
  char *local_18;
  long local_14;
  float local_10;
  char *local_c;
  FONT *local_8;
  
  iVar4 = ((DisplayInterface::currentBuffer->Pane).x1 - (DisplayInterface::currentBuffer->Pane).x0)
          - RIGHT_OFFSET;
  local_38 = iVar4 - WIDTH;
  local_34 = (((DisplayInterface::currentBuffer->Pane).y1 -
              (DisplayInterface::currentBuffer->Pane).y0) - HEIGHT) / 2;
  iVar5 = local_34 + -1 + HEIGHT;
  iVar1 = IsJapanese();
  local_8 = J_Font;
  if (iVar1 == 0) {
    local_8 = Default_Font;
  }
  if ((this->objectShow == false) && ((UserProfilePtr->playOption & 0x80) == 0)) {
    pGVar10 = (GameObject *)0x0;
  }
  else {
    pGVar10 = FindSightObject(this);
  }
  SetObject(this,pGVar10);
  if (this->objectSave == (GameObject *)0x0) {
    fVar8 = Get_TimeLocal();
    if (fVar8 < this->objectiveLast) {
      local_18 = (char *)spriteZ;
      local_c = (char *)0x0;
      local_14 = 0;
      local_10 = 0.0;
      if (0 < this->objectiveCount) {
        ppcVar6 = &this->objectiveMessage[0].text;
        do {
          if (*ppcVar6 != (char *)0x0) {
            Font_Get_String_Dimensions(local_8,*ppcVar6,&local_1c,&local_28.y);
            if ((int)local_c < local_1c) {
              local_c = (char *)local_1c;
            }
            local_14 = local_14 + 10 + local_28.y;
          }
          local_10 = (float)((int)local_10 + 1);
          ppcVar6 = ppcVar6 + 6;
        } while ((int)local_10 < this->objectiveCount);
      }
      if (WIDTH < (int)local_c) {
        local_38 = local_38 + (WIDTH - (int)local_c);
      }
      if (HEIGHT < local_14) {
        local_34 = local_34 - (local_14 - HEIGHT) / 2;
        iVar5 = iVar5 + ((local_14 - HEIGHT) + 1) / 2;
      }
      if (400 < Device.Viewport.Width) {
        spriteZ = (float)local_18 + 0.01;
        Clipped_Rect_Filled(DisplayInterface::currentBuffer,local_38 + -0x11,local_34 + -2,iVar4 + 1
                            ,iVar5 + 2,DisplayInterface::colorBlack,ONE_THIRD_TRANSLUCENT_PIXELS);
      }
      local_14 = 0;
      spriteZ = (float)local_18;
      if (0 < this->objectiveCount) {
        plVar7 = &this->objectiveMessage[0].color;
        do {
          local_18 = (char *)plVar7[-1];
          if (local_18 != (char *)0x0) {
            Font_Set_Foreground(local_8,*plVar7);
            Font_Print_String(local_8,DisplayInterface::currentBuffer,local_38,local_34,local_18);
            lVar3 = Font_Get_String_Height(local_8,local_18);
            local_34 = local_34 + 10 + lVar3;
          }
          local_14 = local_14 + 1;
          plVar7 = plVar7 + 6;
        } while (local_14 < this->objectiveCount);
      }
    }
  }
  else {
    local_c = (this->objectMessage).text;
    local_10 = spriteZ;
    if (local_c != (char *)0x0) {
      Font_Get_String_Dimensions(local_8,local_c,&local_14,(long *)&local_18);
      if (WIDTH < local_14) {
        local_38 = local_38 + (WIDTH - local_14);
      }
      if (HEIGHT < (int)local_18) {
        local_34 = local_34 - ((int)local_18 - HEIGHT) / 2;
        iVar5 = iVar5 + (((int)local_18 - HEIGHT) + 1) / 2;
      }
    }
    if (400 < Device.Viewport.Width) {
      spriteZ = local_10 + 0.01;
      Clipped_Rect_Filled(DisplayInterface::currentBuffer,local_38 + -0x11,local_34 + -2,iVar4 + 1,
                          iVar5 + 2,DisplayInterface::colorBlack,ONE_THIRD_TRANSLUCENT_PIXELS);
    }
    spriteZ = local_10;
    if (local_c != (char *)0x0) {
      Font_Set_Foreground(local_8,(this->objectMessage).color);
      Font_Print_String(local_8,DisplayInterface::currentBuffer,local_38,local_34,local_c);
    }
    pfVar11 = (float *)0x0;
    pCVar9 = DisplayInterface::currentCamera;
    pVVar2 = (VECTOR_3D *)(**(code **)(this->objectSave->_padding_ + 0xc))();
    local_28 = WorldToScreen(pVVar2,pCVar9,pfVar11);
    if (((((DisplayInterface::currentBuffer->Pane).x0 <= local_28.x) &&
         (local_28.x <= (DisplayInterface::currentBuffer->Pane).x1)) &&
        ((DisplayInterface::currentBuffer->Pane).y0 <= local_28.y)) &&
       (local_28.y <= (DisplayInterface::currentBuffer->Pane).y1)) {
      local_20 = local_38 + -10;
      local_1c = (local_34 + iVar5) / 2;
      DrawLabelLine(DisplayInterface::currentBuffer,(tagRECT *)DisplayInterface::colorWhite,
                    unaff_EDI,unaff_ESI,unaff_EBX);
    }
  }
  return;
}
