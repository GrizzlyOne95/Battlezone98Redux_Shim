
undefined1 __thiscall FUN_005edc20(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_30;
  
  cVar2 = FUN_004ce910(param_2,param_1 + 0x18,4);
  if ((cVar2 == '\0') || (cVar2 = FUN_004ce910(param_2,param_1 + 0x1c,4), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) &&
     (cVar2 = FUN_004cf640(param_2,param_1 + 0x20,4,"TugProcess::craft",param_1), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ced10(param_2,param_1 + 0x24,0xc), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x30,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) &&
     (cVar2 = FUN_004cf640(param_2,param_1 + 0x34,4,"TugProcess::task",param_1), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ceb10(param_2,param_1 + 0x38,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ced10(param_2,param_1 + 0x3c,0xc), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004616d0(param_2), cVar2 != '\0')) {
    local_30 = 1;
  }
  else {
    local_30 = 0;
  }
  return local_30;
}

