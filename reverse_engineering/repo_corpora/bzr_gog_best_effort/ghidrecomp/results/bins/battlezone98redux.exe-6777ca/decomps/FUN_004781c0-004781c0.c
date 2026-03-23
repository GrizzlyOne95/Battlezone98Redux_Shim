
undefined1 __thiscall FUN_004781c0(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_1c;
  
  cVar2 = FUN_004cd360(param_2,param_1 + 0x134,4,"attackRangeSq");
  if ((cVar2 == '\0') ||
     (cVar2 = FUN_004cd360(param_2,param_1 + 0x138,4,"waitRangeSq"), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x13c,4,"fleeFrom"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_005ffa70(param_2), cVar2 != '\0')) {
    local_1c = 1;
  }
  else {
    local_1c = 0;
  }
  return local_1c;
}

