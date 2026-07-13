
void __thiscall FUN_004a6f00(int param_1,int param_2)

{
  undefined4 local_8;
  
  *(undefined4 *)(param_1 + 0xfc4 + param_2 * 4) = *(undefined4 *)(param_1 + 0x188);
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x188); local_8 = local_8 + 1) {
    *(undefined4 *)(param_1 + 0x18c + param_2 * 0x16c + local_8 * 4) =
         *(undefined4 *)(param_1 + 0x1c + local_8 * 4);
  }
  return;
}

