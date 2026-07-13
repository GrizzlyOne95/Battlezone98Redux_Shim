/*
 * Entry: 0050e30e
 * Name: Blobs_Find_Blobs
 * Namespace: Global
 * Signature: ushort * * Blobs_Find_Blobs(ushort * * param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort ** __cdecl
Blobs_Find_Blobs(ushort **param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  ushort **ppuVar1;
  ushort **ppuVar2;
  ushort **ppuVar3;
  int iVar4;
  int local_10;
  
  ppuVar1 = Blobs_New_Single_Band(param_5,param_6);
  ppuVar2 = Blobs_New_Single_Band(param_5,param_6);
  if (0 < param_5) {
    local_10 = param_5;
    ppuVar3 = ppuVar1;
    do {
      iVar4 = 0;
      if (0 < param_6) {
        do {
          (*ppuVar3)[iVar4] =
               *(ushort *)(*(int *)(((int)param_1 - (int)ppuVar1) + (int)ppuVar3) + iVar4 * 2);
          iVar4 = iVar4 + 1;
        } while (iVar4 < param_6);
      }
      ppuVar3 = ppuVar3 + 1;
      local_10 = local_10 + -1;
    } while (local_10 != 0);
  }
  Blobs_Do_Threshholding(ppuVar1,ppuVar2,param_2,param_3,param_5,param_6);
  Blobs_Find_Connected_Regions(ppuVar2,param_4,param_5,param_6);
  Blobs_Single_Band_Delete(ppuVar1,param_5,param_6);
  return ppuVar2;
}
