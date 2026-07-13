/*
 * Entry: 0050dd99
 * Name: Blobs_Do_Threshholding
 * Namespace: Global
 * Signature: void Blobs_Do_Threshholding(ushort * * param_1, ushort * * param_2, int param_3, int param_4, int param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Blobs_Do_Threshholding
          (ushort **param_1,ushort **param_2,int param_3,int param_4,int param_5,int param_6)

{
  uint uVar1;
  int iVar2;
  ushort uVar3;
  int iVar4;
  
  if (0 < param_5) {
    iVar4 = (int)param_1 - (int)param_2;
    do {
      iVar2 = 0;
      if (0 < param_6) {
        do {
          uVar1 = (uint)*(ushort *)(*(int *)(iVar4 + (int)param_2) + iVar2 * 2);
          if (((int)uVar1 < param_3) || (param_4 < (int)uVar1)) {
            uVar3 = 0;
          }
          else {
            uVar3 = 0x7d1;
          }
          (*param_2)[iVar2] = uVar3;
          iVar2 = iVar2 + 1;
        } while (iVar2 < param_6);
      }
      param_2 = param_2 + 1;
      param_5 = param_5 + -1;
    } while (param_5 != 0);
  }
  return;
}
