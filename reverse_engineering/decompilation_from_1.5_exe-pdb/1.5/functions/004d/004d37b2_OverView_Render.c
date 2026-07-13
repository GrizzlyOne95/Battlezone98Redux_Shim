/*
 * Entry: 004d37b2
 * Name: OverView::Render
 * Namespace: OverView
 * Signature: void Render(OverView * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OverView::Render(OverView *this)

{
  _OBJ76 *p_Var1;
  tagPOINT tVar2;
  tagRECT tVar3;
  tagPOINT tVar4;
  tagPOINT tVar5;
  tagPOINT tVar6;
  tagPOINT tVar7;
  tagPOINT tVar8;
  long lVar9;
  int iVar10;
  GameObject *pGVar11;
  VECTOR_3D *pVVar12;
  AiCommand AVar13;
  long lVar14;
  MAT_3D *pMVar15;
  CAMERA *unaff_EDI;
  MAT_3D *pMVar16;
  tagPOINT tVar17;
  tagRECT local_34;
  undefined1 local_24 [8];
  float local_1c;
  float local_18;
  VECTOR_3D local_14;
  tagRECT *local_8;
  
  lVar9 = DisplayInterface::mousePos.y;
  lVar14 = DisplayInterface::mousePos.x;
  if (TerrainEditMode != 0) {
    return;
  }
  if ((hudFlags == 0) &&
     (tVar17.y = DisplayInterface::mousePos.y, tVar17.x = DisplayInterface::mousePos.x,
     iVar10 = InsideRect(tVar17,&mapRadar.viewRect), iVar10 != 0)) {
    ControlPanel::SetCommand(&controlPanel,CMD_NONE,(VECTOR_3D *)0x0);
    return;
  }
  tVar4.y = lVar9;
  tVar4.x = lVar14;
  MoveCamera(this,tVar4);
  iVar10 = UserPref_arcadeMode();
  if (iVar10 != 0) {
    if ((_S2 & 1) == 0) {
      _S2 = _S2 | 1;
      pMVar15 = &Identity_Matrix;
      pMVar16 = &mat;
      for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
        pMVar16->right_x = pMVar15->right_x;
        pMVar15 = (MAT_3D *)&pMVar15->right_y;
        pMVar16 = (MAT_3D *)&pMVar16->right_y;
      }
    }
    tVar5.y = DisplayInterface::mousePos.y;
    tVar5.x = DisplayInterface::mousePos.x;
    pGVar11 = ClickedOn(this,tVar5);
    this->who = pGVar11;
    tVar6.y = DisplayInterface::mousePos.y;
    tVar6.x = DisplayInterface::mousePos.x;
    pVVar12 = ScreenToWorld((VECTOR_3D *)(local_24 + 4),tVar6,unaff_EDI);
    local_34.top = (long)pVVar12->x;
    local_34.right = (long)pVVar12->y;
    local_34.bottom = (long)pVVar12->z;
    pVVar12 = &this->where;
    pVVar12->x = (float)local_34.top;
    (this->where).y = (float)local_34.right;
    (this->where).z = (float)local_34.bottom;
    reticle.groundPos = pVVar12;
    if (this->who == (GameObject *)0x0) {
      this->startCommand = CMD_NONE;
      ControlPanel::SetCommand(&controlPanel,this->startCommand,pVVar12);
    }
    else {
      this->startCommand = CMD_SELECT;
      ControlPanel::SetCommand(&controlPanel,this->startCommand,this->who);
    }
    if (select == (GameObject *)0x0) {
      if (((command_controls.cmd_click[0] != '\0') || (command_controls.cmd_click[1] != '\0')) &&
         (select = this->who, select != (GameObject *)0x0)) {
        pMVar15 = &select->obj->transform;
        pMVar16 = &mat;
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          pMVar16->right_x = pMVar15->right_x;
          pMVar15 = (MAT_3D *)&pMVar15->right_y;
          pMVar16 = (MAT_3D *)&pMVar16->right_y;
        }
      }
      goto LAB_004d3c11;
    }
    if (command_controls.cmd_delete == '\0') {
      if (command_controls.cmd_hold[0] == '\0') {
        if (command_controls.cmd_hold[1] != '\0') {
          p_Var1 = select->obj;
          local_14.x = (float)(p_Var1->transform).posit_x;
          local_14.y = (float)(p_Var1->transform).posit_y;
          local_14.z = (float)(p_Var1->transform).posit_z;
          local_34.top = (long)((this->where).x - local_14.x);
          local_34.right = (long)((this->where).y - local_14.y);
          local_34.bottom = (long)((this->where).z - local_14.z);
          local_24._4_4_ = local_34.top;
          local_1c = (float)local_34.right;
          local_18 = (float)local_34.bottom;
          GameObject::SetFrontVector(select,(VECTOR_3D *)(local_24 + 4));
          tVar17 = WorldToScreen(&local_14,DisplayInterface::currentCamera,(float *)0x0);
          Graphic_Line(DisplayInterface::currentBuffer,tVar17.x,tVar17.y,
                       DisplayInterface::mousePos.x,DisplayInterface::mousePos.y,
                       DisplayInterface::colorWhite,SOLID_PIXELS);
          goto LAB_004d3c11;
        }
      }
      else {
        if (command_controls.cmd_hold[1] == '\0') {
          GameObject::SetOrigin(select,&this->where);
          goto LAB_004d3c11;
        }
        GameObject::SetTransform(select,&mat);
      }
    }
    else {
      (**(code **)(select->_padding_ + 0x10))();
    }
    select = (GameObject *)0x0;
    goto LAB_004d3c11;
  }
  tVar7.y = DisplayInterface::mousePos.y;
  tVar7.x = DisplayInterface::mousePos.x;
  pGVar11 = ClickedOn(this,tVar7);
  this->who = pGVar11;
  tVar8.y = DisplayInterface::mousePos.y;
  tVar8.x = DisplayInterface::mousePos.x;
  pVVar12 = ScreenToWorld((VECTOR_3D *)(local_24 + 4),tVar8,unaff_EDI);
  local_34.top = (long)pVVar12->x;
  local_34.right = (long)pVVar12->y;
  local_34.bottom = (long)pVVar12->z;
  reticle.groundPos = &this->where;
  (reticle.groundPos)->x = (float)local_34.top;
  (this->where).y = (float)local_34.right;
  (this->where).z = (float)local_34.bottom;
  if (this->wasDown == 0) {
    if (this->who == (GameObject *)0x0) {
      if (((((reticle.groundPos)->x <= edgeMinX) || (edgeMaxX <= (reticle.groundPos)->x)) ||
          ((this->where).z <= edgeMinZ)) || (edgeMaxZ <= (this->where).z)) {
        this->startCommand = CMD_NONE;
        AVar13 = CMD_NONE;
      }
      else {
        AVar13 = ActionMode::GetCommand(&actionMode,reticle.groundPos);
        this->startCommand = AVar13;
      }
      ControlPanel::SetCommand(&controlPanel,AVar13,&this->where);
    }
    else {
      AVar13 = ActionMode::GetCommand(&actionMode,this->who);
      this->startCommand = AVar13;
      ControlPanel::SetCommand(&controlPanel,AVar13,this->who);
    }
  }
  if (command_controls.cmd_click[1] == '\0') {
    iVar10 = (int)command_controls.cmd_hold[0] + this->wasDown * 2;
    if (iVar10 == 1) {
      AVar13 = this->startCommand;
      (this->downPos).x = (this->where).x;
      (this->downPos).y = (this->where).y;
      (this->downPos).z = (this->where).z;
      if (AVar13 == CMD_SELECT) {
        pGVar11 = this->who;
        if (pGVar11->teamSlot - 0x23U < 10) {
          if (GameObject::userObject != (GameObject *)0x0) {
            GameObject::SetTarget(GameObject::userObject,pGVar11);
          }
        }
        else if (command_controls.cmd_multi == '\0') {
          ControlPanel::SelectOne(&controlPanel,pGVar11);
        }
        else {
          ControlPanel::SelectAdd(&controlPanel,pGVar11);
        }
      }
    }
    else if (iVar10 == 2) {
      AVar13 = this->startCommand;
      if (AVar13 != CMD_NONE) {
        if (this->who == (GameObject *)0x0) {
          ControlPanel::BroadcastCommand(&controlPanel,AVar13,&this->where);
        }
        else {
          ControlPanel::BroadcastCommand(&controlPanel,AVar13,this->who);
        }
        if ((this->startCommand != CMD_SELECT) && (this->startCommand != CMD_NO_DROPOFF))
        goto LAB_004d3bb3;
      }
    }
    else if (iVar10 == 3) {
      tVar17 = WorldToScreen(&this->downPos,DisplayInterface::currentCamera,(float *)0x0);
      tVar2.y = DisplayInterface::mousePos.y;
      tVar2.x = DisplayInterface::mousePos.x;
      local_8 = PointsToRect((tagRECT *)local_24,tVar17,tVar2);
      local_34.left = local_8->left;
      local_34.top = local_8->top;
      local_34.right = local_8->right;
      local_34.bottom = local_8->bottom;
      lVar14 = RectVolume(&local_34);
      if (100 < lVar14) {
        SelectionBox(this,*local_8,DisplayInterface::colorWhite);
        tVar3.top = local_34.top;
        tVar3.left = local_34.left;
        tVar3.right = local_34.right;
        tVar3.bottom = local_34.bottom;
        ControlPanel::SelectRect(&controlPanel,tVar3);
        this->startCommand = CMD_SELECT;
      }
    }
  }
  else {
LAB_004d3bb3:
    ControlPanel::SelectNone(&controlPanel);
  }
  this->wasDown = (int)command_controls.cmd_hold[0];
LAB_004d3c11:
  if ((command_controls.center_player != '\0') && (GameObject::userObject != (GameObject *)0x0)) {
    SetObject(this,GameObject::userObject);
  }
  if ((command_controls.center_recycler != '\0') &&
     (pGVar11 = Team::GetSlot(GameObject::userTeamList,1), pGVar11 != (GameObject *)0x0)) {
    SetObject(this,pGVar11);
  }
  DisplayInterface::cursorIndex = CURSOR_MAP[this->startCommand].index;
  return;
}
