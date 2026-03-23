
undefined1 __thiscall FUN_004617b0(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_18;
  
  cVar2 = FUN_004cf520(param_2,param_1 + 8,4,"fMission");
  if ((cVar2 == '\0') || (cVar2 = FUN_004cf520(param_2,param_1 + 0xc,4,"fOwner"), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x14,4,"exited"), cVar2 != '\0')) {
    local_18 = 1;
  }
  else {
    local_18 = 0;
  }
  return local_18;
}

