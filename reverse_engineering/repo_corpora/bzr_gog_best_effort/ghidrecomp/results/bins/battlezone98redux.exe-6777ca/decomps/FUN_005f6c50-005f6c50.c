
undefined1 __thiscall FUN_005f6c50(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_20;
  
  cVar2 = FUN_004ce5e0(param_2,param_1 + 0x80,1);
  if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0x84,4), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004ceb10(param_2,param_1 + 0x88,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ce5e0(param_2,param_1 + 100,1), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_005f9490(param_2), cVar2 != '\0')) {
    local_20 = 1;
  }
  else {
    local_20 = 0;
  }
  return local_20;
}

