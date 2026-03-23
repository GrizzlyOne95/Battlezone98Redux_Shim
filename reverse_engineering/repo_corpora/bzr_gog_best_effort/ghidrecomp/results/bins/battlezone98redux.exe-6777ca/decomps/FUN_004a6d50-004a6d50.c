
void __fastcall FUN_004a6d50(int param_1)

{
  undefined4 local_c;
  
  for (local_c = 0; local_c < *(int *)(param_1 + 0x188); local_c = local_c + 1) {
    FUN_004da060(*(undefined4 *)(param_1 + 0x1c + local_c * 4));
    FUN_0049f3c0(0);
  }
  *(undefined4 *)(param_1 + 0x188) = 0;
  *(undefined4 *)(param_1 + 0x117c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1188) = 0;
  return;
}

