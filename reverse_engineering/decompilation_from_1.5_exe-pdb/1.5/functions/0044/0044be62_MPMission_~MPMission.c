/*
 * Entry: 0044be62
 * Name: MPMission::~MPMission
 * Namespace: MPMission
 * Signature: void ~MPMission(MPMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MPMission::~MPMission(MPMission *this)

{
  *(undefined ***)this = &_vftable_;
  AiMission::~AiMission((AiMission *)this);
  return;
}
