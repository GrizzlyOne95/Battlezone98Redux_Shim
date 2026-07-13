/*
 * Entry: 005bef4b
 * Name: makemask
 * Namespace: Global
 * Signature: int makemask(char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl makemask(char *param_1,int param_2)

{
  char *pcVar1;
  uint uVar2;
  char *unaff_EDI;
  
  pcVar1 = strchr(unaff_EDI,99);
  uVar2 = (uint)(pcVar1 != (char *)0x0);
  pcVar1 = strchr(unaff_EDI,0x72);
  if (pcVar1 != (char *)0x0) {
    uVar2 = uVar2 | 2;
  }
  pcVar1 = strchr(unaff_EDI,0x6c);
  if (pcVar1 != (char *)0x0) {
    uVar2 = uVar2 | 4;
  }
  if (0 < (int)param_1) {
    uVar2 = uVar2 | 8;
  }
  return uVar2;
}
