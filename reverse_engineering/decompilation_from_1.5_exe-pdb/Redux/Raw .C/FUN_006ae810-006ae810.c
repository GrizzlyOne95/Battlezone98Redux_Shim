
void __thiscall FUN_006ae810(int *param_1,uint param_2)

{
  undefined4 *puVar1;
  uint local_10;
  uint local_c;
  
  if ((uint)param_1[1] < param_2) {
    local_10 = ((uint)param_1[1] >> 1) + param_1[1];
    if (local_10 < param_2) {
      local_10 = param_2;
    }
    puVar1 = operator_new(local_10 * 4 + 4);
    *puVar1 = *(undefined4 *)*param_1;
    for (local_c = 0; local_c < *(uint *)*param_1; local_c = local_c + 1) {
      puVar1[local_c + 1] = *(undefined4 *)(*param_1 + 4 + local_c * 4);
    }
    operator_delete((void *)*param_1);
    *param_1 = (int)puVar1;
    param_1[1] = local_10;
  }
  return;
}

