
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00623b20(int *param_1,int *param_2,uint *param_3)

{
  int iVar1;
  float10 fVar2;
  int local_18;
  int local_14;
  float local_10;
  int local_c;
  int local_8;
  
  iVar1 = FUN_00435160();
  if (iVar1 == 1) {
    if ((DAT_00920158 != 0) && (DAT_0092015c != 0)) {
      FUN_00623e30(&DAT_02cebcb0,DAT_02cecf00,DAT_02cecf04);
      FUN_004351e0(&DAT_02cebcb0);
      FUN_00623ac0(param_1,0);
      FUN_00623ac0(param_1,1);
      FUN_00623ac0(param_1,2);
      FUN_00623ac0(param_1,3);
      DAT_0092015c = 1;
      DAT_00920158 = 0;
    }
    if (param_3 != (uint *)0x0) {
      *param_3 = DAT_02cebcac;
      DAT_02cebcac = ~DAT_02cebca8 & DAT_02cebcac;
      DAT_02cebca8 = 0;
    }
    if (param_2 != (int *)0x0) {
      fVar2 = (float10)FUN_00822d60();
      local_10 = (float)fVar2;
      _DAT_02a17470 = local_10 + _DAT_02a17470;
      if (0.016666 <= _DAT_02a17470) {
        local_8 = *(int *)(&DAT_008ec494 + *(int *)(DAT_0094672c + 0x38) * 4);
        if (DAT_00918424 != 0) {
          local_c = (int)(SQRT((float)(DAT_02cebca0 * DAT_02cebca0 + DAT_02cebca4 * DAT_02cebca4)) /
                         _DAT_02a17470);
          if (local_c < 0x180) {
            local_8 = (local_c + 0x80) * local_8 >> 8;
          }
          else {
            local_8 = local_8 << 1;
          }
        }
        DAT_02cebca0 = DAT_02cebca0 * local_8;
        DAT_02cebca4 = DAT_02cebca4 * local_8;
        param_1[1] = (int)((float)DAT_02cebca0 / _DAT_02a17470);
        *param_1 = *param_1 + DAT_02cebca0;
        if (*param_1 < -0x10000) {
          *param_1 = -0x10000;
        }
        else if (0x10000 < *param_1) {
          *param_1 = 0x10000;
        }
        param_1[3] = (int)((float)DAT_02cebca4 / _DAT_02a17470);
        param_1[2] = param_1[2] + DAT_02cebca4;
        if (param_1[2] < -0x10000) {
          param_1[2] = -0x10000;
        }
        else if (0x10000 < param_1[2]) {
          param_1[2] = 0x10000;
        }
        *param_2 = *param_1;
        param_2[1] = param_1[1];
        param_2[2] = param_1[2];
        param_2[3] = param_1[3];
        local_18 = DAT_02cecf00 >> 1;
        local_14 = DAT_02cecf04 >> 1;
        FUN_004350e0(&local_18);
        DAT_02cebca0 = 0;
        DAT_02cebca4 = 0;
        _DAT_02a17470 = 0.0;
      }
    }
  }
  else {
    _DAT_02a17470 = 0.0;
    if (param_3 != (uint *)0x0) {
      *param_3 = 0;
    }
  }
  return 0;
}

