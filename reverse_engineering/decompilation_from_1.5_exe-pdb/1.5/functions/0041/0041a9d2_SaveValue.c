/*
 * Entry: 0041a9d2
 * Name: SaveValue
 * Namespace: Global
 * Signature: void SaveValue(_iobuf * param_1, lua_State * param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SaveValue(_iobuf *param_1,lua_State *param_2,int param_3,int param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  MAT_3D *pMVar5;
  VECTOR_3D *pVVar6;
  uint uVar7;
  undefined8 local_10;
  bool local_5;
  
  iVar3 = param_3;
  iVar2 = param_3;
  if (param_3 < 0) {
    iVar2 = lua_gettop(param_2);
    iVar2 = iVar3 + 1 + iVar2;
  }
  iVar3 = lua_type(param_2,iVar2);
  param_3 = CONCAT13((char)iVar3 + '0',(undefined3)param_3);
  out(param_1,(uchar *)((int)&param_3 + 3),1,"type");
  cVar1 = param_3._3_1_ + -0x30;
  param_3 = CONCAT13(cVar1,(undefined3)param_3);
  if (cVar1 == '\0') {
    Trace("nil");
  }
  else if (cVar1 == '\x01') {
    iVar2 = lua_toboolean(param_2,iVar2);
    local_5 = iVar2 != 0;
    pcVar4 = "true";
    if (!local_5) {
      pcVar4 = "false";
    }
    Trace(pcVar4);
    out(param_1,&local_5,1,"b");
  }
  else if (cVar1 == '\x02') {
    iVar2 = GetHandle(param_2,iVar2);
    local_10 = (double)CONCAT44(iVar2,(undefined4)local_10);
    Trace("%08X");
    out(param_1,(int *)((int)&local_10 + 4),4,"h");
  }
  else if (cVar1 == '\x03') {
    local_10 = lua_tonumber(param_2,iVar2);
    Trace("%f");
    out(param_1,(double *)&local_10,8,"f");
  }
  else if (cVar1 == '\x04') {
    pcVar4 = lua_tolstring(param_2,iVar2,(uint *)((int)&local_10 + 4));
    Trace("\"%s\"");
    out(param_1,(int *)((int)&local_10 + 4),4,"l");
    out(param_1,pcVar4,local_10._4_4_,"s");
  }
  else if (cVar1 == '\x05') {
    local_10 = (double)((ulonglong)local_10 & 0xffffffff);
    lua_pushnil(param_2);
    iVar3 = lua_next(param_2,iVar2);
    while (iVar3 != 0) {
      local_10 = (double)CONCAT44(local_10._4_4_ + 1,(undefined4)local_10);
      lua_settop(param_2,-2);
      iVar3 = lua_next(param_2,iVar2);
    }
    out(param_1,(int *)((int)&local_10 + 4),4,"count");
    lua_pushnil(param_2);
    Trace("{");
    param_4 = param_4 + 1;
    iVar3 = lua_next(param_2,iVar2);
    while( true ) {
      if (iVar3 == 0) break;
      Trace("\n%.*s[");
      SaveValue(param_1,param_2,-2,param_4);
      Trace("]=");
      SaveValue(param_1,param_2,-1,param_4);
      lua_settop(param_2,-2);
      iVar3 = lua_next(param_2,iVar2);
    }
    Trace("\n%.*s}");
  }
  else if (cVar1 == '\a') {
    iVar3 = lua_getmetatable(param_2,iVar2);
    if (iVar3 != 0) {
      lua_getfield(param_2,-1,"__type");
      uVar7 = 0x811c9dc5;
      pcVar4 = luaL_checklstring(param_2,-1,(uint *)0x0);
      local_10._4_4_ = Hash(pcVar4,uVar7);
      lua_settop(param_2,-3);
      out(param_1,(ulong *)((int)&local_10 + 4),4,"undeflong");
      if (local_10._4_4_ == 0xe3f3088) {
        pVVar6 = GetVector(param_2,iVar2);
        Trace("{x=%f, y=%f, z=%f}");
        out(param_1,pVVar6,0xc,"undefvector_3d");
      }
      else if (local_10._4_4_ == 0x247e1851) {
        pMVar5 = GetMatrix(param_2,iVar2);
        Trace(
             "{right_x=%f, right_y=%f, right_z=%f, up_x=%f, up_y=%f, up_z=%f, front_x=%f, front_y=%f, front_z=%f, posit_x=%f, posit_y=%f, posit_z=%f}"
             );
        out(param_1,pMVar5,0x40,"undefmat_3d");
      }
    }
  }
  return;
}
