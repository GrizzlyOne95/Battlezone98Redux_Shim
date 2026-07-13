/*
 * Entry: 0046ad95
 * Name: UnitTask::CleanStuck
 * Namespace: UnitTask
 * Signature: void CleanStuck(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::CleanStuck(UnitTask *this)

{
  ulong *puVar1;
  Craft *pCVar2;
  float *pfVar3;
  float fVar4;
  
  fVar4 = Get_Time();
  this->nextStuck = fVar4 + 5.0;
  pfVar3 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
  pCVar2 = this->me;
  (this->lastStuck).x = *pfVar3;
  (this->lastStuck).y = pfVar3[1];
  (this->lastStuck).z = pfVar3[2];
  puVar1 = &pCVar2->vhcl->flags;
  *puVar1 = *puVar1 & 0xfffdffff;
  return;
}
