/*
 * Entry: 004b220c
 * Name: find_textable
 * Namespace: Global
 * Signature: textab * find_textable(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

textab * __cdecl find_textable(char *param_1)

{
  byte bVar1;
  int iVar2;
  textab *ptVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  
  iVar2 = tcacheUsed;
  do {
    if (iVar2 < 0) {
      return (textab *)0x0;
    }
    ptVar3 = tcache + iVar2;
    pbVar5 = (byte *)param_1;
    do {
      bVar1 = ptVar3->group[0];
      bVar6 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_004b2240:
        iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_004b2245;
      }
      if (bVar1 == 0) break;
      bVar1 = ptVar3->group[1];
      bVar6 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_004b2240;
      ptVar3 = (textab *)(ptVar3->group + 2);
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_004b2245:
    if (iVar4 == 0) {
      return tcache + iVar2;
    }
    iVar2 = tcache[iVar2].next;
  } while( true );
}
