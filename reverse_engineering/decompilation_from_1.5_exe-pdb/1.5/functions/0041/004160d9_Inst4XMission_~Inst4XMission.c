/*
 * Entry: 004160d9
 * Name: Inst4XMission::~Inst4XMission
 * Namespace: Inst4XMission
 * Signature: void ~Inst4XMission(Inst4XMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Inst4XMission::~Inst4XMission(Inst4XMission *this)

{
  this->_padding_ = (int)&_vftable_;
  if (this->pathSpawn != (PathSpawn *)0x0) {
    (**(code **)this->pathSpawn->_padding_)(1);
  }
  LuaMission::~LuaMission((LuaMission *)this);
  return;
}
