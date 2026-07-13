
uint __thiscall
FUN_00840080(undefined4 *param_1,uint param_2,uint param_3,ushort *param_4,uint param_5)

{
  uint uVar1;
  ushort *puVar2;
  
  if ((uint)param_1[4] < param_2) {
                    /* WARNING: Subroutine does not return */
    std::_Xout_of_range("invalid string position");
  }
  uVar1 = param_1[4] - param_2;
  if (uVar1 < param_3) {
    param_3 = uVar1;
  }
  if (7 < (uint)param_1[5]) {
    param_1 = (undefined4 *)*param_1;
  }
  uVar1 = param_5;
  if (param_3 < param_5) {
    uVar1 = param_3;
  }
  if (uVar1 != 0) {
    puVar2 = (ushort *)((int)param_1 + param_2 * 2);
    do {
      if (*puVar2 != *param_4) {
        uVar1 = (-(uint)(*puVar2 < *param_4) & 0xfffffffe) + 1;
        goto LAB_008400d7;
      }
      puVar2 = puVar2 + 1;
      param_4 = param_4 + 1;
      uVar1 = uVar1 - 1;
    } while (uVar1 != 0);
  }
  uVar1 = 0;
LAB_008400d7:
  if (uVar1 == 0) {
    if (param_3 < param_5) {
      return 0xffffffff;
    }
    uVar1 = (uint)(param_3 != param_5);
  }
  return uVar1;
}

