/*
 * Entry: 0041cb85
 * Name: LuaMission::LuaMission
 * Namespace: LuaMission
 * Signature: LuaMission * LuaMission(LuaMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LuaMission * __thiscall LuaMission::LuaMission(LuaMission *this)

{
  AiMission::AiMission((AiMission *)this);
  this->L = (lua_State *)0x0;
  this->_padding_ = (int)&_vftable_;
  this->started = false;
  Setup(this);
  return this;
}
