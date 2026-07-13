/*
 * Entry: 005c028f
 * Name: max_expand
 * Namespace: Global
 * Signature: char * max_expand(MatchState * param_1, char * param_2, char * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl max_expand(MatchState *param_1,char *param_2,char *param_3,char *param_4)

{
  int iVar1;
  char *unaff_EBX;
  char *pcVar2;
  char *unaff_ESI;
  char *unaff_EDI;
  int iVar3;
  
  iVar3 = 0;
  pcVar2 = unaff_ESI;
  if (unaff_ESI < param_1->src_end) {
    do {
      iVar1 = singlematch((int)param_3,unaff_EDI,unaff_EBX);
      if (iVar1 == 0) break;
      iVar3 = iVar3 + 1;
      pcVar2 = pcVar2 + 1;
    } while (pcVar2 < param_1->src_end);
    if (iVar3 < 0) {
      return (char *)0x0;
    }
  }
  do {
    pcVar2 = match(param_1,unaff_ESI + iVar3,param_3 + 1);
    if (pcVar2 != (char *)0x0) {
      return pcVar2;
    }
    iVar3 = iVar3 + -1;
  } while (-1 < iVar3);
  return (char *)0x0;
}
