/*
 * Entry: 00419a4d
 * Name: GetODFFloat
 * Namespace: Global
 * Signature: int GetODFFloat(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetODFFloat(lua_State *param_1)

{
  bool bVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 unaff_EBX;
  double dVar6;
  float *pfVar7;
  float fVar8;
  float local_10;
  ParameterDB *local_c;
  char *local_8;
  
  local_c = GetParameterDB(param_1,1);
  if (local_c == (ParameterDB *)0x0) {
    iVar5 = 0;
  }
  else {
    pcVar2 = luaL_optlstring(param_1,2,(char *)0x0,(uint *)0x0);
    local_8 = luaL_checklstring(param_1,3,(uint *)0x0);
    dVar6 = luaL_optnumber(param_1,4,0.0);
    fVar8 = (float)dVar6;
    pfVar7 = &local_10;
    uVar3 = Hash(local_8,0x811c9dc5);
    uVar4 = Hash(pcVar2,0x811c9dc5);
    bVar1 = ParameterDB::Get(local_c,uVar4,uVar3,pfVar7,fVar8);
    lua_pushnumber(param_1,(double)CONCAT44(unaff_EBX,(int)((ulonglong)(double)local_10 >> 0x20)));
    lua_pushboolean(param_1,(uint)bVar1);
    iVar5 = 2;
  }
  return iVar5;
}
