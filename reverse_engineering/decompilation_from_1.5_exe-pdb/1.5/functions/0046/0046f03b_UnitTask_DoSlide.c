/*
 * Entry: 0046f03b
 * Name: UnitTask::DoSlide
 * Namespace: UnitTask
 * Signature: void DoSlide(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::DoSlide(UnitTask *this)

{
  Craft *pCVar1;
  VEHICLE *pVVar2;
  _OBJ76 *p_Var3;
  _OBJ76 *p_Var4;
  float fVar5;
  float fVar6;
  float fVar7;
  ActionInfo local_28;
  
  pCVar1 = this->me;
  p_Var3 = (_OBJ76 *)(**(code **)(this->him->_padding_ + 0x30))();
  p_Var4 = (_OBJ76 *)(**(code **)(pCVar1->_padding_ + 0x30))();
  ActionInfo::ActionInfo(&local_28,p_Var4,p_Var3);
  fVar5 = slideSTable[local_28.ring][local_28.my_quad][local_28.his_quad];
  this->skipObj = this->him;
  GoHeading(this,fVar5);
  pVVar2 = this->me->vhcl;
  if (0.2 < (pVVar2->control).braccel) {
    (pVVar2->control).braccel = 1.0;
  }
  pVVar2 = this->me->vhcl;
  fVar7 = 1.0;
  fVar6 = -1.0;
  fVar5 = TimeStep();
  fVar5 = Clamp(fVar5 * (this->targetDir).y * 20.0 + this->pitch,fVar6,fVar7);
  this->pitch = fVar5;
  (pVVar2->control).pitch = fVar5;
  return;
}
