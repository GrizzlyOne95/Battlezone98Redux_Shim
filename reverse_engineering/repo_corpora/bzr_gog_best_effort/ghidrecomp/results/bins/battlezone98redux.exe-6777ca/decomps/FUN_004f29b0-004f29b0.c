
int __fastcall FUN_004f29b0(int param_1)

{
  uint uVar1;
  undefined4 local_8;
  
  local_8 = FUN_004da060(*(undefined4 *)(param_1 + 0xf0));
  if (local_8 == 0) {
    *(undefined4 *)(param_1 + 0xf0) = 0;
  }
  else {
    uVar1 = FUN_0045c4b0();
    if ((uVar1 & 0x400) != 0) {
      local_8 = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
  }
  return local_8;
}

