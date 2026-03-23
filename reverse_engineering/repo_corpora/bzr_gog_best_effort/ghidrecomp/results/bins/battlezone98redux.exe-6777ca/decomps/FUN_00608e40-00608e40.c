
undefined1 __thiscall FUN_00608e40(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_24;
  
  cVar2 = FUN_004ce910(param_2,param_1 + 0x1c,4);
  bVar1 = true;
  if (cVar2 == '\0') {
    cVar2 = FUN_004cf640(param_2,&DAT_02a13d8c,4,"UserProcess::dummyPtr",param_1);
    if ((cVar2 == '\0') || (cVar2 = FUN_004ce910(param_2,param_1 + 0x1c,4), cVar2 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
  }
  if ((bVar1) && (cVar2 = FUN_004ce400(param_2,param_1 + 0x24,0x28), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ce400(param_2,param_1 + 0x4c,0x28), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004616d0(param_2), cVar2 != '\0')) {
    local_24 = 1;
  }
  else {
    local_24 = 0;
  }
  return local_24;
}

