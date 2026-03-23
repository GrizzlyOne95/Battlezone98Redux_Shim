
undefined4 __fastcall FUN_00492ce0(int param_1)

{
  undefined4 local_c;
  
  if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x200) == 0) {
    local_c = *(undefined4 *)(param_1 + 0x16c);
  }
  else {
    local_c = *(undefined4 *)(param_1 + 0x170);
  }
  return local_c;
}

