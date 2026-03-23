
undefined1 __thiscall FUN_00582ea0(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_28;
  
  cVar2 = FUN_004ccf20(param_2,param_1 + 0x5c,1,"isFriend");
  if ((cVar2 == '\0') ||
     (cVar2 = FUN_004cd360(param_2,param_1 + 0x68,4,"engageRange"), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004cd360(param_2,param_1 + 0x6c,4,"followRange"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd360(param_2,param_1 + 0x70,4,"weaponRange"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd360(param_2,param_1 + 0x74,4,"madTime"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ccf20(param_2,param_1 + 0x78,1,"attackUser"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_005f9ab0(param_2), cVar2 != '\0')) {
    local_28 = 1;
  }
  else {
    local_28 = 0;
  }
  return local_28;
}

