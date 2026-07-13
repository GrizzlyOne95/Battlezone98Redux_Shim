/*
 * Entry: 005bb176
 * Name: luaV_concat
 * Namespace: Global
 * Signature: void luaV_concat(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaV_concat(lua_State *param_1,int param_2,int param_3)

{
  lua_TValue *plVar1;
  int iVar2;
  char *pcVar3;
  GCObject *pGVar4;
  lua_TValue *plVar5;
  uint uVar6;
  uint local_c;
  int local_8;
  
  do {
    plVar1 = param_1->base;
    local_8 = 2;
    if (((plVar1[param_3 + -1].tt == 4) || (plVar1[param_3 + -1].tt == 3)) &&
       ((plVar1[param_3].tt == 4 || (iVar2 = luaV_tostring(param_1,plVar1 + param_3), iVar2 != 0))))
    {
      local_c = *(uint *)(plVar1[param_3].value.b + 0xc);
      if (local_c == 0) {
        if (plVar1[param_3 + -1].tt != 4) {
          luaV_tostring(param_1,plVar1 + param_3 + -1);
        }
      }
      else {
        local_8 = 1;
        if (1 < param_2) {
          plVar5 = plVar1 + param_3 + -1;
          do {
            if ((plVar5->tt != 4) && (iVar2 = luaV_tostring(param_1,plVar5), iVar2 == 0)) break;
            uVar6 = *(uint *)((plVar5->value).b + 0xc);
            if (-local_c - 3 <= uVar6) {
              luaG_runerror(param_1,"string length overflow");
            }
            local_c = local_c + uVar6;
            local_8 = local_8 + 1;
            plVar5 = plVar5 + -1;
          } while (local_8 < param_2);
        }
        pcVar3 = luaZ_openspace(param_1,&param_1->l_G->buff,local_c);
        uVar6 = 0;
        local_c = local_8;
        if (0 < local_8) {
          plVar5 = plVar1 + ((param_3 + 1) - local_8);
          do {
            iVar2 = *(int *)((plVar5->value).b + 0xc);
            memcpy(pcVar3 + uVar6,(plVar5->value).b + 0x10,iVar2);
            uVar6 = uVar6 + iVar2;
            local_c = local_c + -1;
            plVar5 = plVar5 + 1;
          } while (0 < (int)local_c);
        }
        pGVar4 = (GCObject *)luaS_newlstr(param_1,pcVar3,uVar6);
        plVar1[(param_3 + 1) - local_8].value.gc = pGVar4;
        plVar1[(param_3 + 1) - local_8].tt = 4;
      }
    }
    else {
      plVar5 = plVar1 + param_3 + -1;
      iVar2 = call_binTM(param_1,plVar5,plVar1 + param_3,plVar5,TM_CONCAT);
      if (iVar2 == 0) {
        luaG_concaterror(param_1,plVar5,plVar1 + param_3);
      }
    }
    param_2 = param_2 + (1 - local_8);
    param_3 = param_3 + (1 - local_8);
    if (param_2 < 2) {
      return;
    }
  } while( true );
}
