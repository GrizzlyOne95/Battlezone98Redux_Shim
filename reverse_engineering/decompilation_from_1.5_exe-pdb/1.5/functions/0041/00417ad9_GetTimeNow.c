/*
 * Entry: 00417ad9
 * Name: GetTimeNow
 * Namespace: Global
 * Signature: int GetTimeNow(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTimeNow(lua_State *param_1)

{
  double dVar1;
  DWORD DVar2;
  
  DVar2 = Get_TimeNow();
  dVar1 = (double)(int)DVar2;
  if ((int)DVar2 < 0) {
    dVar1 = dVar1 + 4294967296.0;
  }
  lua_pushnumber(param_1,(double)CONCAT44(DVar2,(int)((ulonglong)dVar1 >> 0x20)));
  return 1;
}
