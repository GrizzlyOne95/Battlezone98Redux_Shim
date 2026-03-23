
undefined1 __thiscall FUN_005f6ea0(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_20;
  
  cVar2 = FUN_004ccf20(param_2,param_1 + 0x80,1,"waitDeploy");
  if ((cVar2 == '\0') ||
     (cVar2 = FUN_004cd360(param_2,param_1 + 0x84,4,"waitDeployTime"), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004cd360(param_2,param_1 + 0x88,4,"nextAttackTime"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ccf20(param_2,param_1 + 100,1,"attackUser"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_005f9ab0(param_2), cVar2 != '\0')) {
    local_20 = 1;
  }
  else {
    local_20 = 0;
  }
  return local_20;
}

