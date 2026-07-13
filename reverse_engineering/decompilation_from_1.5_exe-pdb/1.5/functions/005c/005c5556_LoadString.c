/*
 * Entry: 005c5556
 * Name: LoadString
 * Namespace: Global
 * Signature: TString * LoadString(LoadState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TString * __cdecl LoadString(LoadState *param_1)

{
  LoadState *pLVar1;
  TString *pTVar2;
  lua_State *in_ECX;
  undefined4 *unaff_ESI;
  lua_State *plVar3;
  
  LoadBlock((LoadState *)&stack0xfffffff8,(void *)0x4,(uint)in_ECX);
  if (in_ECX == (lua_State *)0x0) {
    return (TString *)0x0;
  }
  plVar3 = (lua_State *)*unaff_ESI;
  pLVar1 = (LoadState *)luaZ_openspace(plVar3,(Mbuffer *)unaff_ESI[2],(uint)in_ECX);
  LoadBlock(pLVar1,in_ECX,(uint)plVar3);
  pTVar2 = luaS_newlstr((lua_State *)*unaff_ESI,(char *)pLVar1,(uint)((int)&in_ECX[-1].errfunc + 3))
  ;
  return pTVar2;
}
