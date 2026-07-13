/*
 * Entry: 0044bf3f
 * Name: MultDMMission::MultDMMission
 * Namespace: MultDMMission
 * Signature: MultDMMission * MultDMMission(MultDMMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MultDMMission * __thiscall MultDMMission::MultDMMission(MultDMMission *this)

{
  LuaMission::LuaMission((LuaMission *)this);
  this->_padding_ = (int)&_vftable_;
  this->multEvent = (MultDMEvent *)0x0;
  this->pathSpawn = (PathSpawn *)0x0;
  this->recently_killed = false;
  this->killed = 0;
  this->camera = false;
  SetAIControl(2,false);
  return this;
}
