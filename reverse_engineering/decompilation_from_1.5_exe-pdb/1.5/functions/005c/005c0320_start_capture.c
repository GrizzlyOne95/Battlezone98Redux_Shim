/*
 * Entry: 005c0320
 * Name: start_capture
 * Namespace: Global
 * Signature: char * start_capture(MatchState * param_1, char * param_2, char * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl start_capture(MatchState *param_1,char *param_2,char *param_3,int param_4)

{
  int iVar1;
  char *pcVar2;
  char *unaff_EBX;
  MatchState *unaff_ESI;
  
  iVar1 = unaff_ESI->level;
  if (0x1f < iVar1) {
    luaL_error(unaff_ESI->L,"too many captures");
  }
  unaff_ESI->capture[iVar1].init = unaff_EBX;
  unaff_ESI->capture[iVar1].len = (int)param_2;
  unaff_ESI->level = iVar1 + 1;
  pcVar2 = match(unaff_ESI,unaff_EBX,(char *)param_1);
  if (pcVar2 == (char *)0x0) {
    unaff_ESI->level = unaff_ESI->level + -1;
  }
  return pcVar2;
}
