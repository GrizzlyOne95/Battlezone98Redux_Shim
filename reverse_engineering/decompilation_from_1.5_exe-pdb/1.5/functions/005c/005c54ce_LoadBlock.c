/*
 * Entry: 005c54ce
 * Name: LoadBlock
 * Namespace: Global
 * Signature: void LoadBlock(LoadState * param_1, void * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LoadBlock(LoadState *param_1,void *param_2,uint param_3)

{
  int in_EAX;
  uint uVar1;
  char *unaff_ESI;
  
  uVar1 = luaZ_read(*(Zio **)(in_EAX + 4),param_1,(uint)param_2);
  if (uVar1 != 0) {
    error((LoadState *)"unexpected end",unaff_ESI);
  }
  return;
}
