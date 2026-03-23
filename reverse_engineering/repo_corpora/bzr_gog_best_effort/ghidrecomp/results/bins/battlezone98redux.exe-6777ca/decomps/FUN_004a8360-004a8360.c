
undefined1 __thiscall FUN_004a8360(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_20;
  
  cVar2 = FUN_004cd1b0(param_2,param_1 + 0x22c,4,"abandoned");
  if ((cVar2 == '\0') ||
     (cVar2 = FUN_0045c3c0(param_2,param_1 + 0x298,4,"cloakState"), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) &&
     (cVar2 = FUN_004cd360(param_2,param_1 + 0x29c,4,"cloakTransBeginTime"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) &&
     (cVar2 = FUN_004cd360(param_2,param_1 + 0x2a0,4,"cloakTransEndTime"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004de110(param_2), cVar2 != '\0')) {
    local_20 = 1;
  }
  else {
    local_20 = 0;
  }
  return local_20;
}

