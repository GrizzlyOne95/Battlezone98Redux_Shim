
void __fastcall FUN_0055be40(int param_1)

{
  undefined4 local_c;
  
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x57) = 0;
  *(undefined1 *)(param_1 + 0x56) = 0;
  *(undefined1 *)(param_1 + 0x55) = 0;
  *(undefined1 *)(param_1 + 0x5b) = 0;
  *(undefined1 *)(param_1 + 0x59) = 0;
  *(undefined1 *)(param_1 + 0x5a) = 0;
  *(undefined1 *)(param_1 + 0x5c) = 0;
  *(undefined1 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0x47c34f80;
  *(undefined4 *)(param_1 + 0x80) = 0x47c34f80;
  *(undefined4 *)(param_1 + 0x78) = 0x47c34f80;
  *(undefined4 *)(param_1 + 0x7c) = 0x47c34f80;
  *(undefined4 *)(param_1 + 0x88) = 0x47c34f80;
  *(undefined4 *)(param_1 + 0xec) = 0;
  *(undefined4 *)(param_1 + 0xf0) = 0;
  *(undefined4 *)(param_1 + 0xe8) = 5;
  *(undefined4 *)(param_1 + 0xd4) = 0;
  *(undefined4 *)(param_1 + 0xd8) = 0;
  *(undefined4 *)(param_1 + 0xdc) = 0;
  *(undefined4 *)(param_1 + 0xe0) = 0;
  *(undefined4 *)(param_1 + 0xf4) = 0;
  for (local_c = 0; local_c < *(int *)(param_1 + 0xe8); local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x5d) = 1;
    *(undefined1 *)(param_1 + local_c + 0x67) = 0;
    *(undefined4 *)(param_1 + 0x90 + local_c * 4) = 0;
  }
  return;
}

