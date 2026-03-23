
char __thiscall FUN_00608fe0(int param_1,undefined4 param_2)

{
  char cVar1;
  char local_10;
  char local_5;
  
  cVar1 = FUN_004cd1b0(param_2,param_1 + 0x1c,4,"cycle");
  if (((cVar1 == '\0') ||
      (cVar1 = FUN_004ccd80(param_2,param_1 + 0x24,0x28,"selectList"), cVar1 == '\0')) ||
     (cVar1 = FUN_004ccd80(param_2,param_1 + 0x4c,0x28,"selectNext"), cVar1 == '\0')) {
    local_10 = '\0';
  }
  else {
    local_10 = '\x01';
  }
  local_5 = local_10;
  if (local_10 != '\0') {
    local_5 = FUN_004617b0(param_2);
  }
  return local_5;
}

