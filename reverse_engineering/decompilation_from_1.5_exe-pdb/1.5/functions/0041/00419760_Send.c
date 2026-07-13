/*
 * Entry: 00419760
 * Name: Send
 * Namespace: Global
 * Signature: int Send(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl Send(lua_State *param_1)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  ushort uVar7;
  undefined1 *puVar8;
  char *local_108;
  undefined1 local_104;
  char local_103;
  char local_102 [114];
  undefined1 local_90 [128];
  char local_10 [8];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_90;
  iVar3 = luaL_optinteger(param_1,1,0);
  uVar7 = (ushort)iVar3;
  local_104 = 0x23;
  pcVar4 = lua_tolstring(param_1,2,(uint *)0x0);
  local_103 = *pcVar4;
  local_108 = local_102;
  iVar5 = lua_gettop(param_1);
  iVar3 = 3;
  if (2 < iVar5) {
    do {
      pcVar4 = local_108;
      bVar1 = PackValue(&local_108,local_10,param_1,iVar3);
      if (!bVar1) {
        TraceError("Lua Send packet full at arg %d\n");
        local_108 = pcVar4;
        break;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 <= iVar5);
  }
  puVar8 = &local_104;
  uVar6 = (int)local_108 - (int)puVar8;
  iVar3 = 1;
  uVar2 = Net_GetMyPlayerID();
  iVar3 = Net::Send(Net::dp,uVar2,uVar7,iVar3,puVar8,uVar6);
  lua_pushboolean(param_1,(uint)(iVar3 == 0));
  return 1;
}
