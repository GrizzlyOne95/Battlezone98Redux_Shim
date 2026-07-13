/*
 * Entry: 0041985e
 * Name: OpenODF
 * Namespace: Global
 * Signature: int OpenODF(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl OpenODF(lua_State *param_1)

{
  char *pcVar1;
  ParameterDB *this;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  strncpy(local_18,pcVar1,0x10);
  pcVar1 = strchr(local_18,0x2e);
  if (pcVar1 == (char *)0x0) {
    strncat(local_18,".odf",0x10);
  }
  this = lua_newuserdata(param_1,4);
  if (this != (ParameterDB *)0x0) {
    ParameterDB::ParameterDB(this,local_18);
  }
  lua_getfield(param_1,-10000,"ParameterDB");
  lua_setmetatable(param_1,-2);
  return 1;
}
