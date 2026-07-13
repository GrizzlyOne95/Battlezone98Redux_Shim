/*
 * Entry: 0044be50
 * Name: MPMission::MPMission
 * Namespace: MPMission
 * Signature: MPMission * MPMission(MPMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MPMission * __thiscall MPMission::MPMission(MPMission *this)

{
  AiMission::AiMission((AiMission *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
