
void __thiscall FUN_0049f270(int param_1,int param_2)

{
  int iVar1;
  int local_c;
  
  for (local_c = 0; local_c < 0xb; local_c = local_c + 1) {
    if (*(int *)(param_1 + local_c * 4) != *(int *)(param_2 + local_c * 4)) {
      *(undefined4 *)(param_1 + local_c * 4) = 0;
    }
  }
  *(uint *)(param_1 + 0x2c) = *(uint *)(param_1 + 0x2c) & *(uint *)(param_2 + 0x2c);
  if ((*(int *)(param_1 + 0x30) == *(int *)(param_2 + 0x30)) &&
     (iVar1 = FUN_0046faf0(*(undefined4 *)(param_1 + 0x30)), iVar1 != 0)) {
    return;
  }
  *(undefined4 *)(param_1 + 0x30) = 0xffffffff;
  return;
}

