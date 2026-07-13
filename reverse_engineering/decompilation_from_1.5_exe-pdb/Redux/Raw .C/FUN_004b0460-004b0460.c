
void __thiscall FUN_004b0460(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 local_48 [10];
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((*(uint *)(*(int *)(param_1 + 0x228) + 0x114) & 4) == 0) {
    if (*(char *)(param_1 + 0x230) == '\0') {
      *(undefined1 *)(param_1 + 0x230) = 1;
      FUN_0062de40(*(undefined4 *)(param_1 + 0xf4),&DAT_01400200);
      *(uint *)(*(int *)(param_1 + 0x228) + 0x114) =
           *(uint *)(*(int *)(param_1 + 0x228) + 0x114) | 0x20;
      if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x800) != 0) {
        FUN_0068a2d0(*(undefined4 *)(param_1 + 0xf4));
      }
      FUN_007809d0(*(undefined4 *)(param_1 + 0x108),*(undefined4 *)(param_1 + 0x110),
                   *(undefined4 *)(*(int *)(param_1 + 0xf8) + 0x17c));
      iVar1 = *(int *)(*(int *)(param_1 + 0xf8) + 0x178);
      if (iVar1 == 0) {
        FUN_007d6c70("%s missing xplBlast\n",*(int *)(param_1 + 0xf8) + 0x38);
      }
      puVar3 = (undefined4 *)(*(int *)(param_1 + 0xf4) + 0x20);
      puVar4 = local_48;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      local_20 = (double)*(float *)(param_1 + 0x108);
      local_18 = (double)*(float *)(param_1 + 0x10c);
      local_10 = (double)*(float *)(param_1 + 0x110);
      (**(code **)(*(int *)(param_1 + 0x18) + 0x10))();
      if (iVar1 != 0) {
        FUN_004cb7b0(local_48,0);
      }
    }
  }
  else {
    FUN_005a7d70(param_2);
  }
  FUN_0083e885();
  return;
}

