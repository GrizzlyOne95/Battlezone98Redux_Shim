
void __thiscall FUN_0045be90(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 local_8;
  
  FUN_0045be60(param_2,param_3);
  for (local_8 = 0; local_8 < 6; local_8 = local_8 + 1) {
    *(undefined4 *)(param_1 + 0x28 + local_8 * 4) = *(undefined4 *)(param_4 + local_8 * 4);
  }
  *(undefined1 *)(param_1 + 0x40) = 1;
  return;
}

