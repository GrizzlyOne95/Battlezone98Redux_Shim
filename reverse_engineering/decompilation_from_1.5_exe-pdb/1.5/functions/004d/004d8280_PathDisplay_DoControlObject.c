/*
 * Entry: 004d8280
 * Name: PathDisplay::DoControlObject
 * Namespace: PathDisplay
 * Signature: void DoControlObject(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::DoControlObject(PathDisplay *this)

{
  int *piVar1;
  GameObject *pGVar2;
  int iVar3;
  _OBJ76 *p_Var4;
  MAT_3D *pMVar5;
  VECTOR_3D *unaff_EBX;
  VECTOR_3D *unaff_ESI;
  MAT_3D *pMVar6;
  float fVar7;
  MAT_3D local_b4;
  MAT_3D local_74;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  float local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  GameObject *local_18;
  GameObject *local_14;
  VECTOR_3D local_10;
  
  pGVar2 = GameObjectHandle::GetObj(this->taskWhoHandle);
  local_14 = pGVar2;
  if (command_controls.cmd_click[0] == '\0') {
    if ((command_controls.cmd_hold[0] == '\0') || (pGVar2 == (GameObject *)0x0)) {
      if (((command_controls.cmd_hold[1] != '\0') && (pGVar2 != (GameObject *)0x0)) &&
         (((this->grabOffset).x != (float)DisplayInterface::mousePos.x ||
          ((this->grabOffset).z != (float)DisplayInterface::mousePos.y)))) {
        (this->grabOffset).x = (float)DisplayInterface::mousePos.x;
        (this->grabOffset).z = (float)DisplayInterface::mousePos.y;
        (**(code **)(this->_padding_ + 0x24))
                  (DisplayInterface::mousePos.x,DisplayInterface::mousePos.y,&local_10,&local_10.z);
        local_10.y = 0.0;
        p_Var4 = pGVar2->obj;
        local_34 = 0;
        local_18 = (GameObject *)&p_Var4->transform;
        local_30 = 0x3f800000;
        local_2c = 0;
        local_28 = local_10.x - (float)(p_Var4->transform).posit_x;
        local_24 = 0;
        local_20 = local_10.z - (float)(p_Var4->transform).posit_z;
        pMVar5 = Build_Orthogonal_Matrix(&local_b4,unaff_ESI,unaff_EBX);
        pGVar2 = local_18;
        local_74.posit_x = *(double *)&local_18->_padding_;
        pMVar6 = &local_74;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          pMVar6->right_x = pMVar5->right_x;
          pMVar5 = (MAT_3D *)&pMVar5->right_y;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
        }
        local_74.posit_y = *(double *)&pGVar2->_padding_;
        local_74.posit_z = *(double *)&pGVar2->_padding_;
        GameObject::SetTransform(local_14,&local_74);
        pGVar2 = local_14;
      }
    }
    else if (((this->grabOffset).x != (float)DisplayInterface::mousePos.x) ||
            ((this->grabOffset).z != (float)DisplayInterface::mousePos.y)) {
      (this->grabOffset).x = (float)DisplayInterface::mousePos.x;
      (this->grabOffset).z = (float)DisplayInterface::mousePos.y;
      (**(code **)(this->_padding_ + 0x24))
                (DisplayInterface::mousePos.x,DisplayInterface::mousePos.y,&local_10,&local_10.z);
      local_10.x = local_10.x - (float)this->cellColorMap[0];
      local_10.z = local_10.z - (float)this->cellColorMap[1];
      local_10.y = Terrain_FindFloor((double)local_10.x,(double)local_10.z);
      p_Var4 = (_OBJ76 *)(**(code **)(pGVar2->_padding_ + 0x30))();
      iVar3 = IsCraft(p_Var4);
      if ((iVar3 != 0) && (pGVar2[1]._padding_ == 0)) {
        fVar7 = Terrain_FindFloor((double)(local_10.x - 5.0),(double)(local_10.z - 5.0));
        if (local_10.y < fVar7) {
          local_10.y = fVar7;
        }
        fVar7 = Terrain_FindFloor((double)(local_10.x - 5.0),(double)(local_10.z + 5.0));
        if (local_10.y < fVar7) {
          local_10.y = fVar7;
        }
        fVar7 = Terrain_FindFloor((double)(local_10.x + 5.0),(double)(local_10.z + 5.0));
        if (local_10.y < fVar7) {
          local_10.y = fVar7;
        }
        fVar7 = Terrain_FindFloor((double)(local_10.x + 5.0),(double)(local_10.z - 5.0));
        if (local_10.y < fVar7) {
          local_10.y = fVar7;
        }
        local_10.y = local_10.y + 10.0;
      }
      GameObject::SetOrigin(pGVar2,&local_10);
      iVar3 = (**(code **)(pGVar2->_padding_ + 0x30))();
      if (*(int *)(iVar3 + 0xac) == 2) {
        terrainChanged = 1;
      }
    }
  }
  else {
    local_18 = pGVar2;
    SelectObject(this,&local_14);
    pGVar2 = local_14;
    if (local_14 == (GameObject *)0x0) {
      iVar3 = 0;
    }
    else {
      iVar3 = GameObject::GetHandle(local_14);
    }
    this->taskWhoHandle = iVar3;
    if (pGVar2 != (GameObject *)0x0) {
      local_10.x = (float)(pGVar2->obj->transform).posit_x;
      iVar3 = this->_padding_;
      local_10.z = (float)(pGVar2->obj->transform).posit_z;
      (this->grabOffset).x = (float)DisplayInterface::mousePos.x;
      (this->grabOffset).z = (float)DisplayInterface::mousePos.y;
      piVar1 = this->cellColorMap + 1;
      (**(code **)(iVar3 + 0x24))
                (DisplayInterface::mousePos.x,DisplayInterface::mousePos.y,this->cellColorMap,piVar1
                );
      this->cellColorMap[0] = (int)((float)this->cellColorMap[0] - local_10.x);
      *piVar1 = (int)((float)*piVar1 - local_10.z);
      if ((pGVar2 == local_18) && (fVar7 = Get_TimeLocal(), fVar7 < (float)(this->prevMousePos).y))
      {
        EditObjectName(this);
      }
    }
    fVar7 = Get_TimeLocal();
    (this->prevMousePos).y = (long)(fVar7 + 0.5);
  }
  if (command_controls.cmd_delete != '\0') {
    if (pGVar2 == (GameObject *)0x0) {
      return;
    }
    (**(code **)(pGVar2->_padding_ + 0x10))();
    local_14 = (GameObject *)0x0;
    this->taskWhoHandle = 0;
    pGVar2 = (GameObject *)0x0;
  }
  if ((pGVar2 != (GameObject *)0x0) &&
     (DrawObject(this,pGVar2,true,DisplayInterface::colorWhite),
     command_controls.cmd_hold[1] != '\0')) {
    local_1c = spriteZ;
    spriteZ = 0.3;
    (**(code **)(this->_padding_ + 0x20))
              ((float)(pGVar2->obj->transform).posit_x,(float)(pGVar2->obj->transform).posit_z,
               &local_14,&local_18);
    Graphic_Line(DisplayInterface::currentBuffer,(long)local_14,(long)local_18,
                 DisplayInterface::mousePos.x,DisplayInterface::mousePos.y,
                 DisplayInterface::colorWhite,SOLID_PIXELS);
    spriteZ = local_1c;
  }
  return;
}
