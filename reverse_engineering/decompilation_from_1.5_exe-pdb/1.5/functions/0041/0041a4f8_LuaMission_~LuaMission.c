/*
 * Entry: 0041a4f8
 * Name: LuaMission::~LuaMission
 * Namespace: LuaMission
 * Signature: void ~LuaMission(LuaMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LuaMission::~LuaMission(LuaMission *this)

{
  this->_padding_ = (int)&_vftable_;
  if (this->L != (lua_State *)0x0) {
    lua_close(this->L);
  }
  AiMission::~AiMission((AiMission *)this);
  return;
}
