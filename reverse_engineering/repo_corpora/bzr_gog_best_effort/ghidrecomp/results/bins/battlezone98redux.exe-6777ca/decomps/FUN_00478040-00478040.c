
undefined1 __thiscall FUN_00478040(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_1c;
  
  cVar2 = FUN_004ceb10(param_2,param_1 + 0x134,4);
  if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0x138,4), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x13c,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_005fef80(param_2), cVar2 != '\0')) {
    local_1c = 1;
  }
  else {
    local_1c = 0;
  }
  return local_1c;
}

