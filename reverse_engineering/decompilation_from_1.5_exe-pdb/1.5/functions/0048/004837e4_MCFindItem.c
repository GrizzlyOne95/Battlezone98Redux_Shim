/*
 * Entry: 004837e4
 * Name: MCFindItem
 * Namespace: Global
 * Signature: cachenode * MCFindItem(MULTICACHE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

cachenode * __cdecl MCFindItem(MULTICACHE *param_1,char *param_2)

{
  byte bVar1;
  int iVar2;
  cachenode *pcVar3;
  byte *pbVar4;
  cachenode *pcVar5;
  bool bVar6;
  
  nFindItems = nFindItems + 1;
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    iVar2 = compute_hash(param_2);
    pcVar3 = param_1->Cache[iVar2];
    pbVar4 = (byte *)param_2;
    pcVar5 = pcVar3;
    if (pcVar3 != (cachenode *)0x0) {
LAB_0048381b:
      do {
        bVar1 = pcVar3->assetname[0];
        bVar6 = bVar1 < *pbVar4;
        if (bVar1 == *pbVar4) {
          if (bVar1 != 0) {
            bVar1 = pcVar3->assetname[1];
            bVar6 = bVar1 < pbVar4[1];
            if (bVar1 != pbVar4[1]) goto LAB_00483839;
            pcVar3 = (cachenode *)(pcVar3->assetname + 2);
            pbVar4 = pbVar4 + 2;
            if (bVar1 != 0) goto LAB_0048381b;
          }
          iVar2 = 0;
        }
        else {
LAB_00483839:
          iVar2 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        }
        if (iVar2 == 0) {
          return pcVar5;
        }
        pcVar3 = pcVar5->Next;
        pbVar4 = (byte *)param_2;
        pcVar5 = pcVar3;
        if (pcVar3 == (cachenode *)0x0) {
          return (cachenode *)0x0;
        }
      } while( true );
    }
  }
  return (cachenode *)0x0;
}
