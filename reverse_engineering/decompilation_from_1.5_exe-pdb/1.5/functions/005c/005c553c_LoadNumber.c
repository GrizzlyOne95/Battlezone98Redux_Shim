/*
 * Entry: 005c553c
 * Name: LoadNumber
 * Namespace: Global
 * Signature: double LoadNumber(LoadState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl LoadNumber(LoadState *param_1)

{
  lua_State *in_ECX;
  lua_State *plVar1;
  
  plVar1 = in_ECX;
  LoadBlock((LoadState *)&stack0xfffffff4,(void *)0x8,(uint)in_ECX);
  return (double)CONCAT44(in_ECX,plVar1);
}
