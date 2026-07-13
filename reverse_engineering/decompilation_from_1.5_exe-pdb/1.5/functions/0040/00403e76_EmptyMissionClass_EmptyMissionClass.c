/*
 * Entry: 00403e76
 * Name: EmptyMissionClass::EmptyMissionClass
 * Namespace: EmptyMissionClass
 * Signature: EmptyMissionClass * EmptyMissionClass(EmptyMissionClass * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

EmptyMissionClass * __thiscall
EmptyMissionClass::EmptyMissionClass(EmptyMissionClass *this,char *param_1)

{
  AiMissionClass::AiMissionClass((AiMissionClass *)this,param_1);
  *(undefined ***)this = &_vftable_;
  return this;
}
