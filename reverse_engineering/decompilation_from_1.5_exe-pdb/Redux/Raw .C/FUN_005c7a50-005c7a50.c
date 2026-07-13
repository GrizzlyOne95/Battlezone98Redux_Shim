
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_005c7a50(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined3 uVar3;
  undefined2 extraout_var_00;
  undefined2 uVar4;
  undefined3 extraout_var;
  float10 extraout_ST0;
  int local_10;
  int local_c;
  
  while (iVar1 = FUN_0061a050(), iVar1 != 0) {
    FUN_007d6a70("fsm_pop_camera called again\n");
    FUN_00821ec0();
  }
  uVar2 = FUN_00822d80();
  _DAT_009182a8 = (float)extraout_ST0;
  if (DAT_009173b7 == '\0') {
    for (local_10 = 0; local_10 < DAT_02a13d84; local_10 = local_10 + 1) {
      uVar2 = FUN_005ce740(local_10);
      uVar2 = FUN_006a37a0(0xffffffff,uVar2);
      iVar1 = FUN_005ce740(local_10);
      *(undefined4 *)(iVar1 + 0x10) = uVar2;
    }
    for (local_c = 0; local_c < 0x10; local_c = local_c + 1) {
      if (-1 < *(int *)(&DAT_02a13d20 + local_c * 4)) {
        iVar1 = FUN_005ce740(*(undefined4 *)(&DAT_02a13d20 + local_c * 4));
        FUN_006a3840(local_c,*(undefined4 *)(iVar1 + 0x10));
      }
    }
    uVar4 = 0;
    if (DAT_02a13d64 != '\0') {
      DAT_02a13c7b = 1;
      FUN_00621790();
      uVar4 = extraout_var_00;
    }
    uVar3 = CONCAT21(uVar4,(DAT_02a13d88 == 0.0) << 6 | NAN(DAT_02a13d88) << 2 | 2U |
                           DAT_02a13d88 < 0.0);
    if (DAT_02a13d88 != 0.0) {
      FUN_004c0bb0(DAT_02a13d88);
      uVar3 = extraout_var;
    }
  }
  else {
    uVar3 = (undefined3)((uint)uVar2 >> 8);
  }
  return CONCAT31(uVar3,1);
}

