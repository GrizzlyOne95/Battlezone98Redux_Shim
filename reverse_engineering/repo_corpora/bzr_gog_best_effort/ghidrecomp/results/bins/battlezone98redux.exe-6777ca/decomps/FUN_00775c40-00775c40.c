
void FUN_00775c40(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  int local_14;
  int local_10;
  int local_c;
  
  for (local_10 = 0; local_10 < DAT_02c04198; local_10 = local_10 + 1) {
    iVar3 = local_10 * 0xc4;
    puVar4 = (undefined4 *)(&DAT_02c042f0 + iVar3);
    if (*(int *)(&DAT_02c04320 + iVar3) == 0) {
      local_c = DAT_02c041a0;
      for (local_14 = 0; (*(int *)(&DAT_02c04320 + iVar3) == 0 && (local_14 < 8));
          local_14 = local_14 + 1) {
        if (local_c < 7) {
          local_c = local_c + 1;
        }
        else {
          local_c = 0;
        }
        if ((local_c << 4 != -0x2c041ac) && ((&DAT_02c041ac)[local_c * 0x10] != '\0')) {
          DAT_02c041a0 = local_c;
          *puVar4 = &DAT_02c041ac + local_c * 0x10;
          *(undefined4 *)(&DAT_02c042f4 + iVar3) = *(undefined4 *)(&DAT_02c042cc + local_c * 4);
          *(undefined4 *)(&DAT_02c042f8 + iVar3) = *(undefined4 *)(&DAT_02c042ac + local_c * 4);
          *(undefined4 *)(&DAT_02c04300 + iVar3) = 0;
          *(undefined4 *)(&DAT_02c042fc + iVar3) = 1;
          *(uint *)(&DAT_02c0431c + iVar3) = DAT_02c041a4;
          if (DAT_02c041a4 < DAT_02c041a8) {
            uVar1 = rand();
            *(uint *)(&DAT_02c0431c + iVar3) =
                 uVar1 % (DAT_02c041a8 - DAT_02c041a4) + *(int *)(&DAT_02c0431c + iVar3);
          }
          *(undefined4 *)(&DAT_02c04318 + iVar3) = *(undefined4 *)(&DAT_02c0424c + local_c * 4);
          *(undefined4 *)(&DAT_02c04314 + iVar3) = *(undefined4 *)(&DAT_02c0426c + local_c * 4);
          *(undefined4 *)(&DAT_02c04310 + iVar3) = DAT_02c0419c;
          FUN_00775800(puVar4,param_1);
          uVar2 = FUN_00822e60();
          *(undefined4 *)(&DAT_02c04320 + iVar3) = uVar2;
        }
      }
    }
    if (*(int *)(&DAT_02c04320 + iVar3) != 0) {
      uVar1 = FUN_00822e60();
      if ((uint)(*(int *)(&DAT_02c04320 + iVar3) + *(int *)(&DAT_02c0431c + iVar3)) < uVar1) {
        uVar2 = FUN_00822e60();
        *(undefined4 *)(&DAT_02c04320 + iVar3) = uVar2;
        *(int *)(&DAT_02c04300 + iVar3) = *(int *)(&DAT_02c04300 + iVar3) + 1;
        if (*(int *)(&DAT_02c042f8 + iVar3) <= *(int *)(&DAT_02c04300 + iVar3)) {
          *(undefined4 *)(&DAT_02c04300 + iVar3) = 0;
          *(int *)(&DAT_02c042fc + iVar3) = *(int *)(&DAT_02c042fc + iVar3) + -1;
          if (*(int *)(&DAT_02c042fc + iVar3) < 1) {
            *(undefined4 *)(&DAT_02c04320 + iVar3) = 0;
          }
        }
        *(undefined4 *)(&DAT_02c0431c + iVar3) = *(undefined4 *)(&DAT_02c04318 + iVar3);
      }
    }
    if ((*(int *)(&DAT_02c04320 + iVar3) != 0) && (*(int *)(&DAT_02c04300 + iVar3) != 0)) {
      FUN_007758b0(puVar4,param_1);
    }
  }
  return;
}

