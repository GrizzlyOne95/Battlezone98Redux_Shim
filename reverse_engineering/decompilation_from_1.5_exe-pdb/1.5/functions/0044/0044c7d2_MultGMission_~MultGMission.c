/*
 * Entry: 0044c7d2
 * Name: MultGMission::~MultGMission
 * Namespace: MultGMission
 * Signature: void ~MultGMission(MultGMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MultGMission::~MultGMission(MultGMission *this)

{
  *(undefined ***)this = &_vftable_;
  AiMission::~AiMission((AiMission *)this);
  return;
}
