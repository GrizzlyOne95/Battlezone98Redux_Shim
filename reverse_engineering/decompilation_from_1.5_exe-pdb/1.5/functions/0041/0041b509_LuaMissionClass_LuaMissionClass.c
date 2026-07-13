/*
 * Entry: 0041b509
 * Name: LuaMissionClass::LuaMissionClass
 * Namespace: LuaMissionClass
 * Signature: LuaMissionClass * LuaMissionClass(LuaMissionClass * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LuaMissionClass * __thiscall LuaMissionClass::LuaMissionClass(LuaMissionClass *this,char *param_1)

{
  AiMissionClass::AiMissionClass((AiMissionClass *)this,param_1);
  *(undefined ***)this = &_vftable_;
  return this;
}
