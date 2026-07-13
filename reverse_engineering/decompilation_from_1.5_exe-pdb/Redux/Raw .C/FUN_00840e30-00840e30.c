
void __thiscall FUN_00840e30(undefined4 *param_1,uint param_2)

{
  undefined4 *puVar1;
  
  if ((param_2 != 0) && (param_2 < (uint)param_1[4])) {
    puVar1 = param_1;
    if (7 < (uint)param_1[5]) {
      puVar1 = (undefined4 *)*param_1;
    }
    if (*(short *)((int)puVar1 + param_2 * 2 + 2) != 0x2f) {
      if (7 < (uint)param_1[5]) {
        param_1 = (undefined4 *)*param_1;
      }
      if (*(short *)((int)param_1 + param_2 * 2 + 2) != 0x5c) {
        return;
      }
    }
    FID_conflict_erase(param_2,1);
  }
  return;
}

