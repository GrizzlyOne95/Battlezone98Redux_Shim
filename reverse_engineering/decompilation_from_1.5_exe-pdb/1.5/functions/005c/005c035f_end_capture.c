/*
 * Entry: 005c035f
 * Name: end_capture
 * Namespace: Global
 * Signature: char * end_capture(MatchState * param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl end_capture(MatchState *param_1,char *param_2,char *param_3)

{
  int iVar1;
  char *pcVar2;
  int *piVar3;
  MatchState *unaff_ESI;
  
  iVar1 = unaff_ESI->level + -1;
  if (-1 < iVar1) {
    piVar3 = &unaff_ESI->capture[unaff_ESI->level + -1].len;
    do {
      if (*piVar3 == -1) goto LAB_005c0385;
      iVar1 = iVar1 + -1;
      piVar3 = piVar3 + -2;
    } while (-1 < iVar1);
  }
  iVar1 = luaL_error(unaff_ESI->L,"invalid pattern capture");
LAB_005c0385:
  piVar3 = &unaff_ESI->capture[iVar1].len;
  *piVar3 = (int)param_1 - (int)unaff_ESI->capture[iVar1].init;
  pcVar2 = match(unaff_ESI,(char *)param_1,param_2);
  if (pcVar2 == (char *)0x0) {
    *piVar3 = -1;
  }
  return pcVar2;
}
