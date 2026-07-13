/*
 * Entry: 004160c3
 * Name: Inst4XMission::Inst4XMission
 * Namespace: Inst4XMission
 * Signature: Inst4XMission * Inst4XMission(Inst4XMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Inst4XMission * __thiscall Inst4XMission::Inst4XMission(Inst4XMission *this)

{
  LuaMission::LuaMission((LuaMission *)this);
  this->pathSpawn = (PathSpawn *)0x0;
  this->_padding_ = (int)&_vftable_;
  return this;
}
