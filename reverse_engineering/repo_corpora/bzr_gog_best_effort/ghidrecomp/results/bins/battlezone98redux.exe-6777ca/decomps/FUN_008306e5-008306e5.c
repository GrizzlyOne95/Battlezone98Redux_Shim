
void FUN_008306e5(undefined4 param_1,int param_2)

{
  byte *pbVar1;
  int iVar2;
  int extraout_EDX;
  int extraout_EDX_00;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (*(int *)(param_2 + 0x20) != 0) {
    pbVar1 = (byte *)(*(int *)(param_2 + 0x20) + 5);
    *pbVar1 = *pbVar1 & 0xfc;
  }
  iVar4 = 0;
  iVar3 = 0;
  if (0 < *(int *)(param_2 + 0x28)) {
    iVar5 = 0;
    do {
      if ((3 < *(int *)(*(int *)(param_2 + 8) + 8 + iVar5)) &&
         (iVar2 = *(int *)(*(int *)(param_2 + 8) + iVar5), (*(byte *)(iVar2 + 5) & 3) != 0)) {
        FUN_00830437(param_1,iVar2);
        param_2 = extraout_EDX;
      }
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + 0x10;
    } while (iVar3 < *(int *)(param_2 + 0x28));
  }
  iVar3 = 0;
  if (0 < *(int *)(param_2 + 0x24)) {
    do {
      iVar5 = *(int *)(*(int *)(param_2 + 0x1c) + iVar3 * 4);
      if (iVar5 != 0) {
        pbVar1 = (byte *)(iVar5 + 5);
        *pbVar1 = *pbVar1 & 0xfc;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(param_2 + 0x24));
  }
  iVar3 = 0;
  if (0 < *(int *)(param_2 + 0x34)) {
    do {
      iVar5 = *(int *)(*(int *)(param_2 + 0x10) + iVar3 * 4);
      if ((iVar5 != 0) && ((*(byte *)(iVar5 + 5) & 3) != 0)) {
        FUN_00830437(param_1,iVar5);
        param_2 = extraout_EDX_00;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(param_2 + 0x34));
  }
  if (0 < *(int *)(param_2 + 0x38)) {
    iVar3 = 0;
    do {
      iVar5 = *(int *)(iVar3 + *(int *)(param_2 + 0x18));
      if (iVar5 != 0) {
        pbVar1 = (byte *)(iVar5 + 5);
        *pbVar1 = *pbVar1 & 0xfc;
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0xc;
    } while (iVar4 < *(int *)(param_2 + 0x38));
  }
  return;
}

