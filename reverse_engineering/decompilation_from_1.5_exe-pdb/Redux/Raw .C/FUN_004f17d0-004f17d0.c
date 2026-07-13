
undefined1 __thiscall FUN_004f17d0(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 local_14;
  
  cVar1 = FUN_004cf640(param_2,param_1 + 0x14c,4,"HuntTask::my_craft",param_1);
  if ((cVar1 == '\0') || (cVar1 = FUN_004e5b10(param_2), cVar1 == '\0')) {
    local_14 = 0;
  }
  else {
    local_14 = 1;
  }
  return local_14;
}

