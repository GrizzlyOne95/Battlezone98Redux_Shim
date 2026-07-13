/*
 * Entry: 0046f4db
 * Name: UnitTask::GoTowards
 * Namespace: UnitTask
 * Signature: void GoTowards(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::GoTowards(UnitTask *this)

{
  VEHICLE *pVVar1;
  int iVar2;
  VECTOR_2D *pVVar3;
  VECTOR_3D_LONG VVar4;
  VECTOR_2D VVar5;
  VECTOR_2D VVar6;
  bool bVar7;
  VECTOR_3D *pVVar8;
  float *pfVar9;
  long lVar10;
  VHCL_CONTROL *pVVar11;
  float10 fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  VECTOR_3D local_3c;
  VECTOR_3D local_30;
  float local_24;
  float local_20;
  float local_1c;
  VECTOR_2D local_18;
  float local_10;
  VHCL_CONTROL *local_c;
  MAT_3D *local_8;
  
  pVVar1 = this->me->vhcl;
  iVar2 = this->me->_padding_;
  local_8 = (MAT_3D *)(iVar2 + 0x20);
  local_c = &pVVar1->control;
  VVar4.y._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar2 + 0x50) >> 0x20);
  VVar4._0_12_ = *(undefined1 (*) [12])(iVar2 + 0x48);
  VVar4.z._0_4_ = (int)*(undefined8 *)(iVar2 + 0x58);
  VVar4.z._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar2 + 0x58) >> 0x20);
  Floor_GetFloor(VVar4,&local_10,&local_30);
  iVar2 = this->me->_padding_;
  fVar13 = Clamp((*(float *)(iVar2 + 0x38) * local_30.x +
                 *(float *)(iVar2 + 0x3c) * local_30.y + *(float *)(iVar2 + 0x40) * local_30.z) *
                 -1.0,-1.0,1.0);
  (pVVar1->control).pitch = fVar13;
  if (((this->me->vhcl->flags & 4) == 0) && (this->plan->pathType != BAD_PATH)) {
    bVar7 = false;
  }
  else {
    bVar7 = true;
  }
  pVVar8 = GotoForce(this,&local_3c,bVar7);
  (this->gotoForce).x = pVVar8->x;
  (this->gotoForce).y = pVVar8->y;
  (this->gotoForce).z = pVVar8->z;
  pVVar8 = Vector_Unrotate(&local_3c,&this->gotoForce,local_8);
  local_24 = pVVar8->x;
  local_20 = pVVar8->y;
  local_1c = pVVar8->z;
  pVVar11 = local_c;
  if (0.0001 < local_1c * local_1c + local_24 * local_24 + local_20 * local_20) {
    if (this->planPoint == 0) {
      pfVar9 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
      pVVar3 = this->plan->points;
      fVar13 = *pfVar9;
      local_3c.y = pfVar9[1];
      fVar16 = pfVar9[2];
      local_18.z = fVar16;
      local_18.x = fVar13;
      fVar15 = pVVar3[this->planPoint].z;
      fVar14 = pVVar3[this->planPoint].x;
      local_3c.x = fVar13;
      local_3c.z = fVar16;
    }
    else {
      pVVar3 = this->plan->points + this->planPoint;
      fVar16 = pVVar3[-1].z;
      fVar13 = pVVar3[-1].x;
      fVar15 = pVVar3->z;
      fVar14 = pVVar3->x;
    }
    VVar5.z = fVar15;
    VVar5.x = fVar14;
    VVar6.z = fVar16;
    VVar6.x = fVar13;
    local_18 = Vec2D_Subtract(VVar5,VVar6);
    fVar12 = (float10)fpatan((float10)local_8->right_x * (float10)local_18.x +
                             (float10)local_8->right_z * (float10)local_18.z,
                             (float10)local_8->front_x * (float10)local_18.x +
                             (float10)local_8->front_z * (float10)local_18.z);
    fVar13 = Clamp((float)-(((float10)(float)this->me->_padding_ * (float10)this->omegaFactor +
                            fVar12) * (float10)this->steerFactor),-1.0,1.0);
    local_c->steer = fVar13;
    pVVar11 = local_c;
  }
  local_8 = (MAT_3D *)0x3f800000;
  if (ABS(pVVar11->steer) == 1.0) {
    local_8 = (MAT_3D *)0x3e800000;
  }
  else if (0.7 < ABS(pVVar11->steer)) {
    local_8 = (MAT_3D *)0x3f000000;
  }
  local_c = (VHCL_CONTROL *)-(float)local_8;
  fVar13 = Clamp(this->braccelFactor * local_1c,(float)local_c,(float)local_8);
  pVVar11->braccel = fVar13;
  fVar13 = Clamp(this->strafeFactor * local_24,(float)local_c,(float)local_8);
  pVVar11->strafe = fVar13;
  fVar13 = pVVar11->braccel;
  if ((NAN(fVar13) || 1.0 < fVar13 == (fVar13 == 1.0)) || (0.8 <= local_30.y)) {
    lVar10 = 0;
  }
  else {
    lVar10 = 1;
  }
  pVVar11->turbo = lVar10;
  return;
}
