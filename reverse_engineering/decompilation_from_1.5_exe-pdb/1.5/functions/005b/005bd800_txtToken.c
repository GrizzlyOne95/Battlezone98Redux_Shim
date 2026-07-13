/*
 * Entry: 005bd800
 * Name: txtToken
 * Namespace: Global
 * Signature: char * txtToken(LexState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl txtToken(LexState *param_1,int param_2)

{
  LexState *in_EAX;
  char *pcVar1;
  int unaff_EBX;
  
  if (((int)param_1 < 0x11c) || (0x11e < (int)param_1)) {
    pcVar1 = luaX_token2str(in_EAX,(int)param_1);
  }
  else {
    save((LexState *)0x0,unaff_EBX);
    pcVar1 = in_EAX->buff->buffer;
  }
  return pcVar1;
}
