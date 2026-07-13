
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00442d30(int *param_1)

{
  int iVar1;
  undefined4 *local_c;
  undefined4 *local_8;
  
  if ((param_1 == (int *)0x0) || (*param_1 == 0)) {
    FUN_007d6a70("DeleteCollisionEntity called with NULL entity or obj76\n");
  }
  else {
    if (param_1[9] != 0) {
      iVar1 = FUN_0062e000(*param_1);
      if (iVar1 == 0) {
        local_c = &DAT_0260d0f0;
      }
      else {
        local_c = &DAT_0260cac4;
      }
      for (local_8 = (undefined4 *)*local_c; local_8 != (undefined4 *)0x0;
          local_8 = (undefined4 *)*local_8) {
        if ((int *)local_8[2] == param_1) {
          if (local_8 == DAT_0260d0ec) {
            FUN_00443650();
          }
          FUN_00443a00(param_1);
          _DAT_0260d0e8 = 0;
          FUN_008245a0(local_c,local_8);
          break;
        }
      }
    }
    iVar1 = FUN_00445220(*param_1);
    if (iVar1 != 0) {
      FUN_00444f20(param_1);
    }
  }
  return;
}

