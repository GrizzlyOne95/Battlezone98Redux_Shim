/*
 * Entry: 005c02e2
 * Name: min_expand
 * Namespace: Global
 * Signature: char * min_expand(MatchState * param_1, char * param_2, char * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl min_expand(MatchState *param_1,char *param_2,char *param_3,char *param_4)

{
  char *in_EAX;
  int iVar1;
  char *pcVar2;
  int unaff_EBX;
  char *unaff_ESI;
  char *unaff_EDI;
  
  while( true ) {
    pcVar2 = match(param_1,in_EAX,(char *)(unaff_EBX + 1));
    if (pcVar2 != (char *)0x0) {
      return pcVar2;
    }
    if ((param_1->src_end <= in_EAX) ||
       (iVar1 = singlematch(unaff_EBX,unaff_EDI,unaff_ESI), iVar1 == 0)) break;
    in_EAX = in_EAX + 1;
  }
  return (char *)0x0;
}
