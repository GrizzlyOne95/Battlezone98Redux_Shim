
void __thiscall FUN_0045b950(uint *param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  uint local_c;
  
  if (param_1[1] <= *param_1) {
    local_c = (*param_1 >> 1) + *param_1;
    if (local_c < 0x40) {
      local_c = 0x40;
    }
    FUN_0045b820(local_c);
  }
  puVar2 = (undefined4 *)(param_1[2] + *param_1 * 0x28);
  for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar2 = puVar2 + 1;
  }
  *param_1 = *param_1 + 1;
  return;
}

