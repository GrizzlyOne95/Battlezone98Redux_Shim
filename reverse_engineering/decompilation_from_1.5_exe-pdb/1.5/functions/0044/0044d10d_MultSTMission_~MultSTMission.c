/*
 * Entry: 0044d10d
 * Name: MultSTMission::~MultSTMission
 * Namespace: MultSTMission
 * Signature: void ~MultSTMission(MultSTMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MultSTMission::~MultSTMission(MultSTMission *this)

{
  this->_padding_ = (int)&_vftable_;
  if (this->pathSpawn != (PathSpawn *)0x0) {
    (**(code **)this->pathSpawn->_padding_)(1);
  }
  LuaMission::~LuaMission((LuaMission *)this);
  return;
}
