/*
 * Entry: 005b7faa
 * Name: luaO_pushvfstring
 * Namespace: Global
 * Signature: char * luaO_pushvfstring(lua_State * param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char * __cdecl luaO_pushvfstring(lua_State *param_1,char *param_2,char *param_3)

{
  Value VVar1;
  char cVar2;
  lua_TValue *plVar3;
  GCObject *pGVar4;
  char *pcVar5;
  int iVar6;
  int *piVar7;
  char *unaff_EDI;
  int local_34;
  char *local_30;
  undefined1 local_2c;
  char local_2b;
  undefined1 local_2a;
  uchar local_28;
  uchar local_27;
  lua_TValue *local_24;
  char local_20 [24];
  CallInfo *local_8;
  
  local_8 = (CallInfo *)(__security_cookie ^ (uint)&stack0xfffffffc);
  iVar6 = 1;
  local_24 = (lua_TValue *)param_3;
  local_34 = 1;
  pushstr((lua_State *)"",unaff_EDI);
  local_30 = strchr(param_2,0x25);
  if (local_30 != (char *)0x0) {
    piVar7 = (int *)&local_24[-1].field_0xc;
    local_24 = (lua_TValue *)&local_24[-1].tt;
    do {
      plVar3 = param_1->top;
      pGVar4 = (GCObject *)luaS_newlstr(param_1,param_2,(int)local_30 - (int)param_2);
      (plVar3->value).gc = pGVar4;
      plVar3->tt = 4;
      if ((int)param_1->stack_last - (int)param_1->top < 0x11) {
        luaD_growstack(param_1,1);
      }
      param_1->top = param_1->top + 1;
      cVar2 = local_30[1];
      plVar3 = param_1->top;
      if (cVar2 == '%') {
        pcVar5 = "%";
LAB_005b8106:
        pushstr((lua_State *)pcVar5,unaff_EDI);
      }
      else {
        if (cVar2 == 'c') {
          local_24 = (lua_TValue *)((int)&local_24->value + 4);
          piVar7 = piVar7 + 1;
          local_28 = (uchar)*piVar7;
          local_27 = '\0';
          pcVar5 = (char *)&local_28;
          goto LAB_005b8106;
        }
        if (cVar2 == 'd') {
          local_24 = (lua_TValue *)((int)&local_24->value + 4);
          piVar7 = piVar7 + 1;
          VVar1.n = (double)*piVar7;
LAB_005b80c7:
          plVar3->value = VVar1;
          plVar3->tt = 3;
          if ((int)param_1->stack_last - (int)param_1->top < 0x11) {
            luaD_growstack(param_1,1);
          }
          param_1->top = param_1->top + 1;
        }
        else {
          if (cVar2 == 'f') {
            local_24 = (lua_TValue *)&local_24->tt;
            VVar1 = *(Value *)local_24;
            piVar7 = piVar7 + 2;
            goto LAB_005b80c7;
          }
          if (cVar2 != 'p') {
            if (cVar2 == 's') {
              local_24 = (lua_TValue *)((int)&local_24->value + 4);
              piVar7 = piVar7 + 1;
              pcVar5 = (char *)*piVar7;
              if ((lua_State *)pcVar5 == (lua_State *)0x0) {
                pcVar5 = "(null)";
              }
            }
            else {
              local_2c = 0x25;
              local_2a = 0;
              pcVar5 = &local_2c;
              local_2b = cVar2;
            }
            goto LAB_005b8106;
          }
          local_24 = (lua_TValue *)((int)&local_24->value + 4);
          piVar7 = piVar7 + 1;
          pcVar5 = local_20;
          sprintf(pcVar5,"%p",*piVar7);
          pushstr((lua_State *)local_20,pcVar5);
        }
      }
      iVar6 = local_34 + 2;
      param_2 = local_30 + 2;
      local_30 = strchr(param_2,0x25);
      local_34 = iVar6;
    } while (local_30 != (char *)0x0);
  }
  pushstr((lua_State *)param_2,unaff_EDI);
  luaV_concat(param_1,iVar6 + 1,((int)param_1->top - (int)param_1->base >> 4) + -1);
  param_1->top = param_1->top + -iVar6;
  return (char *)(param_1->top[-1].value.b + 0x10);
}
