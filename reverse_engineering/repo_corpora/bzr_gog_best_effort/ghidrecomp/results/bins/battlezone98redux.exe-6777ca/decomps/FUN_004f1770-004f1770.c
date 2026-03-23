
undefined1 __fastcall FUN_004f1770(int param_1)

{
  undefined1 local_c;
  
  if ((*(int *)(param_1 + 8) == 0xd) ||
     ((*(int *)(param_1 + 0x40) != 0 && (*(int *)(*(int *)(param_1 + 0x40) + 0x10) == 3)))) {
    local_c = 1;
  }
  else {
    local_c = 0;
  }
  return local_c;
}

