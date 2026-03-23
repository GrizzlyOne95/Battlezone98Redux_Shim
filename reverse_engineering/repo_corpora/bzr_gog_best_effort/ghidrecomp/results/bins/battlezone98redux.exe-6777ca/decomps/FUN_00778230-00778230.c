
void __fastcall FUN_00778230(int param_1)

{
  undefined4 local_c;
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
    for (local_c = 0; local_c < 4; local_c = local_c + 1) {
      *(undefined1 *)(param_1 + 0x270 + local_8 * 4 + local_c) = 1;
    }
  }
  return;
}

