
bool __thiscall FUN_006602a0(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  bool local_24;
  
  if (DAT_00917b20 < 0x7d4) {
    cVar2 = FUN_0047eb20(param_2);
    local_24 = cVar2 != '\0';
  }
  else {
    cVar2 = FUN_004ce910(param_2,param_1 + 0x244,4);
    if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0x23c,4), cVar2 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if ((bVar1) && (cVar2 = FUN_004ceb10(param_2,param_1 + 0x240,4), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) && (cVar2 = FUN_004ce5e0(param_2,param_1 + 0x248,1), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) && (cVar2 = FUN_0047eb20(param_2), cVar2 != '\0')) {
      local_24 = true;
    }
    else {
      local_24 = false;
    }
  }
  return local_24;
}

