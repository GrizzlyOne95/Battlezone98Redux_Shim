
undefined1 __thiscall FUN_0049ab50(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_2c;
  undefined1 local_28;
  
  cVar2 = FUN_004ceb10(param_2,param_1 + 0x18,4);
  if ((cVar2 == '\0') || (cVar2 = FUN_004ce910(param_2,param_1 + 0x1c,4), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x20,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x24,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ce5e0(param_2,param_1 + 0x28,1), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ce5e0(param_2,param_1 + 0x29,1), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ce5e0(param_2,param_1 + 0x2a,1), cVar2 != '\0')) {
    local_28 = 1;
  }
  else {
    local_28 = 0;
  }
  if ((*(char *)(param_1 + 0x28) == '\0') || (0xe0f < *(int *)(param_1 + 0x1c))) {
    local_2c = 1;
  }
  else {
    local_2c = 0;
  }
  *(undefined1 *)(param_1 + 0x2b) = local_2c;
  return local_28;
}

