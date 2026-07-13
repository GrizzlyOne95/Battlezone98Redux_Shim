/*
 * Entry: 004118d3
 * Name: MUFFriend::InitWait
 * Namespace: MUFFriend
 * Signature: void InitWait(MUFFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MUFFriend::InitWait(MUFFriend *this)

{
  CoastTask *pCVar1;
  SitTask *this_00;
  
  RecyclerProcess::TryToDeploy((RecyclerProcess *)this);
  if (*(float *)(*(int *)&this->field_0x1c + 0x124) <= 10.0) {
    this_00 = operator_new(0x138);
    if (this_00 != (SitTask *)0x0) {
      pCVar1 = (CoastTask *)SitTask::SitTask(this_00,*(Craft **)&this->field_0x1c);
      goto LAB_00411924;
    }
  }
  else {
    pCVar1 = operator_new(0x138);
    if (pCVar1 != (CoastTask *)0x0) {
      pCVar1 = CoastTask::CoastTask(pCVar1,*(Craft **)&this->field_0x1c);
      goto LAB_00411924;
    }
  }
  pCVar1 = (CoastTask *)0x0;
LAB_00411924:
  *(CoastTask **)&this->field_0x30 = pCVar1;
  return;
}
