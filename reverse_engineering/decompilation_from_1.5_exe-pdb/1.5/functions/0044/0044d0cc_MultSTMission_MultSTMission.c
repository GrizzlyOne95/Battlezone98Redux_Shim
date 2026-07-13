/*
 * Entry: 0044d0cc
 * Name: MultSTMission::MultSTMission
 * Namespace: MultSTMission
 * Signature: MultSTMission * MultSTMission(MultSTMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MultSTMission * __thiscall MultSTMission::MultSTMission(MultSTMission *this)

{
  LuaMission::LuaMission((LuaMission *)this);
  this->_padding_ = (int)&_vftable_;
  this->pathSpawn = (PathSpawn *)0x0;
  king_of_the_hill_game = 0;
  stratgy_game = 1;
  mission_stop = 0;
  this->recently_killed = false;
  this->killed = 0;
  this->camera = false;
  this->dwLastTime = 0;
  SetAIControl(2,false);
  return this;
}
