
void FUN_00830d93(undefined4 param_1,int param_2)

{
  if (*(undefined **)(param_2 + 0x10) != &DAT_0086eef0) {
    FUN_00838869(param_1,*(undefined4 *)(param_2 + 0x10),(1 << (*(byte *)(param_2 + 7) & 0x1f)) << 5
                 ,0);
  }
  FUN_00838869(param_1,*(undefined4 *)(param_2 + 0xc),*(int *)(param_2 + 0x1c) << 4,0);
  FUN_00838869(param_1,param_2,0x20,0);
  return;
}

