/*
 * Entry: 004c4998
 * Name: ControlPanel::Render
 * Namespace: ControlPanel
 * Signature: void Render(ControlPanel * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::Render(ControlPanel *this)

{
  BuildItem *pBVar1;
  _OBJ76 *p_Var2;
  AiCommand AVar3;
  GameObjectClass *pGVar4;
  tagPOINT tVar5;
  VECTOR_3D VVar6;
  Scanner *pSVar7;
  Team *this_00;
  char cVar8;
  bool bVar9;
  int iVar10;
  uint uVar11;
  int extraout_EAX;
  GameObject *pGVar12;
  int iVar13;
  long lVar14;
  MAT_3D *pMVar15;
  AiMission *pAVar16;
  ulong uVar17;
  int iVar18;
  GameObject *pGVar19;
  float *pfVar20;
  VECTOR_3D *pVVar21;
  GameObject *pGVar22;
  tagENTITY *ptVar23;
  int *piVar24;
  int iVar25;
  VECTOR_3D *unaff_ESI;
  _GRAPHIC_BUFFER *p_Var26;
  ModeList *pMVar27;
  VECTOR_3D *unaff_EDI;
  char **ppcVar28;
  tagRECT *ptVar29;
  ModeList *pMVar30;
  long *plVar31;
  float10 fVar32;
  float fVar33;
  char *pcVar34;
  GKCommandKey GVar35;
  MAT_3D local_e4;
  undefined1 local_a4 [40];
  tagPOINT local_7c;
  double local_74;
  double local_6c;
  float local_64;
  tagPOINT local_60;
  tagRECT local_58;
  undefined1 local_48 [8];
  long local_40;
  int local_3c;
  int local_38;
  Scanner *local_34;
  char *local_30;
  long *local_2c;
  GameObject *local_28;
  float local_24;
  undefined8 local_20;
  float local_18;
  GameObject *local_14;
  tagRECT *local_10;
  char local_9;
  GameObject *local_8;
  
  CONNECTOR_POS.x = 5;
  if (Device.Viewport.Height < 0x1e0) {
    iVar10 = (Device.Viewport.Height * 0xb4) / 0x1e0;
  }
  else {
    iVar10 = 0xb4;
  }
  CONNECTOR_POS.y = Device.Viewport.Height - iVar10;
  local_28 = GameObject::userObject;
  if (GameObject::userObject == (GameObject *)0x0) {
    CONNECTOR_POS.x = 5;
    return;
  }
  uVar11 = (int)command_controls.menu_cycle + this->menuState * -2 & 3;
  this->menuState = uVar11;
  local_9 = '\0';
  if (uVar11 == 1) {
    this->menuItem = 0;
  }
  else if (uVar11 == 2) {
    this->menuItem = -1;
  }
  else if (uVar11 == 3) {
    if (command_controls.menu_down != '\0') {
      this->menuPos = this->menuPos + 0x10000;
    }
    if (command_controls.menu_up != '\0') {
      this->menuPos = this->menuPos + -0x10000;
    }
    TimeStepLocal();
    _ftol2_sse();
    plVar31 = &this->menuPos;
    *plVar31 = *plVar31 + extraout_EAX;
    if (*plVar31 < 0) {
      this->menuPos = 0;
    }
    if (0xcffff < (uint)this->menuPos) {
      this->menuPos = 0xcffff;
    }
    iVar10 = (int)*(short *)((int)&this->menuPos + 2);
    if (this->menuItem != iVar10) {
      local_9 = '\x01';
      this->menuItem = iVar10;
    }
  }
  local_18 = spriteZ;
  if (400 < Device.Viewport.Width) {
    spriteZ = spriteZ + 0.3;
    Clipped_Rect_Filled(DisplayInterface::currentBuffer,CONTROL_PANEL_RECT.left + -2,
                        CONTROL_PANEL_RECT.top + -2,CONTROL_PANEL_RECT.right + 2,
                        CONTROL_PANEL_RECT.bottom + 2,DisplayInterface::colorBlack,
                        ONE_THIRD_TRANSLUCENT_PIXELS);
  }
  if (-1 < this->menuItem) {
    if (command_controls.menu_next != '\0') {
      *BUTTON_MAP[this->menuItem] = '\x01';
    }
    spriteZ = local_18 + 0.2;
    iVar10 = this->menuItem;
    Clipped_Rect_Filled(DisplayInterface::currentBuffer,MODE_BUTTON_RECT[iVar10].left,
                        MODE_BUTTON_RECT[iVar10].top,MODE_BUTTON_RECT[iVar10].right,
                        MODE_BUTTON_RECT[iVar10].bottom,DisplayInterface::colorDkGrey,SOLID_PIXELS);
  }
  spriteZ = local_18;
  if (command_controls.cmd_click[0] != '\0') {
    ppcVar28 = BUTTON_MAP;
    local_10 = MODE_BUTTON_RECT;
    do {
      tVar5.y = DisplayInterface::mousePos.y;
      tVar5.x = DisplayInterface::mousePos.x;
      iVar10 = InsideRect(tVar5,local_10);
      if (iVar10 != 0) {
        **ppcVar28 = '\x01';
      }
      local_10 = local_10 + 1;
      ppcVar28 = ppcVar28 + 1;
    } while ((int)local_10 < 0x6299d0);
  }
  if (local_9 != '\0') {
    iVar10 = this->menuItem;
    if (iVar10 < 10) {
      if (this->modeButton[iVar10].color != 0) {
        bVar9 = ((this->currentModes).enabledMask & 1 << ((char)iVar10 + 1U & 0x1f)) == 0;
        goto LAB_004c4be5;
      }
      pcVar34 = "mnu_empt.wav";
    }
    else {
      if (iVar10 == 10) {
        bVar9 = (this->cmdButton).command == CMD_NONE;
      }
      else if (iVar10 == 0xb) {
        bVar9 = (this->altButton).command == CMD_NONE;
      }
      else {
        if (iVar10 != 0xc) goto LAB_004c4c28;
        bVar9 = this->itemSelected == 0;
      }
LAB_004c4be5:
      if (bVar9) {
        pcVar34 = "mnu_disa.wav";
      }
      else {
        pcVar34 = "mnu_enab.wav";
      }
    }
    StartGASEvent(pcVar34,(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
  }
LAB_004c4c28:
  this->itemEnabled = 0;
  this->itemSelected = 0;
  this->itemAttacked = 0;
  local_20 = (double)CONCAT44(GameObject::userTeamList,(undefined4)local_20);
  iVar10 = UserPref_arcadeMode();
  if (iVar10 != 0) {
    this->currentItem = -1;
    ModeList::RemoveAllModes(&this->currentModes);
    SelectNone(this);
    pGVar12 = (this->cmdButton).object;
    p_Var26 = DisplayInterface::currentBuffer;
    if (pGVar12 != (GameObject *)0x0) {
      iVar10 = pGVar12->nameIndex;
      if (iVar10 == 0) {
        pcVar34 = pGVar12->name;
        pGVar12 = (GameObject *)0x0;
        if (pcVar34 != (char *)0x0) {
          Font_Set_Foreground(Default_Font,(this->cmdButton).color);
          Font_Get_String_Dimensions(Default_Font,pcVar34,(long *)&local_14,(long *)&local_34);
          Font_Print_String(Default_Font,DisplayInterface::currentBuffer,CMD_BUTTON_POS->x,
                            CMD_BUTTON_POS->y - (int)local_34 / 2,pcVar34);
          pGVar12 = local_14;
        }
      }
      else {
        Foreground_Color = (this->cmdButton).color;
        DrawSprite(DisplayInterface::currentBuffer,iVar10,CMD_BUTTON_POS->x,CMD_BUTTON_POS->y,
                   0x40005);
        pGVar12 = (GameObject *)GetSpriteWidth(iVar10);
      }
      pVVar21 = (this->cmdButton).pos;
      p_Var26 = DisplayInterface::currentBuffer;
      if (pVVar21 != (VECTOR_3D *)0x0) {
        iVar10 = CMD_BUTTON_POS->y;
        local_30 = (char *)((int)&pGVar12->_padding_ + CMD_BUTTON_POS->x + 3);
        local_60 = WorldToScreen(pVVar21,DisplayInterface::currentCamera,(float *)0x0);
        p_Var26 = DisplayInterface::currentBuffer;
        local_48._0_4_ = (DisplayInterface::currentBuffer->Pane).x0 + 2;
        local_48._4_4_ = (DisplayInterface::currentBuffer->Pane).y0 + 2;
        local_40 = (DisplayInterface::currentBuffer->Pane).x1 + -2;
        local_3c = (DisplayInterface::currentBuffer->Pane).y1 + -2;
        iVar13 = InsideRect(local_60,(tagRECT *)local_48);
        if (iVar13 != 0) {
          Graphic_Rect_Filled(p_Var26,(long)(local_30 + -2),iVar10 + -2,(long)(local_30 + 2),
                              iVar10 + 2,(this->cmdButton).color,SOLID_PIXELS);
          Graphic_Line(DisplayInterface::currentBuffer,(long)local_30,iVar10,
                       CMD_BUTTON_RECT->right + 10,iVar10,(this->cmdButton).color,SOLID_PIXELS);
          lVar14 = local_60.x;
          Graphic_Line(DisplayInterface::currentBuffer,CMD_BUTTON_RECT->right + 10,iVar10,local_60.x
                       ,local_60.y,(this->cmdButton).color,SOLID_PIXELS);
          Graphic_Rect_Filled(DisplayInterface::currentBuffer,lVar14 + -2,local_60.y + -2,lVar14 + 2
                              ,local_60.y + 2,(this->cmdButton).color,SOLID_PIXELS);
          p_Var26 = DisplayInterface::currentBuffer;
        }
      }
    }
    if (this->buildItem->parent != (BuildItem *)0x0) {
      DrawSprite(p_Var26,CANCEL_KEY.index,CANCEL_BUTTON_POS->x + -4,CANCEL_BUTTON_POS->y,0x60001);
      Foreground_Color = DisplayInterface::colorWhite;
      DrawSprite(DisplayInterface::currentBuffer,CANCEL_LABEL.index,CANCEL_BUTTON_POS->x,
                 CANCEL_BUTTON_POS->y,0x40005);
      if (command_controls.menu_back != '\0') {
        StartGASEvent("mnu_back.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
        this->buildItem = this->buildItem->parent;
      }
    }
    if ((_S2 & 1) == 0) {
      _S2 = _S2 | 1;
      itemColor[0] = DisplayInterface::colorWhite;
      itemColor[1] = DisplayInterface::colorGreen;
      itemColor[2] = DisplayInterface::colorRed;
    }
    pBVar1 = this->buildItem;
    if (pBVar1->menu != (BuildItem *)0x0) {
      this->menuMode = MENU_ITEM_PANEL;
      if (pBVar1->index == 0) {
        if (pBVar1->name[0] != '\0') {
          Font_Set_Foreground(Default_Font,itemColor[pBVar1->team]);
          Font_Print_String(Default_Font,&Device.Viewport,TITLE_BUTTON_POS.x,
                            TITLE_BUTTON_POS.y - Default_Font->char_height / 2,this->buildItem->name
                           );
        }
      }
      else {
        Foreground_Color = itemColor[pBVar1->team];
        DrawSprite(DisplayInterface::currentBuffer,this->buildItem->index,TITLE_BUTTON_POS.x + 2,
                   TITLE_BUTTON_POS.y,0x40005);
      }
      ptVar29 = (tagRECT *)&this->modeButton[0].color;
      local_8 = (GameObject *)0x0;
      local_2c = (long *)0x0;
      do {
        pGVar12 = (GameObject *)((int)local_2c + (int)(this->buildItem->menu->name + -4));
        lVar14 = 0;
        local_14 = pGVar12;
        local_10 = ptVar29;
        if (pGVar12->_padding_ == 0) {
          if (pGVar12->_padding_ == 0) {
            (((ModeButton *)((int)ptVar29 + -4))->field0_0x0).type = 0;
          }
          else {
            if (*BUTTON_MAP[(int)local_8] != '\0') {
              StartGASEvent("mnu_next.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
              this->buildItem = (BuildItem *)pGVar12;
            }
            (((ModeButton *)((int)ptVar29 + -4))->field0_0x0).type = (long)local_8;
            lVar14 = itemColor[pGVar12->_padding_];
          }
        }
        else {
          if ((*BUTTON_MAP[(int)local_8] != '\0') &&
             (StartGASEvent("mnu_clik.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0),
             reticle.groundPos != (VECTOR_3D *)0x0)) {
            local_60 = (tagPOINT)(double)(reticle.groundPos)->x;
            local_20 = (double)(reticle.groundPos)->z;
            Terrain_GetHeightAndNormal
                      ((double)local_60,local_20,(float *)&local_34,(VECTOR_3D *)(local_48 + 4));
            p_Var2 = local_28->obj;
            local_58.top = (long)(p_Var2->transform).front_x;
            local_58.right = (long)(p_Var2->transform).front_y;
            local_58.bottom = (long)(p_Var2->transform).front_z;
            pMVar15 = Build_Orthogonal_Matrix(&local_e4,unaff_EDI,unaff_ESI);
            local_7c = local_60;
            pBVar1 = this->buildItem;
            pfVar20 = (float *)local_a4;
            for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
              *pfVar20 = pMVar15->right_x;
              pMVar15 = (MAT_3D *)&pMVar15->right_y;
              pfVar20 = pfVar20 + 1;
            }
            local_74 = (double)(float)local_34;
            local_6c = local_20;
            pGVar12 = GameObjectClass::Build
                                ((GameObjectClass *)local_14->_padding_,(MAT_3D *)local_a4,
                                 pBVar1->team,0,-1,(char *)0x0);
            pAVar16 = AiMission::GetCurrent();
            (**(code **)(pAVar16->_padding_ + 0x18))(pGVar12);
            pGVar12 = local_14;
            ptVar29 = local_10;
          }
          ((ModeButton *)((int)ptVar29 + -4))->field0_0x0 = (ModeButton_u_0)pGVar12->_padding_;
          lVar14 = DisplayInterface::colorWhite;
        }
        ptVar29->left = lVar14;
        if (lVar14 != 0) {
          DrawSprite(DisplayInterface::currentBuffer,NUM_KEY[(int)local_8].index,
                     MODE_BUTTON_POS[(int)local_8].x + -4,MODE_BUTTON_POS[(int)local_8].y,0x60001);
        }
        if (pGVar12->_padding_ == 0) {
          local_14 = (GameObject *)&pGVar12->_padding_;
          if ((char)*(int *)local_14 != '\0') {
            Font_Set_Foreground(Default_Font,ptVar29->left);
            Font_Print_String(Default_Font,&Device.Viewport,MODE_BUTTON_POS[(int)local_8].x,
                              MODE_BUTTON_POS[(int)local_8].y - Default_Font->char_height / 2,
                              (char *)local_14);
          }
        }
        else {
          Foreground_Color = ptVar29->left;
          DrawSprite(DisplayInterface::currentBuffer,pGVar12->_padding_,
                     MODE_BUTTON_POS[(int)local_8].x,MODE_BUTTON_POS[(int)local_8].y,0x40005);
        }
        local_8 = (GameObject *)((int)&local_8->_padding_ + 1);
        local_2c = local_2c + 9;
        ptVar29 = (tagRECT *)((int)ptVar29 + 0x18);
        local_10 = ptVar29;
      } while ((int)local_8 < 10);
    }
    goto LAB_004c72e3;
  }
  this->buildItem = &buildMenu;
  local_10 = (tagRECT *)0x0;
  local_8 = (GameObject *)0x0;
  if (0 < this->selectNum) {
    piVar24 = this->selectList;
    local_2c = piVar24;
    do {
      local_14 = GameObject::GetObj(*piVar24);
      if (local_14 != (GameObject *)0x0) {
        cVar8 = (**(code **)(local_14->_padding_ + 0x38))();
        if (cVar8 == '\0') {
          GameObject::SetSelected(local_14,false);
          this->currentItem = -1;
          this->itemSelected = 0;
        }
        else {
          local_10 = (tagRECT *)((int)local_10 + 1);
          *local_2c = *piVar24;
          local_2c = local_2c + 1;
        }
      }
      local_8 = (GameObject *)((int)&local_8->_padding_ + 1);
      piVar24 = piVar24 + 1;
    } while ((int)local_8 < this->selectNum);
  }
  this->selectNum = (long)local_10;
  local_8 = (GameObject *)0x0;
  do {
    if (command_controls.group_select[(int)local_8] != '\0') {
      if (command_controls.cmd_multi == '\0') {
        StartGASEvent("mnu_next.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
        SelectGroup(this,(long)local_8);
      }
      else {
        StartGASEvent("mnu_clik.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
        BindGroup(this,(long)local_8);
      }
      break;
    }
    local_8 = (GameObject *)((int)&local_8->_padding_ + 1);
  } while ((int)local_8 < 10);
  if (command_controls.menu_press != '\0') {
    AVar3 = (this->cmdButton).command;
    if (AVar3 == CMD_SELECT) {
      GameObject::SetCommand((this->cmdButton).object,CMD_SELECT);
      if (((this->cmdButton).object)->teamSlot - 0x23U < 10) {
        StartGASEvent("mnu_clik.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
        GameObject::SetTarget(local_28,(this->cmdButton).object);
      }
      else {
        StartGASEvent("mnu_next.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
        pGVar12 = (this->cmdButton).object;
        if (command_controls.cmd_multi == '\0') {
          SelectOne(this,pGVar12);
        }
        else {
          SelectAdd(this,pGVar12);
        }
      }
    }
    else if (AVar3 == CMD_NO_DROPOFF) {
      StartGASEvent("mnu_buzz.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
      pGVar12 = (this->cmdButton).object;
      if (pGVar12 == (GameObject *)0x0) {
        pVVar21 = (this->cmdButton).pos;
        if (pVVar21 != (VECTOR_3D *)0x0) {
          BroadcastCommand(this,(this->cmdButton).command,pVVar21);
          goto LAB_004c537f;
        }
        pGVar12 = (GameObject *)0x0;
      }
      BroadcastCommand(this,(this->cmdButton).command,pGVar12);
    }
    else if (AVar3 != CMD_NONE) {
      StartGASEvent("mnu_clik.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
      pGVar12 = (this->cmdButton).object;
      if (pGVar12 == (GameObject *)0x0) {
        pVVar21 = (this->cmdButton).pos;
        if (pVVar21 == (VECTOR_3D *)0x0) {
          pGVar12 = (GameObject *)0x0;
          goto LAB_004c536b;
        }
        BroadcastCommand(this,(this->cmdButton).command,pVVar21);
      }
      else {
LAB_004c536b:
        BroadcastCommand(this,(this->cmdButton).command,pGVar12);
      }
      SelectNone(this);
    }
  }
LAB_004c537f:
  Foreground_Color = (this->cmdButton).color;
  DrawSprite(DisplayInterface::currentBuffer,CMD_KEY.index,CMD_BUTTON_POS->x + -4,CMD_BUTTON_POS->y,
             0x60001);
  iVar10 = COMMAND_TEXT[(this->cmdButton).command].index;
  DrawSprite(DisplayInterface::currentBuffer,iVar10,CMD_BUTTON_POS->x,CMD_BUTTON_POS->y,0x40005);
  iVar10 = GetSpriteWidth(iVar10);
  pGVar12 = (this->cmdButton).object;
  if (pGVar12 != (GameObject *)0x0) {
    local_14 = (GameObject *)pGVar12->nameIndex;
    iVar10 = iVar10 + 3;
    if (local_14 == (GameObject *)0x0) {
      local_14 = (GameObject *)pGVar12->name;
      if (local_14 != (GameObject *)0x0) {
        Font_Get_String_Dimensions
                  (Default_Font,(char *)local_14,(long *)&local_2c,(long *)&local_34);
        Font_Set_Foreground(Default_Font,(this->cmdButton).color);
        Font_Print_String(Default_Font,DisplayInterface::currentBuffer,CMD_BUTTON_POS->x + iVar10,
                          CMD_BUTTON_POS->y - (int)local_34 / 2,(char *)local_14);
        iVar10 = iVar10 + (int)local_2c;
      }
    }
    else {
      DrawSprite(DisplayInterface::currentBuffer,(int)local_14,CMD_BUTTON_POS->x + iVar10,
                 CMD_BUTTON_POS->y,0x40005);
      iVar13 = GetSpriteWidth((int)local_14);
      iVar10 = iVar10 + iVar13;
    }
  }
  pVVar21 = (this->cmdButton).pos;
  p_Var26 = DisplayInterface::currentBuffer;
  if ((pVVar21 != (VECTOR_3D *)0x0) && ((this->cmdButton).command != CMD_NONE)) {
    iVar13 = CMD_BUTTON_POS->y;
    local_38 = CMD_BUTTON_POS->x + 3 + iVar10;
    local_60 = WorldToScreen(pVVar21,DisplayInterface::currentCamera,(float *)0x0);
    p_Var26 = DisplayInterface::currentBuffer;
    local_48._0_4_ = (DisplayInterface::currentBuffer->Pane).x0 + 2;
    local_48._4_4_ = (DisplayInterface::currentBuffer->Pane).y0 + 2;
    local_40 = (DisplayInterface::currentBuffer->Pane).x1 + -2;
    local_3c = (DisplayInterface::currentBuffer->Pane).y1 + -2;
    iVar10 = InsideRect(local_60,(tagRECT *)local_48);
    if (iVar10 != 0) {
      Graphic_Rect_Filled(p_Var26,local_38 + -2,iVar13 + -2,local_38 + 2,iVar13 + 2,
                          (this->cmdButton).color,SOLID_PIXELS);
      Graphic_Line(DisplayInterface::currentBuffer,local_38,iVar13,CMD_BUTTON_RECT->right + 10,
                   iVar13,(this->cmdButton).color,SOLID_PIXELS);
      lVar14 = local_60.x;
      Graphic_Line(DisplayInterface::currentBuffer,CMD_BUTTON_RECT->right + 10,iVar13,local_60.x,
                   local_60.y,(this->cmdButton).color,SOLID_PIXELS);
      Graphic_Rect_Filled(DisplayInterface::currentBuffer,lVar14 + -2,local_60.y + -2,lVar14 + 2,
                          local_60.y + 2,(this->cmdButton).color,SOLID_PIXELS);
      p_Var26 = DisplayInterface::currentBuffer;
    }
  }
  if ((command_controls.alt_press != '\0') && ((this->altButton).command != CMD_NONE)) {
    StartGASEvent("mnu_clik.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
    pGVar12 = (this->altButton).object;
    if (pGVar12 == (GameObject *)0x0) {
      pVVar21 = (this->altButton).pos;
      if (pVVar21 == (VECTOR_3D *)0x0) {
        pGVar12 = (GameObject *)0x0;
        goto LAB_004c5609;
      }
      BroadcastCommand(this,(this->altButton).command,pVVar21);
    }
    else {
LAB_004c5609:
      BroadcastCommand(this,(this->altButton).command,pGVar12);
    }
    SelectNone(this);
    p_Var26 = DisplayInterface::currentBuffer;
  }
  Foreground_Color = (this->altButton).color;
  DrawSprite(p_Var26,ALT_KEY.index,ALT_BUTTON_POS->x + -4,ALT_BUTTON_POS->y,0x60001);
  local_34 = (Scanner *)COMMAND_TEXT[(this->altButton).command].index;
  DrawSprite(DisplayInterface::currentBuffer,(int)local_34,ALT_BUTTON_POS->x,ALT_BUTTON_POS->y,
             0x40005);
  pGVar12 = (this->altButton).object;
  if (pGVar12 != (GameObject *)0x0) {
    iVar10 = GetSpriteWidth((int)local_34);
    local_14 = (GameObject *)(iVar10 + 3);
    if (pGVar12->nameIndex == 0) {
      pcVar34 = pGVar12->name;
      if (pcVar34 != (char *)0x0) {
        Font_Get_String_Dimensions(Default_Font,pcVar34,&local_60.y,(long *)&local_34);
        Font_Set_Foreground(Default_Font,(this->altButton).color);
        Font_Print_String(Default_Font,DisplayInterface::currentBuffer,
                          (long)((int)&local_14->_padding_ + ALT_BUTTON_POS->x),
                          ALT_BUTTON_POS->y - (int)local_34 / 2,pcVar34);
      }
    }
    else {
      DrawSprite(DisplayInterface::currentBuffer,pGVar12->nameIndex,
                 (int)((int)&local_14->_padding_ + ALT_BUTTON_POS->x),ALT_BUTTON_POS->y,0x40005);
    }
  }
  if ((-1 < this->currentItem) || (0 < this->selectNum)) {
    DrawSprite(DisplayInterface::currentBuffer,CANCEL_KEY.index,CANCEL_BUTTON_POS->x + -4,
               CANCEL_BUTTON_POS->y,0x60001);
    Foreground_Color = DisplayInterface::colorWhite;
    DrawSprite(DisplayInterface::currentBuffer,CANCEL_LABEL.index,CANCEL_BUTTON_POS->x,
               CANCEL_BUTTON_POS->y,0x40005);
    if (command_controls.menu_back != '\0') {
      StartGASEvent("mnu_back.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
      SelectNone(this);
    }
  }
  local_24 = Get_TimeLocal();
  local_8 = (GameObject *)0x0;
  local_10 = (tagRECT *)&MENU_ITEM[0].maxSlot;
  do {
    uVar11 = 1 << ((byte)local_8 & 0x1f);
    if (local_8 == (GameObject *)SATELLITE_ITEM) {
      iVar10 = ControlPanel_SatelliteEnabled();
      if (iVar10 == 0) {
        if (View_Record.Current_View == OVER_VIEW) {
          StartGASEvent("mnu_back.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
          GVar35 = GK_TOGGLE_OVERVIEW;
          ptVar23 = (tagENTITY *)(**(code **)(local_28->_padding_ + 0x2c))();
          Set_View(ptVar23,GVar35);
        }
      }
      else {
        this->itemEnabled = this->itemEnabled | uVar11;
        if (View_Record.Current_View == OVER_VIEW) {
          this->itemSelected = this->itemSelected | uVar11;
        }
      }
    }
    else {
      iVar10 = local_10[-1].bottom;
      if (iVar10 == local_10->left) {
        pGVar12 = Team::GetSlot(local_20._4_4_,iVar10);
        if (pGVar12 != (GameObject *)0x0) {
          cVar8 = (**(code **)(pGVar12->_padding_ + 0x38))();
          if ((cVar8 != '\0') && (pGVar12->isCargo == false)) {
            this->itemEnabled = this->itemEnabled | uVar11;
          }
          if ((pGVar12->isSelected != false) &&
             (this->itemSelected = this->itemSelected | uVar11, this->currentItem == -1)) {
            this->currentItem = (long)local_8;
          }
          fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
          if ((((float10)0.0 <= fVar32) && (local_24 < pGVar12->enemyShot + 2.0)) &&
             (uVar17 = Get_Time_Long(), (char)uVar17 < '\0')) {
            this->itemAttacked = this->itemAttacked | uVar11;
          }
        }
      }
      else if (iVar10 <= local_10->left) {
        do {
          pGVar12 = Team::GetSlot(local_20._4_4_,iVar10);
          if (pGVar12 != (GameObject *)0x0) {
            this->itemEnabled = this->itemEnabled | uVar11;
            if ((pGVar12->isSelected != false) &&
               (this->itemSelected = this->itemSelected | uVar11, this->currentItem == -1)) {
              this->currentItem = (long)local_8;
            }
            if ((local_24 < pGVar12->enemyShot + 2.0) &&
               (uVar17 = Get_Time_Long(), (char)uVar17 < '\0')) {
              this->itemAttacked = this->itemAttacked | uVar11;
            }
          }
          iVar10 = iVar10 + 1;
        } while (iVar10 <= local_10->left);
      }
    }
    local_8 = (GameObject *)((int)&local_8->_padding_ + 1);
    local_10 = local_10 + 1;
  } while (local_8 < (GameObject *)0x9);
  ModeList::RemoveAllModes(&this->currentModes);
  if (0 < this->selectNum) {
    pGVar12 = GameObject::GetObj(this->selectList[0]);
    pMVar27 = &pGVar12->modeList;
    pMVar30 = &this->currentModes;
    for (iVar10 = 0xd; iVar10 != 0; iVar10 = iVar10 + -1) {
      pMVar30->modeList[0] = pMVar27->modeList[0];
      pMVar27 = (ModeList *)(pMVar27->modeList + 1);
      pMVar30 = (ModeList *)(pMVar30->modeList + 1);
    }
    iVar10 = 1;
    if (1 < this->selectNum) {
      piVar24 = this->selectList;
      do {
        piVar24 = piVar24 + 1;
        pGVar12 = GameObject::GetObj(*piVar24);
        ModeList::Intersect(&this->currentModes,&pGVar12->modeList);
        iVar10 = iVar10 + 1;
      } while (iVar10 < this->selectNum);
    }
  }
  uVar11 = (this->currentModes).activeSlot;
  if (uVar11 < 0xb) {
    iVar10 = (this->currentModes).modeList[uVar11];
  }
  else {
    iVar10 = 0;
  }
  this->currentMode = iVar10;
  lVar14 = TITLE_BUTTON_POS.y;
  iVar10 = this->currentItem;
  if (iVar10 != DEFENSE_ITEM) {
    if (iVar10 != TARGETS_ITEM) {
      if (iVar10 != BEACONS_ITEM) {
        if ((command_controls.cmd_multi == '\0') && (0 < this->selectNum)) {
          this->menuMode = MENU_MODE_PANEL;
          SetModeMenu(this);
          pGVar12 = GameObject::GetObj(this->selectList[0]);
          spriteZ = local_18 + 0.1;
          local_48._0_4_ = 10;
          local_48._4_4_ = 10;
          local_3c = TITLE_BUTTON_POS.y + -1;
          local_40 = 0x9c;
          fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
          local_14 = (GameObject *)(float)fVar32;
          lVar14 = DisplayInterface::colorRed;
          if (pGVar12->enemyShot + 2.0 <= local_24) {
            lVar14 = GetHealthColorDim((float)local_14);
          }
          DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)local_14,(tagRECT *)local_48,
                              lVar14,DisplayInterface::colorBlack);
          local_58.top = TITLE_BUTTON_POS.y + 1;
          local_58.left = 10;
          local_58.right = 0x9c;
          local_58.bottom = 0x12;
          fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
          DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)fVar32,&local_58,
                              DisplayInterface::colorDkBlue,DisplayInterface::colorBlack);
          spriteZ = local_18;
          if (pGVar12->nameIndex == 0) {
            pcVar34 = pGVar12->name;
            if (pcVar34 != (char *)0x0) {
              Font_Set_Foreground(Default_Font,DisplayInterface::colorWhite);
              Font_Print_String(Default_Font,DisplayInterface::currentBuffer,TITLE_BUTTON_POS.x,
                                (0x1c - Default_Font->char_height) / 2,pcVar34);
            }
          }
          else {
            Foreground_Color = DisplayInterface::colorWhite;
            DrawSprite(DisplayInterface::currentBuffer,pGVar12->nameIndex,TITLE_BUTTON_POS.x,0xe,
                       0x40005);
          }
          local_10 = (tagRECT *)&this->modeButton[0].color;
          iVar10 = 0;
          local_20 = (double)CONCAT44(0x629908,(undefined4)local_20);
          do {
            pGVar4 = (((ModeButton *)((int)local_10 + -4))->field0_0x0).item;
            if (pGVar4 != (GameObjectClass *)0x0) {
              local_9 = ((this->currentModes).enabledMask & 1 << ((char)iVar10 + 1U & 0x1f)) != 0;
              if ((bool)local_9) {
                if (*BUTTON_MAP[iVar10] != '\0') {
                  if (pGVar4 == (GameObjectClass *)0xa) {
                    StartGASEvent("mnu_next.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0)
                    ;
                    lVar14 = BEACONS_ITEM;
LAB_004c6a62:
                    this->currentItem = lVar14;
                  }
                  else if (pGVar4 == (GameObjectClass *)0xe) {
                    StartGASEvent("mnu_next.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0)
                    ;
                    lVar14 = TARGETS_ITEM;
                    this->scanTimer = -1e+30;
                    this->currentItem = lVar14;
                  }
                  else {
                    if (pGVar4 == (GameObjectClass *)0x11) {
                      StartGASEvent("mnu_next.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,
                                    (GAS_PREP_INFO *)0x0);
                      lVar14 = DEFENSE_ITEM;
                      goto LAB_004c6a62;
                    }
                    StartGASEvent("mnu_clik.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0)
                    ;
                    (this->currentModes).activeSlot = iVar10;
                    this->currentMode = (int)pGVar4;
                    SetModeMenu(this);
                    bVar9 = BroadcastMode(this,(int)pGVar4);
                    if (bVar9) {
                      SelectNone(this);
                    }
                  }
                }
                DrawSprite(DisplayInterface::currentBuffer,NUM_KEY[iVar10].index,
                           MODE_BUTTON_POS[iVar10].x + -4,MODE_BUTTON_POS[iVar10].y,0x60001);
              }
              if ((int)pGVar4 < 0x19) {
                Foreground_Color = local_10->left;
                DrawSprite(DisplayInterface::currentBuffer,MODE_TEXT[(int)pGVar4].index,
                           MODE_BUTTON_POS[iVar10].x,MODE_BUTTON_POS[iVar10].y,0x40005);
              }
              else {
                if (pGVar4->unitNameIndex == 0) {
                  if (pGVar4 != (GameObjectClass *)0xffffff94) {
                    Font_Set_Foreground(Default_Font,local_10->left);
                    Font_Print_String(Default_Font,DisplayInterface::currentBuffer,
                                      MODE_BUTTON_POS[iVar10].x,
                                      MODE_BUTTON_POS[iVar10].y - Default_Font->char_height / 2,
                                      pGVar4->unitName);
                  }
                }
                else {
                  Foreground_Color = local_10->left;
                  DrawSprite(DisplayInterface::currentBuffer,pGVar4->unitNameIndex,
                             MODE_BUTTON_POS[iVar10].x,MODE_BUTTON_POS[iVar10].y,0x40005);
                }
                local_34 = (Scanner *)GameObject::userTeamNumber;
                lVar14 = AdjustedScrapCost(GameObject::userTeamNumber,pGVar4);
                sprintf((char *)&local_8,"%02d",lVar14);
                lVar14 = DisplayInterface::colorBlue;
                if (local_9 == '\0') {
                  lVar14 = DisplayInterface::colorGrey;
                }
                Font_Set_Foreground(Default_Font,lVar14);
                Font_Print_String(Default_Font,DisplayInterface::currentBuffer,
                                  *(int *)local_20._4_4_ + -0x19,*(long *)((int)local_20._4_4_ + -4)
                                  ,(char *)&local_8);
                lVar14 = AdjustedPilotCost((int)local_34,pGVar4);
                if (lVar14 != 0) {
                  local_8 = (GameObject *)CONCAT22(local_8._2_2_,0x50);
                  lVar14 = DisplayInterface::colorGreen;
                  if (local_9 == '\0') {
                    lVar14 = DisplayInterface::colorGrey;
                  }
                  Font_Set_Foreground(Default_Font,lVar14);
                  Font_Print_String(Default_Font,DisplayInterface::currentBuffer,
                                    *(int *)local_20._4_4_ + -6,*(long *)((int)local_20._4_4_ + -4),
                                    (char *)&local_8);
                }
              }
            }
            local_20 = (double)CONCAT44((int)local_20._4_4_ + 0x10,(undefined4)local_20);
            local_10 = (tagRECT *)((int)local_10 + 0x18);
            iVar10 = iVar10 + 1;
          } while (iVar10 < 10);
        }
        else if (iVar10 < 0) {
          this->menuMode = MENU_TYPE_PANEL;
          Foreground_Color = DisplayInterface::colorWhite;
          DrawSprite(DisplayInterface::currentBuffer,TITLE_TEXT.index,TITLE_BUTTON_POS.x + 2,lVar14,
                     0x40005);
          this->itemDisplayed = this->itemDisplayed | this->itemEnabled;
          uVar11 = 0;
          local_10 = (tagRECT *)0x0;
          plVar31 = &this->modeButton[0].color;
          do {
            local_34 = (Scanner *)(1 << ((byte)uVar11 & 0x1f));
            if ((this->itemDisplayed & (uint)local_34) != 0) {
              local_9 = (this->itemEnabled & (uint)local_34) != 0;
              if (((bool)local_9) && (*BUTTON_MAP[uVar11] != '\0')) {
                if (uVar11 == SATELLITE_ITEM) {
                  if (View_Record.Current_View == OVER_VIEW) {
                    StartGASEvent("mnu_back.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0)
                    ;
                    GVar35 = GK_TOGGLE_OVERVIEW;
                    ptVar23 = (tagENTITY *)(**(code **)(local_28->_padding_ + 0x2c))();
                    Set_View(ptVar23,GVar35);
                    BettyVoice::SatelliteDeactivated(&bettyVoice);
                  }
                  else {
                    StartGASEvent("mnu_next.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0)
                    ;
                    GVar35 = GK_TOGGLE_OVERVIEW;
                    ptVar23 = (tagENTITY *)(**(code **)(local_28->_padding_ + 0x2c))();
                    Set_View(ptVar23,GVar35);
                    BettyVoice::SatelliteActivated(&bettyVoice);
                  }
                }
                else {
                  StartGASEvent("mnu_next.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
                  this->itemSelected = (ulong)local_34;
                  this->currentItem = uVar11;
                  if (local_10[0x629c0].top == local_10[0x629c0].right) {
                    local_14 = Team::GetSlot(local_20._4_4_,local_10[0x629c0].top);
                    if (command_controls.cmd_multi == '\0') {
                      SelectOne(this,local_14);
                    }
                    else {
                      SelectAdd(this,local_14);
                    }
                    GameObject::SetCommand(local_14,CMD_SELECT);
                  }
                  else if (command_controls.cmd_multi != '\0') {
                    SelectType(this,uVar11);
                  }
                }
              }
              local_8 = (GameObject *)0x0;
              (((ModeButton *)(plVar31 + -1))->field0_0x0).mode = uVar11;
              iVar10 = local_10[0x629c0].top;
              if ((iVar10 == local_10[0x629c0].right) && (0 < iVar10)) {
                local_8 = Team::GetSlot(local_20._4_4_,iVar10);
              }
              lVar14 = DisplayInterface::colorRed;
              if ((((this->itemAttacked & (uint)local_34) == 0) &&
                  (lVar14 = DisplayInterface::colorYellow,
                  (this->itemSelected & (uint)local_34) == 0)) &&
                 (lVar14 = DisplayInterface::colorGreen, local_9 == '\0')) {
                lVar14 = DisplayInterface::colorGrey;
              }
              *plVar31 = lVar14;
              if (local_9 != '\0') {
                DrawSprite(DisplayInterface::currentBuffer,NUM_KEY[uVar11].index,
                           MODE_BUTTON_POS[uVar11].x + -4,MODE_BUTTON_POS[uVar11].y,0x60001);
              }
              if (local_8 != (GameObject *)0x0) {
                spriteZ = local_18 + 0.1;
                fVar32 = (float10)(**(code **)(local_8->_padding_ + 0x1c))();
                local_34 = (Scanner *)(float)fVar32;
                fVar32 = (float10)(**(code **)(local_8->_padding_ + 0x1c))();
                local_60.y = (long)(float)fVar32;
                if ((float)local_34 != (float)plVar31[1]) {
                  plVar31[1] = (long)local_34;
                  plVar31[2] = (long)local_24;
                }
                if (fVar32 != (float10)(float)plVar31[3]) {
                  plVar31[3] = (long)(float)fVar32;
                  plVar31[4] = (long)local_24;
                }
                if (local_24 < (float)plVar31[2] + 2.0) {
                  local_48._0_4_ = MODE_BUTTON_POS[uVar11].x + -2;
                  local_48._4_4_ = local_10[0x62990].top;
                  local_40 = local_10[0x62990].right;
                  local_3c = MODE_BUTTON_POS[uVar11].y + -1;
                  lVar14 = DisplayInterface::colorRed;
                  if (local_8->enemyShot + 2.0 <= local_24) {
                    lVar14 = GetHealthColorDim((float)local_34);
                  }
                  DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)local_34,
                                      (tagRECT *)local_48,lVar14,DisplayInterface::colorBlack);
                  if (*plVar31 == DisplayInterface::colorGreen) {
                    *plVar31 = DisplayInterface::colorWhite;
                  }
                }
                if (local_24 < (float)plVar31[4] + 2.0) {
                  local_58.left = MODE_BUTTON_POS[uVar11].x + -2;
                  local_58.top = MODE_BUTTON_POS[uVar11].y + 1;
                  local_58.right = local_10[0x62990].right;
                  local_58.bottom = local_10[0x62990].bottom;
                  DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)local_60.y,&local_58,
                                      DisplayInterface::colorDkBlue,DisplayInterface::colorBlack);
                  if (*plVar31 == DisplayInterface::colorGreen) {
                    *plVar31 = DisplayInterface::colorWhite;
                  }
                }
                spriteZ = local_18;
              }
              if (local_10[0x629c0].bottom != 0) {
                Foreground_Color = *plVar31;
                DrawSprite(DisplayInterface::currentBuffer,local_10[0x629c0].bottom,
                           MODE_BUTTON_POS[uVar11].x,MODE_BUTTON_POS[uVar11].y,0x40005);
              }
            }
            local_10 = local_10 + 1;
            uVar11 = uVar11 + 1;
            plVar31 = plVar31 + 6;
          } while (uVar11 < 9);
        }
        else {
          this->menuMode = MENU_UNIT_PANEL;
          iVar13 = MENU_ITEM[iVar10].minSlot;
          iVar10 = MENU_ITEM[iVar10].maxSlot;
          Foreground_Color = DisplayInterface::colorWhite;
          local_60.y = iVar13;
          DrawSprite(DisplayInterface::currentBuffer,MENU_ITEM[this->currentItem].index,
                     TITLE_BUTTON_POS.x + 2,lVar14,0x40005);
          local_8 = (GameObject *)0x0;
          local_14 = (GameObject *)(iVar10 - iVar13);
          if (-1 < (int)local_14) {
            local_10 = (tagRECT *)&this->modeButton[0].color;
            local_2c = &MODE_BUTTON_RECT[0].right;
            do {
              pGVar12 = Team::GetSlot(local_20._4_4_,(int)&local_8->_padding_ + local_60.y);
              if (pGVar12 != (GameObject *)0x0) {
                cVar8 = (**(code **)(pGVar12->_padding_ + 0x38))();
                if ((cVar8 == '\0') || (pGVar12->isCargo != false)) {
                  local_9 = '\0';
                }
                else {
                  local_9 = '\x01';
                  if (*BUTTON_MAP[(int)local_8] != '\0') {
                    StartGASEvent("mnu_next.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0)
                    ;
                    if (command_controls.cmd_multi == '\0') {
                      SelectOne(this,pGVar12);
                    }
                    else {
                      SelectAdd(this,pGVar12);
                    }
                    GameObject::SetCommand(pGVar12,CMD_SELECT);
                  }
                }
                pGVar19 = local_8;
                spriteZ = local_18 + 0.1;
                local_48._0_4_ = MODE_BUTTON_POS[(int)local_8].x + -2;
                local_48._4_4_ = local_2c[-1];
                local_40 = *local_2c;
                local_3c = MODE_BUTTON_POS[(int)local_8].y + -1;
                fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
                local_34 = (Scanner *)(float)fVar32;
                lVar14 = DisplayInterface::colorRed;
                if (pGVar12->enemyShot + 2.0 <= local_24) {
                  lVar14 = GetHealthColorDim((float)local_34);
                }
                DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)local_34,
                                    (tagRECT *)local_48,lVar14,DisplayInterface::colorBlack);
                local_58.left = MODE_BUTTON_POS[(int)pGVar19].x + -2;
                local_58.top = MODE_BUTTON_POS[(int)pGVar19].y + 1;
                local_58.right = *local_2c;
                local_58.bottom = local_2c[1];
                fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
                DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)fVar32,&local_58,
                                    DisplayInterface::colorDkBlue,DisplayInterface::colorBlack);
                spriteZ = local_18;
                (((ModeButton *)((int)local_10 + -4))->field0_0x0).unit = pGVar12;
                lVar14 = DisplayInterface::colorYellow;
                if ((pGVar12->isSelected == false) &&
                   (lVar14 = DisplayInterface::colorWhite, local_9 == '\0')) {
                  lVar14 = DisplayInterface::colorGrey;
                }
                local_10->left = lVar14;
                if (local_9 != '\0') {
                  DrawSprite(DisplayInterface::currentBuffer,NUM_KEY[(int)pGVar19].index,
                             MODE_BUTTON_POS[(int)pGVar19].x + -4,MODE_BUTTON_POS[(int)pGVar19].y,
                             0x60001);
                }
                if (pGVar12->nameIndex == 0) {
                  pcVar34 = pGVar12->name;
                  if (pcVar34 != (char *)0x0) {
                    Font_Set_Foreground(Default_Font,local_10->left);
                    Font_Print_String(Default_Font,DisplayInterface::currentBuffer,
                                      MODE_BUTTON_POS[(int)pGVar19].x,
                                      MODE_BUTTON_POS[(int)pGVar19].y -
                                      Default_Font->char_height / 2,pcVar34);
                  }
                }
                else {
                  Foreground_Color = local_10->left;
                  DrawSprite(DisplayInterface::currentBuffer,pGVar12->nameIndex,
                             MODE_BUTTON_POS[(int)pGVar19].x,MODE_BUTTON_POS[(int)pGVar19].y,0x40005
                            );
                }
              }
              local_8 = (GameObject *)((int)&local_8->_padding_ + 1);
              local_2c = local_2c + 4;
              local_10 = (tagRECT *)((int)local_10 + 0x18);
            } while ((int)local_8 <= (int)local_14);
          }
        }
        goto LAB_004c72e3;
      }
      this->menuMode = MENU_NAV_PANEL;
      if (this->selectNum < 1) {
        lVar14 = TITLE_BUTTON_POS.x + 2;
        iVar10 = MENU_ITEM[this->currentItem].index;
        iVar13 = TITLE_BUTTON_POS.y;
LAB_004c66c2:
        Foreground_Color = DisplayInterface::colorWhite;
        DrawSprite(DisplayInterface::currentBuffer,iVar10,lVar14,iVar13,0x40005);
      }
      else {
        pGVar12 = GameObject::GetObj(this->selectList[0]);
        spriteZ = local_18 + 0.1;
        local_48._0_4_ = 10;
        local_48._4_4_ = 10;
        local_3c = TITLE_BUTTON_POS.y + -1;
        local_40 = 0x9c;
        fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
        local_14 = (GameObject *)(float)fVar32;
        lVar14 = DisplayInterface::colorRed;
        if (pGVar12->enemyShot + 2.0 <= local_24) {
          lVar14 = GetHealthColorDim((float)local_14);
        }
        DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)local_14,(tagRECT *)local_48,
                            lVar14,DisplayInterface::colorBlack);
        local_58.top = TITLE_BUTTON_POS.y + 1;
        local_58.left = 10;
        local_58.right = 0x9c;
        local_58.bottom = 0x12;
        fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
        DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)fVar32,&local_58,
                            DisplayInterface::colorDkBlue,DisplayInterface::colorBlack);
        spriteZ = local_18;
        iVar10 = pGVar12->nameIndex;
        if (iVar10 != 0) {
          lVar14 = TITLE_BUTTON_POS.x;
          iVar13 = 0xe;
          goto LAB_004c66c2;
        }
        pcVar34 = pGVar12->name;
        if (pcVar34 != (char *)0x0) {
          Font_Set_Foreground(Default_Font,DisplayInterface::colorWhite);
          Font_Print_String(Default_Font,DisplayInterface::currentBuffer,TITLE_BUTTON_POS.x,
                            (0x1c - Default_Font->char_height) / 2,pcVar34);
        }
      }
      local_8 = (GameObject *)0x0;
      local_10 = (tagRECT *)&this->modeButton[0].color;
      do {
        pGVar12 = Team::GetSlot(local_20._4_4_,(int)((int)&local_8->_padding_ + 3));
        if (pGVar12 != (GameObject *)0x0) {
          if (*BUTTON_MAP[(int)local_8] != '\0') {
            StartGASEvent("mnu_clik.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
            if (this->selectNum < 1) {
              GameObject::SetTarget(local_28,pGVar12);
              this->currentItem = -1;
              this->itemSelected = 0;
            }
            else {
              BroadcastCommand(this,CMD_GO,pGVar12);
              SelectNone(this);
            }
          }
          ptVar29 = local_10;
          (((ModeButton *)((int)local_10 + -4))->field0_0x0).unit = pGVar12;
          lVar14 = DisplayInterface::colorGrey;
          if (((pGVar12->obj->flags & 0x200) == 0) &&
             (pGVar19 = GameObject::GetObj(local_28->targetHandle),
             lVar14 = DisplayInterface::colorYellow, pGVar12 != pGVar19)) {
            lVar14 = DisplayInterface::colorWhite;
          }
          pGVar19 = local_8;
          ptVar29->left = lVar14;
          DrawSprite(DisplayInterface::currentBuffer,NUM_KEY[(int)local_8].index,
                     MODE_BUTTON_POS[(int)local_8].x + -4,MODE_BUTTON_POS[(int)local_8].y,0x60001);
          if (pGVar12->nameIndex == 0) {
            pcVar34 = pGVar12->name;
            if (pcVar34 != (char *)0x0) {
              Font_Set_Foreground(Default_Font,local_10->left);
              Font_Print_String(Default_Font,DisplayInterface::currentBuffer,
                                MODE_BUTTON_POS[(int)pGVar19].x,
                                MODE_BUTTON_POS[(int)pGVar19].y - Default_Font->char_height / 2,
                                pcVar34);
            }
          }
          else {
            Foreground_Color = local_10->left;
            DrawSprite(DisplayInterface::currentBuffer,pGVar12->nameIndex,
                       MODE_BUTTON_POS[(int)pGVar19].x,MODE_BUTTON_POS[(int)pGVar19].y,0x40005);
          }
        }
        local_8 = (GameObject *)((int)&local_8->_padding_ + 1);
        local_10 = (tagRECT *)((int)local_10 + 0x18);
      } while ((int)local_8 < 10);
      goto LAB_004c72e3;
    }
    this->menuMode = MENU_TARGET_PANEL;
    if (this->selectNum < 1) {
      lVar14 = TITLE_BUTTON_POS.x + 2;
      iVar10 = MENU_ITEM[this->currentItem].index;
      iVar13 = TITLE_BUTTON_POS.y;
LAB_004c60f2:
      Foreground_Color = DisplayInterface::colorWhite;
      DrawSprite(DisplayInterface::currentBuffer,iVar10,lVar14,iVar13,0x40005);
    }
    else {
      pGVar12 = GameObject::GetObj(this->selectList[0]);
      spriteZ = local_18 + 0.1;
      local_48._0_4_ = 10;
      local_48._4_4_ = 10;
      local_3c = TITLE_BUTTON_POS.y + -1;
      local_40 = 0x9c;
      fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
      local_14 = (GameObject *)(float)fVar32;
      lVar14 = DisplayInterface::colorRed;
      if (pGVar12->enemyShot + 2.0 <= local_24) {
        lVar14 = GetHealthColorDim((float)local_14);
      }
      DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)local_14,(tagRECT *)local_48,lVar14
                          ,DisplayInterface::colorBlack);
      local_58.top = TITLE_BUTTON_POS.y + 1;
      local_58.left = 10;
      local_58.right = 0x9c;
      local_58.bottom = 0x12;
      fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
      DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)fVar32,&local_58,
                          DisplayInterface::colorDkBlue,DisplayInterface::colorBlack);
      spriteZ = local_18;
      iVar10 = pGVar12->nameIndex;
      if (iVar10 != 0) {
        lVar14 = TITLE_BUTTON_POS.x;
        iVar13 = 0xe;
        goto LAB_004c60f2;
      }
      pcVar34 = pGVar12->name;
      if (pcVar34 != (char *)0x0) {
        Font_Set_Foreground(Default_Font,DisplayInterface::colorWhite);
        Font_Print_String(Default_Font,DisplayInterface::currentBuffer,TITLE_BUTTON_POS.x,
                          (0x1c - Default_Font->char_height) / 2,pcVar34);
      }
    }
    if (this->scanTimer < local_24) {
      this->targetNum = 0;
      this->scanTimer = local_24 + 1e+30;
      local_34 = local_28->scanner;
      if (local_34 != (Scanner *)0x0) {
        pfVar20 = (float *)(**(code **)(local_28->_padding_ + 0xc))();
        pSVar7 = local_34;
        local_64 = *pfVar20;
        local_60 = *(tagPOINT *)(pfVar20 + 1);
        Range::Search(GameObject::objectRange,(double)local_64,(double)pfVar20[2],
                      (double)local_34->range,(Range_Search_Results *)(local_a4 + 0x14));
        local_34 = (Scanner *)(pSVar7->range * pSVar7->range);
LAB_004c629c:
        bVar9 = Range_Search_Results::Get_Next_Object
                          ((Range_Search_Results *)(local_a4 + 0x14),&local_2c);
        if (bVar9) {
          pGVar12 = GameObject::GetObj(*local_2c);
          if ((pGVar12 != (GameObject *)0x0) && ((pGVar12->obj->flags & 1) == 0)) {
            piVar24 = &pGVar12->_padding_;
            iVar10 = (**(code **)*piVar24)();
            if (((*(int *)(iVar10 + 0x28) == 6) ||
                ((iVar10 = (**(code **)*piVar24)(), *(int *)(iVar10 + 0x28) == 1 ||
                 (iVar10 = (**(code **)*piVar24)(), *(int *)(iVar10 + 0x28) == 2)))) &&
               (iVar10 = (**(code **)(*piVar24 + 4))(), iVar10 != 0)) {
              iVar10 = (**(code **)(*piVar24 + 4))();
              bVar9 = Team::EnemyP(local_20._4_4_,iVar10);
              if (bVar9) {
                pVVar21 = (VECTOR_3D *)(**(code **)(*piVar24 + 0xc))();
                VVar6.y = (float)local_60.x;
                VVar6.x = local_64;
                VVar6.z = (float)local_60.y;
                fVar33 = Dist3D_Squared(*pVVar21,VVar6);
                if (fVar33 <= (float)local_34) {
                  iVar10 = 0;
                  if (0 < this->targetNum) {
                    do {
                      if (fVar33 < *(float *)(local_a4 + iVar10 * 4 + -0x28)) break;
                      iVar10 = iVar10 + 1;
                    } while (iVar10 < this->targetNum);
                    if (9 < iVar10) goto LAB_004c629c;
                  }
                  if (9 < this->targetNum) {
                    this->targetNum = 9;
                  }
                  iVar13 = this->targetNum;
                  if (iVar10 < iVar13) {
                    piVar24 = this->targetList + iVar13;
                    do {
                      iVar18 = piVar24[-1];
                      *(undefined4 *)(local_a4 + iVar13 * 4 + -0x28) =
                           *(undefined4 *)(local_a4 + iVar13 * 4 + -0x2c);
                      *piVar24 = iVar18;
                      iVar13 = iVar13 + -1;
                      piVar24 = piVar24 + -1;
                    } while (iVar10 < iVar13);
                  }
                  plVar31 = local_2c;
                  *(float *)(local_a4 + iVar10 * 4 + -0x28) = fVar33;
                  this->targetList[iVar10] = *plVar31;
                  this->targetNum = this->targetNum + 1;
                }
              }
            }
          }
          goto LAB_004c629c;
        }
      }
    }
    local_8 = (GameObject *)0x0;
    if (0 < this->targetNum) {
      local_20 = (double)CONCAT44(&this->modeButton[0].color,(undefined4)local_20);
      local_2c = this->targetList;
      local_10 = (tagRECT *)&MODE_BUTTON_RECT[0].right;
      do {
        pGVar12 = GameObject::GetObj(*local_2c);
        if (pGVar12 != (GameObject *)0x0) {
          pGVar12->illumination = 1.0;
          if (*BUTTON_MAP[(int)local_8] != '\0') {
            StartGASEvent("mnu_clik.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
            if (this->selectNum < 1) {
              GameObject::SetTarget(local_28,pGVar12);
              this->currentItem = -1;
              this->itemSelected = 0;
            }
            else {
              BroadcastCommand(this,CMD_ATTACK,pGVar12);
              SelectNone(this);
            }
          }
          pGVar19 = local_8;
          spriteZ = local_18 + 0.1;
          local_48._0_4_ = MODE_BUTTON_POS[(int)local_8].x + -2;
          local_48._4_4_ = local_10[-1].bottom;
          local_40 = local_10->left;
          local_3c = MODE_BUTTON_POS[(int)local_8].y + -1;
          fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
          local_14 = (GameObject *)(float)fVar32;
          lVar14 = DisplayInterface::colorRed;
          if (pGVar12->enemyShot + 2.0 <= local_24) {
            lVar14 = GetHealthColorDim((float)local_14);
          }
          DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)local_14,(tagRECT *)local_48,
                              lVar14,DisplayInterface::colorBlack);
          local_58.left = MODE_BUTTON_POS[(int)pGVar19].x + -2;
          local_58.top = MODE_BUTTON_POS[(int)pGVar19].y + 1;
          local_58.right = local_10->left;
          local_58.bottom = local_10->top;
          fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
          DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)fVar32,&local_58,
                              DisplayInterface::colorDkBlue,DisplayInterface::colorBlack);
          spriteZ = local_18;
          *(GameObject **)((int)local_20._4_4_ + -4) = pGVar12;
          lVar14 = DisplayInterface::colorGrey;
          if (((pGVar12->obj->flags & 0x200) == 0) &&
             (pGVar22 = GameObject::GetObj(local_28->targetHandle),
             lVar14 = DisplayInterface::colorYellow, pGVar12 != pGVar22)) {
            lVar14 = DisplayInterface::colorWhite;
          }
          *(long *)local_20._4_4_ = lVar14;
          DrawSprite(DisplayInterface::currentBuffer,NUM_KEY[(int)pGVar19].index,
                     MODE_BUTTON_POS[(int)pGVar19].x + -4,MODE_BUTTON_POS[(int)pGVar19].y,0x60001);
          if (pGVar12->nameIndex == 0) {
            pcVar34 = pGVar12->name;
            if (pcVar34 != (char *)0x0) {
              Font_Set_Foreground(Default_Font,*(long *)local_20._4_4_);
              Font_Print_String(Default_Font,DisplayInterface::currentBuffer,
                                MODE_BUTTON_POS[(int)pGVar19].x,
                                MODE_BUTTON_POS[(int)pGVar19].y - Default_Font->char_height / 2,
                                pcVar34);
            }
          }
          else {
            Foreground_Color = *(long *)local_20._4_4_;
            DrawSprite(DisplayInterface::currentBuffer,pGVar12->nameIndex,
                       MODE_BUTTON_POS[(int)pGVar19].x,MODE_BUTTON_POS[(int)pGVar19].y,0x40005);
          }
        }
        local_8 = (GameObject *)((int)&local_8->_padding_ + 1);
        local_2c = local_2c + 1;
        local_10 = local_10 + 1;
        local_20 = (double)CONCAT44((int)local_20._4_4_ + 0x18,(undefined4)local_20);
      } while ((int)local_8 < this->targetNum);
    }
    goto LAB_004c72e3;
  }
  this->menuMode = MENU_DEFENSE_PANEL;
  if (this->selectNum < 1) {
    lVar14 = TITLE_BUTTON_POS.x + 2;
    iVar10 = MENU_ITEM[this->currentItem].index;
    iVar13 = TITLE_BUTTON_POS.y;
LAB_004c5b47:
    Foreground_Color = DisplayInterface::colorWhite;
    DrawSprite(DisplayInterface::currentBuffer,iVar10,lVar14,iVar13,0x40005);
  }
  else {
    pGVar12 = GameObject::GetObj(this->selectList[0]);
    spriteZ = local_18 + 0.1;
    local_48._0_4_ = 10;
    local_48._4_4_ = 10;
    local_3c = TITLE_BUTTON_POS.y + -1;
    local_40 = 0x9c;
    fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
    local_14 = (GameObject *)(float)fVar32;
    lVar14 = DisplayInterface::colorRed;
    if (pGVar12->enemyShot + 2.0 <= local_24) {
      lVar14 = GetHealthColorDim((float)local_14);
    }
    DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)local_14,(tagRECT *)local_48,lVar14,
                        DisplayInterface::colorBlack);
    local_58.top = TITLE_BUTTON_POS.y + 1;
    local_58.left = 10;
    local_58.right = 0x9c;
    local_58.bottom = 0x12;
    fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
    DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)fVar32,&local_58,
                        DisplayInterface::colorDkBlue,DisplayInterface::colorBlack);
    spriteZ = local_18;
    iVar10 = pGVar12->nameIndex;
    if (iVar10 != 0) {
      lVar14 = TITLE_BUTTON_POS.x;
      iVar13 = 0xe;
      goto LAB_004c5b47;
    }
    pcVar34 = pGVar12->name;
    if (pcVar34 != (char *)0x0) {
      Font_Set_Foreground(Default_Font,DisplayInterface::colorWhite);
      Font_Print_String(Default_Font,DisplayInterface::currentBuffer,TITLE_BUTTON_POS.x,
                        (0x1c - Default_Font->char_height) / 2,pcVar34);
    }
  }
  this_00 = local_20._4_4_;
  this->targetNum = 0;
  pGVar12 = Team::GetSlot(local_20._4_4_,1);
  if (pGVar12 != (GameObject *)0x0) {
    iVar10 = GameObject::GetHandle(pGVar12);
    this->targetList[this->targetNum] = iVar10;
    this->targetNum = this->targetNum + 1;
  }
  pGVar12 = Team::GetSlot(this_00,2);
  if (pGVar12 != (GameObject *)0x0) {
    iVar10 = GameObject::GetHandle(pGVar12);
    this->targetList[this->targetNum] = iVar10;
    this->targetNum = this->targetNum + 1;
  }
  pGVar12 = Team::GetSlot(this_00,3);
  if (pGVar12 != (GameObject *)0x0) {
    iVar10 = GameObject::GetHandle(pGVar12);
    this->targetList[this->targetNum] = iVar10;
    this->targetNum = this->targetNum + 1;
  }
  pGVar12 = Team::GetSlot(this_00,4);
  if (pGVar12 != (GameObject *)0x0) {
    iVar10 = GameObject::GetHandle(pGVar12);
    this->targetList[this->targetNum] = iVar10;
    this->targetNum = this->targetNum + 1;
  }
  iVar10 = 0;
  if (0 < GameObject::objectiveCount) {
    do {
      if (9 < this->targetNum) break;
      pGVar12 = GameObject::objectiveList[iVar10];
      bVar9 = GameObject::FriendP(local_28,pGVar12);
      if (bVar9) {
        iVar18 = GameObject::GetHandle(pGVar12);
        iVar13 = this->targetNum;
        iVar25 = 0;
        if (0 < iVar13) {
          piVar24 = this->targetList;
          do {
            if (*piVar24 == iVar18) break;
            iVar25 = iVar25 + 1;
            piVar24 = piVar24 + 1;
          } while (iVar25 < this->targetNum);
        }
        if (iVar13 <= iVar25) {
          this->targetList[iVar13] = iVar18;
          this->targetNum = this->targetNum + 1;
        }
      }
      iVar10 = iVar10 + 1;
    } while (iVar10 < GameObject::objectiveCount);
  }
  iVar10 = 0x2d;
  do {
    if (9 < this->targetNum) break;
    pGVar12 = Team::GetSlot(local_20._4_4_,iVar10);
    if (pGVar12 != (GameObject *)0x0) {
      local_34 = (Scanner *)pGVar12->enemyShot;
      fVar33 = Get_TimeLocal();
      if (fVar33 < (float)local_34 + 10.0) {
        iVar18 = GameObject::GetHandle(pGVar12);
        iVar13 = this->targetNum;
        iVar25 = 0;
        if (0 < iVar13) {
          piVar24 = this->targetList;
          do {
            if (*piVar24 == iVar18) break;
            iVar25 = iVar25 + 1;
            piVar24 = piVar24 + 1;
          } while (iVar25 < this->targetNum);
        }
        if (iVar13 <= iVar25) {
          this->targetList[iVar13] = iVar18;
          this->targetNum = this->targetNum + 1;
        }
      }
    }
    iVar10 = iVar10 + 1;
  } while (iVar10 < 0x50);
  local_10 = (tagRECT *)0x0;
  if (0 < this->targetNum) {
    local_20 = (double)CONCAT44(&this->modeButton[0].color,(undefined4)local_20);
    local_2c = this->targetList;
    local_8 = (GameObject *)&MODE_BUTTON_RECT[0].right;
    do {
      pGVar12 = GameObject::GetObj(*local_2c);
      if (pGVar12 != (GameObject *)0x0) {
        pGVar12->illumination = 1.0;
        if (*BUTTON_MAP[(int)local_10] != '\0') {
          StartGASEvent("mnu_clik.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
          if (this->selectNum < 1) {
            GameObject::SetTarget(local_28,pGVar12);
            this->currentItem = -1;
            this->itemSelected = 0;
          }
          else {
            BroadcastCommand(this,CMD_DEFEND,pGVar12);
            SelectNone(this);
          }
        }
        ptVar29 = local_10;
        spriteZ = local_18 + 0.1;
        local_48._0_4_ = MODE_BUTTON_POS[(int)local_10].x + -2;
        local_48._4_4_ = local_8[-1].ownerHandle;
        local_40 = local_8->_padding_;
        local_3c = MODE_BUTTON_POS[(int)local_10].y + -1;
        fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
        local_14 = (GameObject *)(float)fVar32;
        lVar14 = DisplayInterface::colorRed;
        if (pGVar12->enemyShot + 2.0 <= local_24) {
          lVar14 = GetHealthColorDim((float)local_14);
        }
        DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)local_14,(tagRECT *)local_48,
                            lVar14,DisplayInterface::colorBlack);
        local_58.left = MODE_BUTTON_POS[(int)ptVar29].x + -2;
        local_58.top = MODE_BUTTON_POS[(int)ptVar29].y + 1;
        local_58.right = local_8->_padding_;
        local_58.bottom = local_8->_padding_;
        fVar32 = (float10)(**(code **)(pGVar12->_padding_ + 0x1c))();
        DrawHorizontalGauge(DisplayInterface::currentBuffer,(float)fVar32,&local_58,
                            DisplayInterface::colorDkBlue,DisplayInterface::colorBlack);
        spriteZ = local_18;
        *(GameObject **)((int)local_20._4_4_ + -4) = pGVar12;
        lVar14 = DisplayInterface::colorGrey;
        if (((pGVar12->obj->flags & 0x200) == 0) &&
           (pGVar19 = GameObject::GetObj(local_28->targetHandle),
           lVar14 = DisplayInterface::colorYellow, pGVar12 != pGVar19)) {
          lVar14 = DisplayInterface::colorWhite;
        }
        *(long *)local_20._4_4_ = lVar14;
        DrawSprite(DisplayInterface::currentBuffer,NUM_KEY[(int)ptVar29].index,
                   MODE_BUTTON_POS[(int)ptVar29].x + -4,MODE_BUTTON_POS[(int)ptVar29].y,0x60001);
        if (pGVar12->nameIndex == 0) {
          pcVar34 = pGVar12->name;
          if (pcVar34 != (char *)0x0) {
            Font_Set_Foreground(Default_Font,*(long *)local_20._4_4_);
            Font_Print_String(Default_Font,DisplayInterface::currentBuffer,
                              MODE_BUTTON_POS[(int)ptVar29].x,
                              MODE_BUTTON_POS[(int)ptVar29].y - Default_Font->char_height / 2,
                              pcVar34);
          }
        }
        else {
          Foreground_Color = *(long *)local_20._4_4_;
          DrawSprite(DisplayInterface::currentBuffer,pGVar12->nameIndex,
                     MODE_BUTTON_POS[(int)ptVar29].x,MODE_BUTTON_POS[(int)ptVar29].y,0x40005);
        }
      }
      local_10 = (tagRECT *)((int)&local_10->left + 1);
      local_2c = local_2c + 1;
      local_8 = (GameObject *)&local_8->_padding_;
      local_20 = (double)CONCAT44((int)local_20._4_4_ + 0x18,(undefined4)local_20);
    } while ((int)local_10 < this->targetNum);
  }
LAB_004c72e3:
  GameObject::SetObjective(local_28,View_Record.Current_View == OVER_VIEW);
  return;
}
