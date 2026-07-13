/*
 * Entry: 0040d0fc
 * Name: SLFFriend::InitWait
 * Namespace: SLFFriend
 * Signature: void InitWait(SLFFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SLFFriend::InitWait(SLFFriend *this)

{
  CoastTask *pCVar1;
  SitTask *this_00;
  
  ArmoryProcess::TryToDeploy((ArmoryProcess *)this);
  if (*(float *)(*(int *)&this->field_0x1c + 0x124) <= 10.0) {
    this_00 = operator_new(0x138);
    if (this_00 != (SitTask *)0x0) {
      pCVar1 = (CoastTask *)SitTask::SitTask(this_00,*(Craft **)&this->field_0x1c);
      goto LAB_0040d14d;
    }
  }
  else {
    pCVar1 = operator_new(0x138);
    if (pCVar1 != (CoastTask *)0x0) {
      pCVar1 = CoastTask::CoastTask(pCVar1,*(Craft **)&this->field_0x1c);
      goto LAB_0040d14d;
    }
  }
  pCVar1 = (CoastTask *)0x0;
LAB_0040d14d:
  *(CoastTask **)&this->field_0x2c = pCVar1;
  return;
}
