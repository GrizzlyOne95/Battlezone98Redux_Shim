/*
 * Entry: 00410fb7
 * Name: DemoMissionClass::DemoMissionClass
 * Namespace: DemoMissionClass
 * Signature: DemoMissionClass * DemoMissionClass(DemoMissionClass * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DemoMissionClass * __thiscall
DemoMissionClass::DemoMissionClass(DemoMissionClass *this,char *param_1)

{
  AiMissionClass::AiMissionClass((AiMissionClass *)this,param_1);
  *(undefined ***)this = &_vftable_;
  return this;
}
