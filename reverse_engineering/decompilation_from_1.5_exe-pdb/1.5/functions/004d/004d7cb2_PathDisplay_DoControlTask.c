/*
 * Entry: 004d7cb2
 * Name: PathDisplay::DoControlTask
 * Namespace: PathDisplay
 * Signature: void DoControlTask(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall PathDisplay::DoControlTask(PathDisplay *this)

{
  char **ppcVar1;
  bool bVar2;
  GameObject *this_00;
  VECTOR_3D *pVVar3;
  VECTOR_3D *pVVar4;
  float fVar5;
  AiMission *pAVar6;
  long lVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  AiCmdInfo *pAVar11;
  GameObject *unaff_EDI;
  AiCmdInfo *pAVar12;
  char *_Format;
  GameObject *pGVar13;
  AiCmdInfo local_bc;
  GameObject *local_a4;
  int local_a0;
  PathDisplay *local_9c;
  int local_98;
  GameObject *local_94;
  int local_90;
  GameObject *local_8c;
  char local_88 [12];
  undefined1 local_7c [116];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_7c;
  local_9c = this;
  this_00 = GameObjectHandle::GetObj(this->taskWhoHandle);
  local_94 = this_00;
  local_a4 = GameObjectHandle::GetObj((int)(this->taskWhere).x);
  if (command_controls.cmd_click[1] != '\0') {
    if (((this_00 != (GameObject *)0x0) && (this->taskPath != (AiPath *)0x0)) &&
       ((local_a4 != (GameObject *)0x0 || (((this->taskWhere).y != 0.0 || (this->dblTime != -1.0))))
       )) {
      local_bc.priority = 1;
      if ((local_a4 == (GameObject *)0x0) && (&this->taskPath[-1].me.field_0x4 < (undefined1 *)0x2))
      {
        this->taskPath = (AiPath *)0x3;
      }
      local_bc.what = (AiCommand)this->taskPath;
      local_bc.where = (AiPath *)(this->taskWhere).y;
      if (local_bc.where == (AiPath *)0x0) {
        if (this->dblTime == -1.0) {
          if (local_a4 == (GameObject *)0x0) {
            local_bc.who = 0;
          }
          else {
            local_bc.who = GameObject::GetHandle(local_a4);
          }
          local_8c = operator_new(0x1c);
          if (local_8c != (GameObject *)0x0) {
            pVVar3 = (VECTOR_3D *)(**(code **)(local_a4->_padding_ + 0xc))();
            goto LAB_004d7dbc;
          }
        }
        else {
          local_bc.who = 0;
          local_8c = operator_new(0x1c);
          if (local_8c != (GameObject *)0x0) {
            pVVar3 = (VECTOR_3D *)&(this->taskWhere).z;
LAB_004d7dbc:
            pVVar4 = (VECTOR_3D *)(**(code **)(this_00->_padding_ + 0xc))();
            local_bc.where = AiPath::AiPath((AiPath *)local_8c,pVVar4,pVVar3);
            goto LAB_004d7dd6;
          }
        }
        local_bc.where = (AiPath *)0x0;
      }
      else {
        local_bc.who = 0;
      }
LAB_004d7dd6:
      local_bc.param = 0;
      GameObject::SetCommand(this_00,&local_bc);
    }
    this->taskPath = (AiPath *)0x0;
    this->dblTime = -1.0;
    (this->taskWhere).x = 0.0;
    local_a4 = (GameObject *)0x0;
    (this->taskWhere).y = 0.0;
  }
  if ((command_controls.cmd_click[0] != '\0') &&
     (bVar2 = InVerbArea(&DisplayInterface::mousePos), !bVar2)) {
    if ((this_00 == (GameObject *)0x0) || (this->taskPath == (AiPath *)0x0)) {
      local_8c = this_00;
      SelectObject(this,&local_94);
      this_00 = local_94;
      if (local_94 == (GameObject *)0x0) {
        this->taskWhoHandle = 0;
      }
      else {
        iVar8 = GameObject::GetHandle(local_94);
        this->taskWhoHandle = iVar8;
        if ((this_00 == local_8c) &&
           (fVar5 = Get_TimeLocal(), fVar5 < (float)(this->prevMousePos).y)) {
          EditObjectName(this);
        }
      }
      fVar5 = Get_TimeLocal();
      (this->prevMousePos).y = (long)(fVar5 + 0.5);
    }
    else {
      SelectObject(this,&local_a4);
      if (local_a4 == (GameObject *)0x0) {
        (this->taskWhere).x = 0.0;
        SelectPath(this,(AiPath **)&(this->taskWhere).y,(int *)&local_8c);
        if ((this->taskWhere).y == 0.0) {
          (**(code **)(this->_padding_ + 0x24))(DisplayInterface::mousePos.x);
          this->dblTime = 0.0;
        }
      }
      else {
        fVar5 = (float)GameObject::GetHandle(local_a4);
        (this->taskWhere).x = fVar5;
      }
    }
  }
  if ((command_controls.cmd_delete != '\0') && (this_00 != (GameObject *)0x0)) {
    if ((((this_00->curCmd).what != CMD_NONE) && ((this_00->curCmd).priority == 1)) &&
       (((this_00->nextCmd).what == CMD_NONE || ((this_00->nextCmd).priority == 0)))) {
      pAVar11 = &this_00->curCmd;
      pAVar12 = &local_bc;
      for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
        pAVar12->priority = pAVar11->priority;
        pAVar11 = (AiCmdInfo *)&pAVar11->what;
        pAVar12 = (AiCmdInfo *)&pAVar12->what;
      }
      GameObject::ClearCommand(this_00);
      GameObject::SetCommand(this_00,&local_bc);
      this = local_9c;
    }
    if (this_00->aiProcess != (AiProcess *)0x0) {
      (**(code **)this_00->aiProcess->_padding_)();
    }
    pGVar13 = this_00;
    pAVar6 = AiMission::GetCurrent();
    AiProcess::Attach(pAVar6,pGVar13);
  }
  DrawPaths(this,false);
  local_9c = (PathDisplay *)(DisplayInterface::currentBuffer->Height + -0x3c);
  if (this_00 == (GameObject *)0x0) {
    return;
  }
  DrawObject(this,this_00,true,DisplayInterface::colorWhite);
  GetObjectName((GameObject *)cmdText[(this_00->curCmd).what]);
  sprintf(local_88," Subject: Name (%s) Current Command (%s) Next Command (%s)");
  DrawCommand(this,this_00,&this_00->curCmd,DisplayInterface::colorGreen);
  DrawCommand(this,this_00,&this_00->nextCmd,DisplayInterface::colorDkGreen);
  local_8c = (GameObject *)this_00->aiProcess;
  DisplayInterface::SetTextPos
            (((DisplayInterface::currentBuffer->Pane).x1 -
             (DisplayInterface::currentBuffer->Pane).x0) + -0x96,0x14);
  if (local_8c == (GameObject *)0x0) {
    EmptyDrawState(unaff_EDI);
  }
  else {
    (**(code **)(local_8c->_padding_ + 0x14))();
  }
  Graphic_Text(DisplayInterface::currentBuffer,0xf,(long)local_9c,&local_98,&local_90,local_88,
               DisplayInterface::textFont,DisplayInterface::colorWhite,DisplayInterface::colorBlack,
               0,0,0);
  iVar10 = local_90 + 2;
  Graphic_Text(DisplayInterface::currentBuffer,0xf,iVar10,&local_98,&local_90," Set Command:",
               DisplayInterface::textFont,DisplayInterface::colorWhite,DisplayInterface::colorBlack,
               0,0,0);
  btnX1 = local_98 + 5;
  local_94 = (GameObject *)0x0;
  iVar8 = local_98;
  iVar9 = local_90;
  btnY0 = iVar10;
  btnX0 = btnX1;
  local_a0 = btnX1;
  do {
    if ((local_94 != (GameObject *)0x1) && (((int)local_94 < 10 || (0xe < (int)local_94)))) {
      local_9c = (PathDisplay *)DisplayInterface::colorWhite;
      local_8c = (GameObject *)DisplayInterface::colorBlack;
      if ((GameObject *)this->taskPath != local_94) {
        local_8c = (GameObject *)DisplayInterface::colorWhite;
        local_9c = (PathDisplay *)DisplayInterface::colorBlack;
      }
      ppcVar1 = cmdText + (int)local_94;
      lVar7 = Font_Get_String_Length(DisplayInterface::textFont,*ppcVar1);
      if (DisplayInterface::currentBuffer->Width < lVar7 + local_a0) {
        local_a0 = btnX0;
        iVar10 = local_90 + 2;
        if (btnX1 < local_98) {
          btnX1 = local_98;
        }
      }
      Graphic_Text(DisplayInterface::currentBuffer,local_a0,iVar10,&local_98,&local_90,*ppcVar1,
                   DisplayInterface::textFont,(long)local_8c,(long)local_9c,0,0,0);
      if ((((command_controls.cmd_click[0] != '\0') && (local_a0 <= DisplayInterface::mousePos.x))
          && (DisplayInterface::mousePos.x < local_98)) &&
         ((iVar10 <= DisplayInterface::mousePos.y && (DisplayInterface::mousePos.y < local_90)))) {
        this->taskPath = (AiPath *)local_94;
      }
      local_a0 = local_98 + 5;
      iVar8 = local_98;
      iVar9 = local_90;
    }
    local_94 = (GameObject *)((int)&local_94->_padding_ + 1);
  } while ((int)local_94 < 0x1b);
  if (btnX1 < iVar8) {
    btnX1 = iVar8;
  }
  btnY1 = iVar9;
  if ((this->taskWhere).y == 0.0) {
    if (this->dblTime != -1.0) {
      sprintf(local_88," Object: Pos X(%f), Z(%f)",(double)(this->taskWhere).z,
              (double)(float)(this->prevMousePos).x);
      goto LAB_004d823c;
    }
    if (local_a4 == (GameObject *)0x0) {
      return;
    }
    GetObjectName(unaff_EDI);
    _Format = " Object: Name (%s)";
  }
  else {
    _Format = " Object: Path (%s)";
  }
  sprintf(local_88,_Format);
LAB_004d823c:
  Graphic_Text(DisplayInterface::currentBuffer,0xf,iVar9 + 2,&local_98,&local_90,local_88,
               DisplayInterface::textFont,DisplayInterface::colorWhite,DisplayInterface::colorBlack,
               0,0,0);
  return;
}
