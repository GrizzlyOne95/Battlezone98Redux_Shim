/*
 * Entry: 0046d084
 * Name: UnitTask::ApplyForce
 * Namespace: UnitTask
 * Signature: void ApplyForce(UnitTask * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::ApplyForce(UnitTask *this,VECTOR_3D *param_1)

{
  Craft *pCVar1;
  VEHICLE *pVVar2;
  float fVar3;
  UnitTask *pUVar4;
  VECTOR_3D *pVVar5;
  float fVar6;
  VECTOR_3D local_24;
  float local_18;
  float fStack_14;
  float local_10;
  UnitTask *local_c;
  float local_8;
  
  (this->gotoForce).x = param_1->x;
  (this->gotoForce).y = param_1->y;
  pCVar1 = this->me;
  (this->gotoForce).z = param_1->z;
  pVVar2 = pCVar1->vhcl;
  fVar6 = ABS((pVVar2->control).steer);
  fVar3 = 1.0;
  if (fVar6 == 1.0) {
    fVar3 = 0.25;
  }
  else if (0.7 < fVar6) {
    fVar3 = 0.5;
  }
  local_c = this;
  pVVar5 = Vector_Unrotate(&local_24,&this->gotoForce,(MAT_3D *)(pCVar1->_padding_ + 0x20));
  pUVar4 = local_c;
  local_8 = -fVar3;
  local_18 = pVVar5->x;
  fStack_14 = pVVar5->y;
  local_10 = pVVar5->z;
  fVar6 = Clamp(local_c->braccelFactor * local_10,local_8,fVar3);
  (pVVar2->control).braccel = fVar6;
  fVar6 = Clamp(pUVar4->strafeFactor * local_18,local_8,fVar3);
  (pVVar2->control).strafe = fVar6;
  (pVVar2->control).turbo = 0;
  return;
}
