
void FUN_007753c0(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  int local_14;
  int local_10;
  
  for (local_10 = 0; local_10 < DAT_00945494; local_10 = local_10 + 1) {
    iVar4 = local_10 * 0xb8;
    puVar5 = (undefined4 *)(&DAT_02c01118 + iVar4);
    if (*(int *)(&DAT_02c0113c + iVar4) == 0) {
      iVar1 = FUN_00774f80(puVar5,param_1);
      if (-1 < iVar1) {
        if (*(int *)(&DAT_02c00ef8 + iVar1 * 0x44) < 1) {
          local_14 = 0;
        }
        else {
          local_14 = rand();
          local_14 = local_14 % *(int *)(&DAT_02c00ef8 + iVar1 * 0x44);
        }
        *puVar5 = *(undefined4 *)(&DAT_02c00f1c + local_14 * 4 + iVar1 * 0x44);
        *(undefined4 *)(&DAT_02c0111c + iVar4) =
             *(undefined4 *)(&DAT_02c00efc + local_14 * 4 + iVar1 * 0x44);
        *(undefined4 *)(&DAT_02c01120 + iVar4) = 0;
        *(undefined4 *)(&DAT_02c01124 + iVar4) = 1;
        if ((DAT_008f049c == 0) || (*(int *)(&DAT_02c0111c + iVar4) == 0)) {
          *(undefined4 *)(&DAT_02c01138 + iVar4) = 0;
        }
        else {
          iVar1 = rand();
          *(int *)(&DAT_02c01138 + iVar4) = iVar1 % (DAT_008f049c * *(int *)(&DAT_02c0111c + iVar4))
          ;
        }
        *(int *)(&DAT_02c01134 + iVar4) = DAT_008f049c;
        uVar2 = FUN_00822e60();
        *(undefined4 *)(&DAT_02c0113c + iVar4) = uVar2;
      }
    }
    if (*(int *)(&DAT_02c0113c + iVar4) != 0) {
      uVar3 = FUN_00822e60();
      if ((uint)(*(int *)(&DAT_02c0113c + iVar4) + *(int *)(&DAT_02c01138 + iVar4)) < uVar3) {
        uVar2 = FUN_00822e60();
        *(undefined4 *)(&DAT_02c0113c + iVar4) = uVar2;
        *(int *)(&DAT_02c01120 + iVar4) = *(int *)(&DAT_02c01120 + iVar4) + 1;
        if (*(int *)(&DAT_02c0111c + iVar4) <= *(int *)(&DAT_02c01120 + iVar4)) {
          *(undefined4 *)(&DAT_02c01120 + iVar4) = 0;
          *(int *)(&DAT_02c01124 + iVar4) = *(int *)(&DAT_02c01124 + iVar4) + -1;
          if (*(int *)(&DAT_02c01124 + iVar4) < 1) {
            *(undefined4 *)(&DAT_02c0113c + iVar4) = 0;
          }
        }
        *(undefined4 *)(&DAT_02c01138 + iVar4) = *(undefined4 *)(&DAT_02c01134 + iVar4);
      }
    }
    if ((*(int *)(&DAT_02c0113c + iVar4) != 0) && (*(int *)(&DAT_02c01120 + iVar4) != 0)) {
      FUN_00775130(puVar5,param_1,(float)DAT_008f0590 * 0.01,(float)DAT_008f0590 * 0.01);
    }
  }
  return;
}

