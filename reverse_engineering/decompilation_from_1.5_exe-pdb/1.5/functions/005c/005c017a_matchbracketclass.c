/*
 * Entry: 005c017a
 * Name: matchbracketclass
 * Namespace: Global
 * Signature: int matchbracketclass(int param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl matchbracketclass(int param_1,char *param_2,char *param_3)

{
  byte bVar1;
  char *in_EAX;
  int iVar2;
  uint unaff_EBX;
  byte *pbVar3;
  int unaff_EDI;
  char *pcVar4;
  bool bVar5;
  uint local_8;
  
  bVar5 = in_EAX[1] == '^';
  if (bVar5) {
    in_EAX = in_EAX + 1;
  }
  local_8 = (uint)!bVar5;
  pbVar3 = (byte *)(in_EAX + 1);
  if (pbVar3 < (uint)param_1) {
    pcVar4 = in_EAX + 3;
    do {
      if (*pbVar3 == 0x25) {
        pbVar3 = pbVar3 + 1;
        pcVar4 = pcVar4 + 1;
        iVar2 = match_class((uint)*pbVar3,unaff_EDI);
        if (iVar2 != 0) {
          return local_8;
        }
      }
      else if ((pbVar3[1] == 0x2d) && (pcVar4 < (uint)param_1)) {
        bVar1 = *pbVar3;
        pbVar3 = pbVar3 + 2;
        pcVar4 = pcVar4 + 2;
        if (((int)(uint)bVar1 <= (int)unaff_EBX) && ((int)unaff_EBX <= (int)(uint)*pbVar3)) {
          return local_8;
        }
      }
      else if (*pbVar3 == unaff_EBX) {
        return local_8;
      }
      pbVar3 = pbVar3 + 1;
      pcVar4 = pcVar4 + 1;
    } while (pbVar3 < (uint)param_1);
  }
  return (uint)(local_8 == 0);
}
