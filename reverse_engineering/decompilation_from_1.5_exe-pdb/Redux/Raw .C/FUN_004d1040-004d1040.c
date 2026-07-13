
void __fastcall FUN_004d1040(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_00491000(*(undefined4 *)(param_1 + 0x648),*(undefined4 *)(param_1 + 0x64c),
                       (float)*(int *)(param_1 + 0x64c) / *(float *)(param_1 + 0x650),
                       *(undefined4 *)(param_1 + 0x658),*(undefined4 *)(param_1 + 0x65c));
  *(undefined4 *)(param_1 + 0x644) = uVar1;
  return;
}

