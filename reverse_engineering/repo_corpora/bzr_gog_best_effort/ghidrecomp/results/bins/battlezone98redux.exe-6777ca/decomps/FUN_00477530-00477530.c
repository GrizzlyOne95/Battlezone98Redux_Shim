
void __thiscall FUN_00477530(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 local_c;
  
  *(undefined4 *)(param_1 + 0x10) = param_2;
  FUN_00421b30(*(undefined4 *)(param_1 + 0x10));
  for (local_c = 0; local_c < *(int *)(param_1 + 0x10); local_c = local_c + 1) {
    puVar1 = (undefined4 *)FUN_004200d0(local_c);
    *puVar1 = 0;
  }
  return;
}

