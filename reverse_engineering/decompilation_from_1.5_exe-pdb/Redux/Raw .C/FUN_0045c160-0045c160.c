
char __thiscall FUN_0045c160(int param_1,undefined4 param_2)

{
  char cVar1;
  int local_1c;
  char local_18;
  char local_14;
  undefined4 local_10;
  int local_c;
  char local_5;
  
  local_c = param_1;
  cVar1 = FUN_004ce910(param_2,param_1,4);
  if (((cVar1 != '\0') && (cVar1 = FUN_0045c370(param_2,local_c + 4,4), cVar1 != '\0')) &&
     (cVar1 = FUN_004ce910(param_2,local_c + 8,4), cVar1 != '\0')) {
    cVar1 = FUN_004cf640(param_2,local_c + 0xc,4,"AiCmdInfo:where",local_c);
    if (cVar1 != '\0') {
      local_10 = 1;
      goto LAB_0045c1ef;
    }
  }
  local_10 = 0;
LAB_0045c1ef:
  local_5 = (char)local_10;
  if (DAT_00917b20 < 0x7dc) {
    if (((char)local_10 == '\0') || (cVar1 = FUN_004ce910(param_2,&local_1c,4), cVar1 == '\0')) {
      local_14 = '\0';
    }
    else {
      local_14 = '\x01';
    }
    local_5 = local_14;
    if (local_14 != '\0') {
      *(int *)(local_c + 0x18) = local_1c;
      *(int *)(local_c + 0x1c) = local_1c >> 0x1f;
    }
  }
  else {
    if (((char)local_10 == '\0') || (cVar1 = FUN_004cf210(param_2,local_c + 0x18,8), cVar1 == '\0'))
    {
      local_18 = '\0';
    }
    else {
      local_18 = '\x01';
    }
    local_5 = local_18;
  }
  return local_5;
}

