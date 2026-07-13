/*
 * Entry: 005c01f7
 * Name: singlematch
 * Namespace: Global
 * Signature: int singlematch(int param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl singlematch(int param_1,char *param_2,char *param_3)

{
  byte bVar1;
  byte *in_EAX;
  int iVar2;
  uint in_ECX;
  char *unaff_EBX;
  char *unaff_retaddr;
  
  bVar1 = *in_EAX;
  if (bVar1 == 0x25) {
    iVar2 = match_class((uint)in_EAX[1],(int)unaff_EBX);
  }
  else {
    if (bVar1 == 0x2e) {
      return 1;
    }
    if (bVar1 != 0x5b) {
      return (uint)(bVar1 == in_ECX);
    }
    iVar2 = matchbracketclass(param_1 + -1,unaff_EBX,unaff_retaddr);
  }
  return iVar2;
}
