
undefined1 __thiscall FUN_004a7440(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 local_14;
  
  cVar1 = FUN_004ccd80(param_2,param_1 + 0xfc4,0x28,"groupNum");
  if ((cVar1 == '\0') ||
     (cVar1 = FUN_004ccd80(param_2,param_1 + 0x18c,0xe38,"groupList"), cVar1 == '\0')) {
    local_14 = 0;
  }
  else {
    local_14 = 1;
  }
  return local_14;
}

