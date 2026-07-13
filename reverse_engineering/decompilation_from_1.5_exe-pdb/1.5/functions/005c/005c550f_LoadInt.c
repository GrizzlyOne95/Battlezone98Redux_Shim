/*
 * Entry: 005c550f
 * Name: LoadInt
 * Namespace: Global
 * Signature: int LoadInt(LoadState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl LoadInt(LoadState *param_1)

{
  char *unaff_ESI;
  lua_State *local_8;
  
  LoadBlock((LoadState *)&local_8,(void *)0x4,(uint)unaff_ESI);
  if ((int)local_8 < 0) {
    error((LoadState *)"bad integer",unaff_ESI);
  }
  return (int)local_8;
}
