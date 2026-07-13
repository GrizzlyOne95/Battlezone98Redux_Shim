/*
 * Entry: 00403ed0
 * Name: EmptyMission::~EmptyMission
 * Namespace: EmptyMission
 * Signature: void ~EmptyMission(EmptyMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EmptyMission::~EmptyMission(EmptyMission *this)

{
  *(undefined ***)this = &_vftable_;
  AiMission::~AiMission((AiMission *)this);
  return;
}
