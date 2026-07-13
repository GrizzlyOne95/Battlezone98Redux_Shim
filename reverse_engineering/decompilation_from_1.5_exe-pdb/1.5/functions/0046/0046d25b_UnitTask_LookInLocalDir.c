/*
 * Entry: 0046d25b
 * Name: UnitTask::LookInLocalDir
 * Namespace: UnitTask
 * Signature: void LookInLocalDir(UnitTask * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::LookInLocalDir(UnitTask *this,VECTOR_3D *param_1)

{
  Craft *pCVar1;
  VHCL_CONTROL *pVVar2;
  VECTOR_3D *pVVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  VECTOR_3D local_20;
  float local_14;
  float fStack_10;
  float fStack_c;
  VHCL_CONTROL *local_8;
  
  local_8 = &this->me->vhcl->control;
  pVVar3 = Vector_Rotate(&local_20,param_1,(MAT_3D *)(this->me->_padding_ + 0x20));
  pCVar1 = this->me;
  local_14 = pVVar3->x;
  fStack_10 = pVVar3->y;
  fStack_c = pVVar3->z;
  (this->gotoDir).x = local_14;
  (this->gotoDir).y = fStack_10;
  (this->gotoDir).z = fStack_c;
  fVar4 = (float10)fpatan((float10)param_1->x,(float10)param_1->z);
  fVar5 = Clamp((float)((-((float10)(float)pCVar1->_padding_ * (float10)this->omegaFactor) - fVar4)
                       * (float10)this->steerFactor),-1.0,1.0);
  pVVar2 = local_8;
  local_8->steer = fVar5;
  fVar7 = 1.0;
  fVar6 = -1.0;
  fVar5 = TimeStep();
  fVar5 = Clamp(fVar5 * param_1->y * 4.0 + this->pitch,fVar6,fVar7);
  this->pitch = fVar5;
  pVVar2->pitch = fVar5;
  return;
}
