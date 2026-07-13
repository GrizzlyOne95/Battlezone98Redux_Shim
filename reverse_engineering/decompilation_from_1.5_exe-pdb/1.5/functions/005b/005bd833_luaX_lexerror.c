/*
 * Entry: 005bd833
 * Name: luaX_lexerror
 * Namespace: Global
 * Signature: void luaX_lexerror(LexState * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaX_lexerror(LexState *param_1,char *param_2,int param_3)

{
  int unaff_ESI;
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  luaO_chunkid(local_58,(char *)(param_1->source + 1),0x50);
  luaO_pushfstring(param_1->L,"%s:%d: %s");
  if (param_3 != 0) {
    if ((param_3 < 0x11c) || (0x11e < param_3)) {
      luaX_token2str(param_1,param_3);
    }
    else {
      save((LexState *)0x0,unaff_ESI);
    }
    luaO_pushfstring(param_1->L,"%s near \'%s\'");
  }
                    /* WARNING: Subroutine does not return */
  luaD_throw(param_1->L,3);
}
