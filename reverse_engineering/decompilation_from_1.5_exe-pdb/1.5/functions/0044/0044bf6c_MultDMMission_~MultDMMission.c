/*
 * Entry: 0044bf6c
 * Name: MultDMMission::~MultDMMission
 * Namespace: MultDMMission
 * Signature: void ~MultDMMission(MultDMMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MultDMMission::~MultDMMission(MultDMMission *this)

{
  this->_padding_ = (int)&_vftable_;
  if (this->pathSpawn != (PathSpawn *)0x0) {
    (**(code **)this->pathSpawn->_padding_)(1);
  }
  if (this->multEvent != (MultDMEvent *)0x0) {
    (**(code **)this->multEvent->_padding_)(1);
  }
  LuaMission::~LuaMission((LuaMission *)this);
  return;
}
