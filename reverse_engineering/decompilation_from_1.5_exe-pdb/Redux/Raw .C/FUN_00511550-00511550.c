
undefined1 __thiscall FUN_00511550(int param_1,undefined4 param_2)

{
  char cVar1;
  bool bVar2;
  undefined1 local_14;
  
  bVar2 = true;
  if ((0x40d < DAT_00917b20) && (DAT_009173b7 == '\0')) {
    cVar1 = FUN_004ceb10(param_2,param_1 + 0x238,4);
    bVar2 = cVar1 != '\0';
  }
  if ((bVar2) && (cVar1 = FUN_0047eb20(param_2), cVar1 != '\0')) {
    local_14 = 1;
  }
  else {
    local_14 = 0;
  }
  return local_14;
}

