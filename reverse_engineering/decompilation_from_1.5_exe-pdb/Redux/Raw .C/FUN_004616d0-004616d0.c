
undefined1 __thiscall FUN_004616d0(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_18;
  
  cVar2 = FUN_004cf640(param_2,param_1 + 8,4,"AiProcess::fMission",param_1);
  if ((cVar2 == '\0') ||
     (cVar2 = FUN_004cf640(param_2,param_1 + 0xc,4,"AiProcess::fOwner",param_1), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x14,4), cVar2 != '\0')) {
    local_18 = 1;
  }
  else {
    local_18 = 0;
  }
  return local_18;
}

