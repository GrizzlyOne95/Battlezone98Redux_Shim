
undefined1 __thiscall FUN_005a7c20(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  
  if (DAT_009173b7 == '\0') {
    FUN_004cea20(param_2,*(int *)(param_1 + 0x228) + 0x114,4);
  }
  uVar1 = FUN_004dd370(param_2);
  if (*(float *)(param_1 + 0x200) <= 0.0 && *(float *)(param_1 + 0x200) != 0.0) {
    *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) =
         *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) | 0x1000000;
  }
  return uVar1;
}

