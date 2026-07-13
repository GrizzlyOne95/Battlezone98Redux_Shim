/*
 * Entry: 0040d169
 * Name: SLFEnemy::InitWait
 * Namespace: SLFEnemy
 * Signature: void InitWait(SLFEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SLFEnemy::InitWait(SLFEnemy *this)

{
  bool bVar1;
  CoastTask *pCVar2;
  SitTask *this_00;
  
  bVar1 = ArmoryProcess::TryToDeploy((ArmoryProcess *)this);
  if (*(float *)(*(int *)&this->field_0x1c + 0x124) <= 10.0) {
    this_00 = operator_new(0x138);
    if (this_00 != (SitTask *)0x0) {
      pCVar2 = (CoastTask *)SitTask::SitTask(this_00,*(Craft **)&this->field_0x1c);
      goto LAB_0040d1bd;
    }
  }
  else {
    pCVar2 = operator_new(0x138);
    if (pCVar2 != (CoastTask *)0x0) {
      pCVar2 = CoastTask::CoastTask(pCVar2,*(Craft **)&this->field_0x1c);
      goto LAB_0040d1bd;
    }
  }
  pCVar2 = (CoastTask *)0x0;
LAB_0040d1bd:
  *(CoastTask **)&this->field_0x2c = pCVar2;
  if (!bVar1) {
    *(undefined4 *)&this->field_0x18 = 8;
  }
  return;
}
