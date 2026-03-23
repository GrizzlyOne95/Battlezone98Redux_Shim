
undefined1 __thiscall FUN_0047ebf0(int param_1,undefined4 param_2)

{
  char cVar1;
  bool bVar2;
  undefined1 local_14;
  
  bVar2 = true;
  if (DAT_009173b7 == '\0') {
    cVar1 = FUN_004ccf20(param_2,param_1 + 0x234,1,"tempBuilding");
    bVar2 = cVar1 != '\0';
  }
  if ((bVar2) && (cVar1 = FUN_004de110(param_2), cVar1 != '\0')) {
    local_14 = 1;
  }
  else {
    local_14 = 0;
  }
  return local_14;
}

