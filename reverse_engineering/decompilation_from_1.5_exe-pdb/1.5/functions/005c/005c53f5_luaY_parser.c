/*
 * Entry: 005c53f5
 * Name: luaY_parser
 * Namespace: Global
 * Signature: Proto * luaY_parser(lua_State * param_1, Zio * param_2, Mbuffer * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

Proto * __cdecl luaY_parser(lua_State *param_1,Zio *param_2,Mbuffer *param_3,char *param_4)

{
  char cVar1;
  char *pcVar2;
  TString *pTVar3;
  int unaff_EDI;
  FuncState *pFVar4;
  undefined1 local_28c [72];
  Proto *local_244;
  undefined1 local_20c [516];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_20c;
  local_28c._60_4_ = param_3;
  pcVar2 = param_4;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pTVar3 = luaS_newlstr(param_1,param_4,(int)pcVar2 - (int)(param_4 + 1));
  pFVar4 = (FuncState *)local_28c;
  luaX_setinput(param_1,(LexState *)pFVar4,param_2,pTVar3);
  open_func((LexState *)param_1,pFVar4);
  local_244->is_vararg = '\x02';
  luaX_next((LexState *)local_28c);
  chunk((LexState *)local_28c);
  if ((lua_State *)local_28c._16_4_ != (lua_State *)0x11f) {
    error_expected((LexState *)0x11f,unaff_EDI);
  }
  close_func((LexState *)local_28c);
  return local_244;
}
