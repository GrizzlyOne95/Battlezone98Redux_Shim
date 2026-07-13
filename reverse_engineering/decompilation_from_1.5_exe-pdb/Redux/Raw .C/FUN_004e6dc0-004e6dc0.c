
undefined1 __thiscall FUN_004e6dc0(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_1c;
  
  cVar2 = FUN_004ceb10(param_2,param_1 + 0x14c,4);
  if ((cVar2 == '\0') || (cVar2 = FUN_004ce5e0(param_2,param_1 + 0x150,1), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004ceb10(param_2,param_1 + 0x154,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004e5b10(param_2), cVar2 != '\0')) {
    local_1c = 1;
  }
  else {
    local_1c = 0;
  }
  return local_1c;
}

