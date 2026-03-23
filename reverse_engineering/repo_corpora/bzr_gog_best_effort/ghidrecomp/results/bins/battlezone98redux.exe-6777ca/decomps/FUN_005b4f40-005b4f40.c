
char __thiscall FUN_005b4f40(int param_1,undefined4 param_2)

{
  char cVar1;
  char local_10;
  char local_5;
  
  cVar1 = FUN_004cf520(param_2,param_1 + 0x3c,4,"undefptr");
  if ((((cVar1 == '\0') || (cVar1 = FUN_0045c3c0(param_2,param_1 + 0x40,4,"fWhat"), cVar1 == '\0'))
      || (cVar1 = FUN_004cd1b0(param_2,param_1 + 0x44,4,"lastHit"), cVar1 == '\0')) ||
     ((cVar1 = FUN_004cd360(param_2,param_1 + 0x48,4,"attacked"), cVar1 == '\0' ||
      (cVar1 = FUN_004cd360(param_2,param_1 + 0x4c,4,"waitToSetup"), cVar1 == '\0')))) {
    local_10 = '\0';
  }
  else {
    local_10 = '\x01';
  }
  local_5 = local_10;
  if (local_10 != '\0') {
    local_5 = FUN_005b3640(param_2);
  }
  return local_5;
}

