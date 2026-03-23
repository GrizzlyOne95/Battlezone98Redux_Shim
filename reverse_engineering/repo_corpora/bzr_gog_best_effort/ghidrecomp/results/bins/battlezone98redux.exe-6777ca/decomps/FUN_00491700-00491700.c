
void __fastcall FUN_00491700(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_00491000(*(undefined4 *)(param_1 + 0x8030),*(undefined4 *)(param_1 + 0x8034),
                       (float)*(int *)(param_1 + 0x8034) / *(float *)(param_1 + 0x8038),
                       *(undefined4 *)(param_1 + 0x8040),0x3f800000);
  *(undefined4 *)(param_1 + 0x802c) = uVar1;
  return;
}

