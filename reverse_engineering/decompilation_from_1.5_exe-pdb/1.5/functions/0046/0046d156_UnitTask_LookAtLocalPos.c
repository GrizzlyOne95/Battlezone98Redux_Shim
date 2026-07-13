/*
 * Entry: 0046d156
 * Name: UnitTask::LookAtLocalPos
 * Namespace: UnitTask
 * Signature: void LookAtLocalPos(UnitTask * this, VECTOR_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::LookAtLocalPos(UnitTask *this,VECTOR_3D *param_1,VECTOR_3D *param_2)

{
  VHCL_CONTROL *pVVar1;
  VECTOR_3D *pVVar2;
  float10 fVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  VECTOR_3D local_30;
  VECTOR_3D local_24;
  VECTOR_3D local_18;
  VHCL_CONTROL *local_c;
  MAT_3D *local_8;
  
  local_8 = (MAT_3D *)(this->me->_padding_ + 0x20);
  local_c = &this->me->vhcl->control;
  pVVar2 = Normalize_Vector(&local_24,param_1);
  local_18.x = pVVar2->x;
  local_18.y = pVVar2->y;
  local_18.z = pVVar2->z;
  pVVar2 = Vector_Rotate(&local_30,&local_18,local_8);
  local_24.x = pVVar2->x;
  local_24.y = pVVar2->y;
  local_24.z = pVVar2->z;
  (this->gotoDir).x = local_24.x;
  (this->gotoDir).y = local_24.y;
  (this->gotoDir).z = local_24.z;
  fVar3 = ((float10)param_2->z * (float10)param_1->x - (float10)param_1->z * (float10)param_2->x) /
          ((float10)param_1->z * (float10)param_1->z + (float10)param_1->x * (float10)param_1->x);
  fVar4 = (float10)fpatan((float10)param_1->x,(float10)param_1->z);
  fVar5 = Clamp((float)(((fVar3 - (float10)(float)this->me->_padding_) * (float10)this->omegaFactor
                        - fVar4) * (float10)this->steerFactor + (float10)this->omegaScale * fVar3),
                -1.0,1.0);
  pVVar1 = local_c;
  local_c->steer = fVar5;
  fVar7 = 1.0;
  fVar6 = -1.0;
  fVar5 = TimeStep();
  fVar5 = Clamp(fVar5 * local_18.y * 4.0 + this->pitch,fVar6,fVar7);
  this->pitch = fVar5;
  pVVar1->pitch = fVar5;
  return;
}
