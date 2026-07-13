/*
 * Entry: 0041aee0
 * Name: LuaMission::Update
 * Namespace: LuaMission
 * Signature: void Update(LuaMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall LuaMission::Update(LuaMission *this)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined4 unaff_ESI;
  char *pcVar4;
  char *pcVar5;
  float fVar6;
  lua_State *plVar7;
  char local_58 [64];
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  AiMission::Update((AiMission *)this);
  if (this->L != (lua_State *)0x0) {
    if (user_controls.key != 0) {
      local_18[0] = '\0';
      local_18[1] = 0;
      local_18[2] = '\0';
      local_18[3] = '\0';
      local_18[4] = '\0';
      local_18[5] = '\0';
      local_18[6] = '\0';
      local_18[7] = '\0';
      local_18[8] = '\0';
      local_18[9] = '\0';
      local_18[10] = '\0';
      local_18[0xb] = '\0';
      local_18[0xc] = '\0';
      local_18[0xd] = '\0';
      local_18[0xe] = '\0';
      local_18[0xf] = 0;
      pcVar4 = sGameKeyName[user_controls._0_4_ & 0xff];
      if (pcVar4 == (char *)0x0) {
        if ((user_controls._0_4_ & 0x800) == 0) {
          iVar2 = toupper(user_controls._0_4_ & 0xff);
          local_18[0] = (char)iVar2;
          local_18[1] = 0;
        }
        else {
          builtin_strncpy(local_18,"CapsLock",9);
        }
      }
      else {
        iVar2 = -(int)pcVar4;
        do {
          cVar1 = *pcVar4;
          pcVar4[(int)(local_18 + iVar2)] = cVar1;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
      }
      pcVar4 = "";
      pcVar5 = "Alt+";
      if ((user_controls._0_4_ & 0x400) == 0) {
        pcVar5 = "";
      }
      pcVar3 = "Shift+";
      if ((user_controls._0_4_ & 0x200) == 0) {
        pcVar3 = "";
      }
      if ((user_controls._0_4_ & 0x100) != 0) {
        pcVar4 = "Ctrl+";
      }
      sprintf(local_58,"%s%s%s%s",pcVar4,pcVar3,pcVar5,local_18);
      lua_getfield(this->L,-0x2712,"GameKey");
      iVar2 = lua_type(this->L,-1);
      if (iVar2 == 6) {
        lua_pushstring(this->L,local_58);
        plVar7 = this->L;
        pcVar4 = "Lua script GameKey error:\n%s";
        iVar2 = lua_pcall(plVar7,1,0,0);
        LuaCheckStatus(iVar2,plVar7,pcVar4);
      }
      else {
        lua_settop(this->L,-2);
      }
      lua_pushstring(this->L,local_58);
      lua_setfield(this->L,-0x2712,"LastGameKey");
    }
    lua_getfield(this->L,-0x2712,"Update");
    iVar2 = lua_type(this->L,-1);
    if (iVar2 == 6) {
      fVar6 = TimeStep();
      lua_pushnumber(this->L,(double)CONCAT44(unaff_ESI,(int)((ulonglong)(double)fVar6 >> 0x20)));
      plVar7 = this->L;
      pcVar4 = "Lua script Update error:\n%s";
      iVar2 = lua_pcall(plVar7,1,0,0);
      LuaCheckStatus(iVar2,plVar7,pcVar4);
    }
    else {
      lua_settop(this->L,-2);
    }
  }
  return;
}
