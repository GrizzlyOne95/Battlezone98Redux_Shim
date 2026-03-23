
undefined1 __thiscall FUN_004e5b10(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_24;
  
  cVar2 = FUN_004cf640(param_2,param_1 + 0x134,4,"GotoTask::path",param_1);
  if ((cVar2 == '\0') || (cVar2 = FUN_004ce910(param_2,param_1 + 0x138,4), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004ce5e0(param_2,param_1 + 0x13c,1), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (0x40b < DAT_00917b20) {
    if ((bVar1) && (cVar2 = FUN_004ce5e0(param_2,param_1 + 0x13d,1), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  if ((bVar1) && (cVar2 = FUN_004ced10(param_2,param_1 + 0x140,0xc), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_005fef80(param_2), cVar2 != '\0')) {
    local_24 = 1;
  }
  else {
    local_24 = 0;
  }
  return local_24;
}

