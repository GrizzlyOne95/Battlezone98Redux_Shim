
undefined1 __thiscall FUN_004e4b00(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 local_14;
  
  cVar1 = FUN_004cd1b0(param_2,param_1 + 0x150,4,"oneGeyser");
  if ((cVar1 == '\0') || (cVar1 = FUN_004e5cf0(param_2), cVar1 == '\0')) {
    local_14 = 0;
  }
  else {
    local_14 = 1;
  }
  return local_14;
}

