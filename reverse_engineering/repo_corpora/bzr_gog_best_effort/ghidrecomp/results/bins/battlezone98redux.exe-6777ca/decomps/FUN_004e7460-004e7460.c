
undefined1 __thiscall FUN_004e7460(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 local_14;
  
  cVar1 = FUN_004cf520(param_2,param_1 + 0x14c,4,"lastPlan");
  if ((cVar1 == '\0') || (cVar1 = FUN_004e5cf0(param_2), cVar1 == '\0')) {
    local_14 = 0;
  }
  else {
    local_14 = 1;
  }
  return local_14;
}

