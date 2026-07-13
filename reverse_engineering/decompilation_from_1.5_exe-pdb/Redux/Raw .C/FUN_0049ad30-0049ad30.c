
undefined1 __thiscall FUN_0049ad30(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_28;
  
  cVar2 = FUN_004cd360(param_2,param_1 + 0x18,4,&DAT_00877424);
  if ((cVar2 == '\0') || (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x1c,4,"timer"), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x20,4,&DAT_0087743c), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x24,4,"alert"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ccf20(param_2,param_1 + 0x28,1,"countdown"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ccf20(param_2,param_1 + 0x29,1,"active"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ccf20(param_2,param_1 + 0x2a,1,&DAT_00877414), cVar2 != '\0')) {
    local_28 = 1;
  }
  else {
    local_28 = 0;
  }
  return local_28;
}

