/*
 * Entry: 0046d31a
 * Name: UnitTask::DoFollow
 * Namespace: UnitTask
 * Signature: void DoFollow(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::DoFollow(UnitTask *this)

{
  VEHICLE *pVVar1;
  int iVar2;
  _OBJ76 *p_Var3;
  Craft *pCVar4;
  GameObject *pGVar5;
  VECTOR_3D_LONG VVar6;
  VECTOR_3D VVar7;
  VECTOR_3D VVar8;
  MAT_3D *pMVar9;
  VECTOR_3D *pVVar10;
  float *pfVar11;
  VHCL_CONTROL *pVVar12;
  float fVar13;
  VECTOR_3D local_48;
  VECTOR_3D local_3c;
  VECTOR_3D local_30;
  VECTOR_3D local_24;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  VHCL_CONTROL *local_8;
  
  pVVar1 = this->me->vhcl;
  pVVar12 = &pVVar1->control;
  local_8 = pVVar12;
  fVar13 = Get_Time();
  if ((((this->lastStopped + 10.0 <= fVar13) || (0.1 <= ABS((pVVar1->control).braccel))) ||
      (0.1 <= ABS(pVVar12->steer))) ||
     ((0.1 <= ABS((pVVar1->control).strafe) || (0.1 <= ABS((pVVar1->control).pitch))))) {
    iVar2 = this->me->_padding_;
    VVar6.y._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar2 + 0x50) >> 0x20);
    VVar6._0_12_ = *(undefined1 (*) [12])(iVar2 + 0x48);
    VVar6.z._0_4_ = (int)*(undefined8 *)(iVar2 + 0x58);
    VVar6.z._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar2 + 0x58) >> 0x20);
    Floor_GetFloor(VVar6,&local_c,&local_30);
    iVar2 = this->me->_padding_;
    fVar13 = Clamp((*(float *)(iVar2 + 0x38) * local_30.x +
                   *(float *)(iVar2 + 0x40) * local_30.z + *(float *)(iVar2 + 0x3c) * local_30.y) *
                   -1.0,-1.0,1.0);
    (pVVar1->control).pitch = fVar13;
    p_Var3 = this->him->obj;
    local_24.x = (p_Var3->transform).front_x;
    pMVar9 = &p_Var3->transform;
    local_24.y = (p_Var3->transform).front_y;
    local_24.z = (p_Var3->transform).front_z;
    VVar8.x = (p_Var3->transform).front_x;
    VVar8.y = (p_Var3->transform).front_y;
    VVar8.z = (p_Var3->transform).front_z;
    local_18 = pMVar9->right_x;
    local_14 = (p_Var3->transform).right_y;
    local_10 = (p_Var3->transform).right_z;
    VVar7.x = pMVar9->right_x;
    VVar7.y = pMVar9->right_y;
    VVar7.z = pMVar9->right_z;
    pVVar10 = CombineVectors(&local_3c,this->followDx,VVar7,this->followDz,VVar8);
    local_24.x = pVVar10->x;
    local_24.y = pVVar10->y;
    local_24.z = pVVar10->z;
    pfVar11 = (float *)(**(code **)(this->him->_padding_ + 0xc))();
    local_18 = *pfVar11;
    local_14 = pfVar11[1];
    local_10 = pfVar11[2];
    local_48.x = local_24.x + local_18;
    local_48.y = local_24.y + local_14;
    local_48.z = local_24.z + local_10;
    local_3c.x = local_48.x;
    local_3c.y = local_48.y;
    local_3c.z = local_48.z;
    pVVar10 = FollowForce(&local_24,(GameObject *)this->me,&local_48,this->avoidObj);
    pCVar4 = this->me;
    local_3c.x = pVVar10->x;
    local_3c.y = pVVar10->y;
    local_3c.z = pVVar10->z;
    (this->gotoForce).x = local_3c.x;
    (this->gotoForce).y = local_3c.y;
    (this->gotoForce).z = local_3c.z;
    pVVar10 = Vector_Unrotate(&local_3c,&this->gotoForce,(MAT_3D *)(pCVar4->_padding_ + 0x20));
    pGVar5 = this->him;
    local_24.x = pVVar10->x;
    local_24.y = pVVar10->y;
    local_24.z = pVVar10->z;
    if (5.0 <= (pGVar5->euler).v_mag) {
      local_3c.x = (pGVar5->euler).v.x;
      local_3c.y = (pGVar5->euler).v.y;
      local_3c.z = (pGVar5->euler).v.z;
      local_14 = local_3c.x;
      local_10 = local_3c.z;
      (**(code **)(this->me->_padding_ + 0x88))(local_3c.x,local_3c.z);
    }
    else {
      p_Var3 = pGVar5->obj;
      local_3c.x = (p_Var3->transform).front_x;
      local_3c.y = (p_Var3->transform).front_y;
      local_3c.z = (p_Var3->transform).front_z;
      local_14 = local_3c.x;
      local_10 = local_3c.z;
      (**(code **)(this->me->_padding_ + 0x88))(local_3c.x,local_3c.z);
      if (local_24.z * local_24.z + local_24.x * local_24.x + local_24.y * local_24.y < 100.0) {
        CleanStuck(this);
        fVar13 = Get_Time();
        this->lastStopped = fVar13;
      }
    }
    fVar13 = Clamp(this->braccelFactor * local_24.z,-1.0,1.0);
    pVVar12 = local_8;
    local_8->braccel = fVar13;
    fVar13 = Clamp(this->strafeFactor * local_24.x,-1.0,1.0);
    pVVar12->strafe = fVar13;
    if (pVVar12->braccel == 1.0) {
      pVVar12->turbo = 1;
    }
    else {
      pVVar12->turbo = 0;
    }
  }
  else {
    CleanStuck(this);
    (pVVar1->control).braccel = 0.0;
    pVVar12->steer = 0.0;
    (pVVar1->control).strafe = 0.0;
    (pVVar1->control).pitch = 0.0;
  }
  return;
}
