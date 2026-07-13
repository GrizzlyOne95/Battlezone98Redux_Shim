
undefined1 __thiscall FUN_005115f0(int param_1,undefined4 param_2)

{
  char cVar1;
  bool bVar2;
  undefined1 local_14;
  
  bVar2 = true;
  if (DAT_009173b7 == '\0') {
    cVar1 = FUN_004cd360(param_2,param_1 + 0x238,4,"lifeTimer");
    bVar2 = cVar1 != '\0';
  }
  if ((bVar2) && (cVar1 = FUN_0047ebf0(param_2), cVar1 != '\0')) {
    local_14 = 1;
  }
  else {
    local_14 = 0;
  }
  return local_14;
}

