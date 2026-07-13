/*
 * Entry: 00403ebe
 * Name: EmptyMission::EmptyMission
 * Namespace: EmptyMission
 * Signature: EmptyMission * EmptyMission(EmptyMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

EmptyMission * __thiscall EmptyMission::EmptyMission(EmptyMission *this)

{
  AiMission::AiMission((AiMission *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
