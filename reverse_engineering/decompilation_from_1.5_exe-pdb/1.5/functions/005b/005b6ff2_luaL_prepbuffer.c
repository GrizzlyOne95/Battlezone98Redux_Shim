/*
 * Entry: 005b6ff2
 * Name: luaL_prepbuffer
 * Namespace: Global
 * Signature: char * luaL_prepbuffer(luaL_Buffer * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl luaL_prepbuffer(luaL_Buffer *param_1)

{
  int iVar1;
  luaL_Buffer *unaff_ESI;
  
  iVar1 = emptybuffer(unaff_ESI);
  if (iVar1 != 0) {
    adjuststack(unaff_ESI);
  }
  return param_1->buffer;
}
