/*
 * Entry: 005c0edb
 * Name: str_format
 * Namespace: Global
 * Signature: int str_format(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl str_format(lua_State *param_1)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  undefined4 uVar7;
  char *pcVar8;
  char *unaff_EDI;
  double dVar9;
  uint local_438;
  uint local_434;
  char *local_430;
  luaL_Buffer *local_42c;
  luaL_Buffer local_428;
  char local_21c [512];
  char acStack_1c [20];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_428.buffer + 0x5c);
  iVar3 = lua_gettop(param_1);
  local_42c = (luaL_Buffer *)0x1;
  pcVar4 = luaL_checklstring(param_1,1,&local_438);
  luaL_buffinit(param_1,&local_428);
  pcVar8 = pcVar4;
  do {
    while( true ) {
      while( true ) {
        if (pcVar4 + local_438 <= pcVar8) {
          luaL_pushresult(&local_428);
          return 1;
        }
        if ((*pcVar8 == '%') && (pcVar8 = pcVar8 + 1, *pcVar8 != '%')) break;
        if (local_21c <= local_428.p) {
          luaL_prepbuffer(&local_428);
        }
        *local_428.p = *pcVar8;
        local_428.p = local_428.p + 1;
        pcVar8 = pcVar8 + 1;
      }
      local_42c = (luaL_Buffer *)((int)&local_42c->p + 1);
      if (iVar3 < (int)local_42c) {
        luaL_argerror(param_1,(int)local_42c,"no value");
      }
      local_430 = scanformat(param_1,pcVar8,unaff_EDI);
      iVar5 = (int)*local_430;
      local_430 = local_430 + 1;
      if (0x69 < iVar5) break;
      if (iVar5 == 0x69) {
LAB_005c0ffa:
        pcVar6 = acStack_1c;
        pcVar8 = acStack_1c + 1;
        do {
          cVar2 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar2 != '\0');
        pcVar1 = pcVar6 + (int)(local_21c + (0x1ff - (int)pcVar8));
        pcVar1[0] = 'l';
        pcVar1[1] = '\0';
        pcVar6[(int)(acStack_1c + -(int)pcVar8)] = *pcVar1;
        pcVar6[(int)(acStack_1c + (1 - (int)pcVar8))] = '\0';
LAB_005c102a:
        luaL_checknumber(param_1,(int)local_42c);
        _ftol2_sse();
        uVar7 = extraout_EAX;
LAB_005c109a:
        sprintf(local_21c,acStack_1c,uVar7);
      }
      else {
        if ((iVar5 != 0x45) && (iVar5 != 0x47)) {
          if (iVar5 == 0x58) goto LAB_005c105c;
          if (iVar5 == 99) goto LAB_005c102a;
          if (iVar5 == 100) goto LAB_005c0ffa;
          if (2 < iVar5 - 0x65U) goto LAB_005c1170;
        }
        dVar9 = luaL_checknumber(param_1,(int)local_42c);
        sprintf(local_21c,acStack_1c,dVar9);
      }
LAB_005c10ae:
      pcVar8 = local_21c;
      do {
        cVar2 = *pcVar8;
        pcVar8 = pcVar8 + 1;
      } while (cVar2 != '\0');
      luaL_addlstring(&local_428,local_21c,(int)pcVar8 - (int)(local_21c + 1));
      pcVar8 = local_430;
    }
    if (iVar5 == 0x6f) {
LAB_005c105c:
      pcVar6 = acStack_1c;
      pcVar8 = acStack_1c + 1;
      do {
        cVar2 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar2 != '\0');
      pcVar1 = pcVar6 + (int)(local_21c + (0x1ff - (int)pcVar8));
      pcVar1[0] = 'l';
      pcVar1[1] = '\0';
      pcVar6[(int)(acStack_1c + -(int)pcVar8)] = *pcVar1;
      pcVar6[(int)(acStack_1c + (1 - (int)pcVar8))] = '\0';
      luaL_checknumber(param_1,(int)local_42c);
      _ftol2();
      uVar7 = extraout_EAX_00;
      goto LAB_005c109a;
    }
    if (iVar5 == 0x71) {
      addquoted(param_1,local_42c,(int)unaff_EDI);
      pcVar8 = local_430;
    }
    else {
      if (iVar5 != 0x73) {
        if ((iVar5 != 0x75) && (iVar5 != 0x78)) {
LAB_005c1170:
          iVar3 = luaL_error(param_1,"invalid option \'%%%c\' to \'format\'");
          return iVar3;
        }
        goto LAB_005c105c;
      }
      luaL_checklstring(param_1,(int)local_42c,&local_434);
      pcVar8 = strchr(acStack_1c,0x2e);
      if ((pcVar8 != (char *)0x0) || (local_434 < 100)) {
        sprintf(local_21c,acStack_1c);
        goto LAB_005c10ae;
      }
      lua_pushvalue(param_1,(int)local_42c);
      luaL_addvalue(&local_428);
      pcVar8 = local_430;
    }
  } while( true );
}
