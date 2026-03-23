
undefined1 __thiscall FUN_004a73a0(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 local_14;
  
  cVar1 = FUN_004ce400(param_2,param_1 + 0xfc4,0x28);
  if ((cVar1 == '\0') || (cVar1 = FUN_004ce400(param_2,param_1 + 0x18c,0xe38), cVar1 == '\0')) {
    local_14 = 0;
  }
  else {
    local_14 = 1;
  }
  return local_14;
}

