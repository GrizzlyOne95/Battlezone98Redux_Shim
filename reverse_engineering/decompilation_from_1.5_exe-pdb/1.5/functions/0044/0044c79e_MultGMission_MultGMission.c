/*
 * Entry: 0044c79e
 * Name: MultGMission::MultGMission
 * Namespace: MultGMission
 * Signature: MultGMission * MultGMission(MultGMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MultGMission * __thiscall MultGMission::MultGMission(MultGMission *this)

{
  AiMission::AiMission((AiMission *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
