
undefined4 __fastcall FUN_00581870(int param_1)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 0x80) == '\0') {
    uVar1 = 0x55;
  }
  else if (*(char *)(param_1 + 0x80) == '\x01') {
    uVar1 = 0x4c;
  }
  else {
    uVar1 = 0x52;
  }
  return uVar1;
}

