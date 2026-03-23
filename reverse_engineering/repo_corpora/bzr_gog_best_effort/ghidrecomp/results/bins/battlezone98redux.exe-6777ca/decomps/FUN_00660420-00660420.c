
undefined1 __thiscall FUN_00660420(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_20;
  
  cVar2 = FUN_004cd1b0(param_2,param_1 + 0x244,4,"portalState");
  if ((cVar2 == '\0') ||
     (cVar2 = FUN_004cd360(param_2,param_1 + 0x23c,4,"portalBeginTime"), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004cd360(param_2,param_1 + 0x240,4,"portalEndTime"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ccf20(param_2,param_1 + 0x248,1,&DAT_00891de4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_0047ebf0(param_2), cVar2 != '\0')) {
    local_20 = 1;
  }
  else {
    local_20 = 0;
  }
  return local_20;
}

