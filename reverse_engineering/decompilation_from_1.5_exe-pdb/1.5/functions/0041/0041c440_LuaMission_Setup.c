/*
 * Entry: 0041c440
 * Name: LuaMission::Setup
 * Namespace: LuaMission
 * Signature: bool Setup(LuaMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __thiscall LuaMission::Setup(LuaMission *this)

{
  uchar *puVar1;
  undefined1 auVar2 [4];
  undefined4 *puVar3;
  bool bVar4;
  char *pcVar5;
  int iVar6;
  lua_State *plVar7;
  uint uVar8;
  MAT_3D *pMVar9;
  MAT_3D *pMVar10;
  undefined4 unaff_EDI;
  undefined4 *puVar11;
  lua_State *plVar12;
  luaL_Reg *plVar13;
  char *pcVar14;
  undefined1 local_18 [4];
  char local_14 [8];
  uint local_c;
  undefined4 uStack_8;
  uint local_4;
  
  local_4 = __security_cookie ^ (uint)local_18;
  local_14[0] = '\0';
  local_14[1] = '\0';
  local_14[2] = '\0';
  local_14[3] = '\0';
  local_14[4] = '\0';
  local_14[5] = '\0';
  local_14[6] = '\0';
  local_14[7] = '\0';
  local_c = 0;
  uStack_8 = 0;
  strncpy(local_14,&msn_filename,8);
  local_c = local_c & 0xffffff00;
  pcVar5 = strchr(local_14,0x2e);
  if (pcVar5 != (char *)0x0) {
    *pcVar5 = '\0';
  }
  puVar3 = (undefined4 *)(local_18 + 3);
  do {
    puVar11 = puVar3;
    puVar3 = (undefined4 *)((int)puVar11 + 1);
  } while (*(char *)((int)puVar11 + 1) != '\0');
  *(undefined4 *)((int)puVar11 + 1) = 0x61756c2e;
  *(undefined1 *)((int)puVar11 + 5) = 0;
  iVar6 = ItemExists(local_14);
  if (iVar6 == 0) {
    Trace("No Lua script \"%s\"\n");
    return false;
  }
  plVar7 = luaL_newstate();
  this->L = plVar7;
  if (plVar7 == (lua_State *)0x0) {
    return false;
  }
  memset(sGameKeyName,0,0x400);
  uVar8 = 0;
  do {
    puVar1 = &sNameToGameKey[0].code + uVar8;
    puVar3 = (undefined4 *)((int)&sNameToGameKey[0].name + uVar8);
    uVar8 = uVar8 + 8;
    sGameKeyName[*puVar1] = (char *)*puVar3;
  } while (uVar8 < 0x108);
  luaL_openlibs(this->L);
  lua_atpanic(this->L,LuaPanic);
  lua_pushstring(this->L,"1.5.2.27 Update 1");
  lua_setfield(this->L,-0x2712,"GameVersion");
  lua_pushcclosure(this->L,LuaPrint,0);
  lua_setfield(this->L,-0x2712,"print");
  lua_pushcclosure(this->L,LuaWarning,0);
  plVar7 = this->L;
  lua_setfield(plVar7,-0x2712,"warning");
  plVar13 = (luaL_Reg *)0xffffd8ee;
  plVar12 = this->L;
  lua_pushvalue(plVar12,-0x2712);
  luaL_setfuncs(plVar12,plVar13,(int)plVar7);
  lua_pushlightuserdata(this->L,(void *)0x0);
  luaL_newmetatable(this->L,"Handle");
  lua_pushstring(this->L,"Handle");
  lua_setfield(this->L,-2,"__type");
  lua_pushcclosure(this->L,Handle_ToString,0);
  lua_setfield(this->L,-2,"__tostring");
  lua_setmetatable(this->L,-2);
  luaL_newmetatable(this->L,"ParameterDB");
  lua_pushstring(this->L,"ParameterDB");
  lua_setfield(this->L,-2,"__type");
  lua_pushcclosure(this->L,CloseODF,0);
  lua_setfield(this->L,-2,"__gc");
  lua_settop(this->L,-2);
  luaL_newmetatable(this->L,"VECTOR_3D");
  lua_pushstring(this->L,"VECTOR_3D");
  lua_setfield(this->L,-2,"__type");
  lua_pushcclosure(this->L,VECTOR_3D_Index,0);
  lua_setfield(this->L,-2,"__index");
  lua_pushcclosure(this->L,VECTOR_3D_NewIndex,0);
  lua_setfield(this->L,-2,"__newindex");
  lua_pushcclosure(this->L,VECTOR_3D_Neg,0);
  lua_setfield(this->L,-2,"__unm");
  lua_pushcclosure(this->L,VECTOR_3D_Add,0);
  lua_setfield(this->L,-2,"__add");
  lua_pushcclosure(this->L,VECTOR_3D_Sub,0);
  lua_setfield(this->L,-2,"__sub");
  lua_pushcclosure(this->L,VECTOR_3D_Mul,0);
  lua_setfield(this->L,-2,"__mul");
  lua_pushcclosure(this->L,VECTOR_3D_Div,0);
  lua_setfield(this->L,-2,"__div");
  lua_pushcclosure(this->L,VECTOR_3D_Eq,0);
  lua_setfield(this->L,-2,"__eq");
  lua_pushcclosure(this->L,VECTOR_3D_ToString,0);
  lua_setfield(this->L,-2,"__tostring");
  lua_settop(this->L,-2);
  luaL_newmetatable(this->L,"MAT_3D");
  lua_pushstring(this->L,"MAT_3D");
  lua_setfield(this->L,-2,"__type");
  lua_pushcclosure(this->L,MAT_3D_Index,0);
  lua_setfield(this->L,-2,"__index");
  lua_pushcclosure(this->L,MAT_3D_NewIndex,0);
  lua_setfield(this->L,-2,"__newindex");
  lua_pushcclosure(this->L,MAT_3D_Mul,0);
  lua_setfield(this->L,-2,"__mul");
  lua_pushcclosure(this->L,MAT_3D_ToString,0);
  lua_setfield(this->L,-2,"__tostring");
  plVar7 = this->L;
  lua_settop(plVar7,-2);
  pMVar9 = NewMatrix(plVar7);
  pMVar10 = &Identity_Matrix;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    pMVar9->right_x = pMVar10->right_x;
    pMVar10 = (MAT_3D *)&pMVar10->right_y;
    pMVar9 = (MAT_3D *)&pMVar9->right_y;
  }
  lua_setfield(this->L,-0x2712,"IdentityMatrix");
  lua_createtable(this->L,0x1b,0x1b);
  local_18 = (undefined1  [4])0x0;
  do {
    auVar2 = local_18;
    lua_pushnumber(this->L,(double)CONCAT44(unaff_EDI,
                                            (int)((ulonglong)(double)(int)local_18 >> 0x20)));
    lua_pushstring(this->L,cmdText[(int)auVar2]);
    lua_pushvalue(this->L,-1);
    lua_pushvalue(this->L,-3);
    lua_rawset(this->L,-5);
    lua_rawset(this->L,-3);
    local_18 = (undefined1  [4])((int)auVar2 + 1);
  } while ((int)local_18 < 0x1b);
  lua_setfield(this->L,-0x2712,"AiCommand");
  uVar8 = 0;
  lua_createtable(this->L,0,0x50);
  do {
    lua_pushnumber(this->L,(double)CONCAT44(unaff_EDI,
                                            (int)((ulonglong)
                                                  (double)*(int *)((int)&sClassIdNames[0].class_id +
                                                                  uVar8) >> 0x20)));
    lua_pushstring(this->L,*(char **)((int)&sClassIdNames[0].name + uVar8));
    lua_pushvalue(this->L,-1);
    lua_pushvalue(this->L,-3);
    lua_rawset(this->L,-5);
    lua_rawset(this->L,-3);
    uVar8 = uVar8 + 8;
  } while (uVar8 < 0x140);
  lua_setfield(this->L,-0x2712,"ClassId");
  uVar8 = 0;
  lua_createtable(this->L,0,0x38);
  do {
    lua_pushnumber(this->L,(double)CONCAT44(unaff_EDI,
                                            (int)((ulonglong)
                                                  (double)*(int *)((int)&sTeamSlotNames[0].slot +
                                                                  uVar8) >> 0x20)));
    lua_pushstring(this->L,*(char **)((int)&sTeamSlotNames[0].name + uVar8));
    lua_pushvalue(this->L,-1);
    lua_pushvalue(this->L,-3);
    lua_rawset(this->L,-5);
    lua_rawset(this->L,-3);
    uVar8 = uVar8 + 8;
  } while (uVar8 < 0xe0);
  lua_setfield(this->L,-0x2712,"TeamSlot");
  lua_getfield(this->L,-0x2712,"package");
  lua_getfield(this->L,-1,"loaders");
  lua_remove(this->L,-2);
  uVar8 = lua_objlen(this->L,-1);
  lua_pushcclosure(this->L,LuaLoader,0);
  lua_rawseti(this->L,-2,uVar8 + 1);
  lua_settop(this->L,-2);
  bVar4 = Net::IsNetGame();
  if (bVar4) {
    Net::MessageHandler = MessageHandler;
  }
  pcVar5 = UseItem(local_14);
  uVar8 = GetItemSize(local_14);
  plVar7 = this->L;
  pcVar14 = "Lua script load error:\n%s";
  iVar6 = luaL_loadbuffer(plVar7,pcVar5,uVar8,local_14);
  bVar4 = LuaCheckStatus(iVar6,plVar7,pcVar14);
  if (bVar4) {
    plVar7 = this->L;
    pcVar5 = "Lua script run error:\n%s";
    iVar6 = lua_pcall(plVar7,0,-1,0);
    bVar4 = LuaCheckStatus(iVar6,plVar7,pcVar5);
    if (bVar4) {
      bVar4 = true;
      goto LAB_0041ca72;
    }
  }
  bVar4 = false;
LAB_0041ca72:
  UnlockItem(local_14);
  return bVar4;
}
