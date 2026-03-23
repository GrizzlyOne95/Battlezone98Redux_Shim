
void FUN_006aecc0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined1 local_5;
  
  iVar2 = get();
  if (iVar2 < 0x4d0) {
    if (iVar2 == 0x4cf) {
      FUN_006d8cf0(0x2743);
    }
    else if (iVar2 == 0x79) {
      FUN_006d8cf0(0x274c);
    }
    else if (iVar2 == 0x4c9) {
      FUN_006d8cf0(0x274d);
    }
  }
  else if (iVar2 == 0x4d0) {
    FUN_006d8cf0(0x2751);
  }
  cVar1 = FUN_004c85a0();
  if (cVar1 != '\0') {
    local_5 = 0;
    FUN_006af470(param_1,&local_5,0xffff,0x7010,0,0,param_2,0x7010);
  }
  return;
}

