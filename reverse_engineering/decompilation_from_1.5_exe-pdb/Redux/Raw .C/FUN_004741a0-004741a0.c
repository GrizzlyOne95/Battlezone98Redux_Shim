
void __fastcall FUN_004741a0(int param_1)

{
  int iVar1;
  char local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  sprintf(local_58," ArmoryProcess:");
  FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
  sprintf(local_58," State (%s)",(&PTR_s_START_008e76a8)[*(int *)(param_1 + 0x18)]);
  FUN_004b70f0(local_58,DAT_0091755c,DAT_00917584);
  iVar1 = *(int *)(param_1 + 0x18);
  if ((3 < iVar1) && ((iVar1 < 6 || (iVar1 == 8)))) {
    (**(code **)(**(int **)(param_1 + 0x28) + 0x20))();
  }
  FUN_0083e885();
  return;
}

