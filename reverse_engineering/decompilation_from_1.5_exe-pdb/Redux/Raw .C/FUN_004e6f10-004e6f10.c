
undefined1 __thiscall FUN_004e6f10(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_1c;
  
  cVar2 = FUN_004cd360(param_2,param_1 + 0x14c,4,"nearSq");
  if ((cVar2 == '\0') || (cVar2 = FUN_004ccf20(param_2,param_1 + 0x150,1,"wasNear"), cVar2 == '\0'))
  {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004cd360(param_2,param_1 + 0x154,4,"nearTime"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004e5cf0(param_2), cVar2 != '\0')) {
    local_1c = 1;
  }
  else {
    local_1c = 0;
  }
  return local_1c;
}

