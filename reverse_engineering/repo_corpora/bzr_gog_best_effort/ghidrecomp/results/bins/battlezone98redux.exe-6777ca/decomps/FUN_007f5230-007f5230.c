
undefined1 FUN_007f5230(undefined4 param_1,long param_2)

{
  char cVar1;
  undefined1 uVar2;
  long lVar3;
  char local_c;
  char local_5;
  
  lVar3 = abs(param_2);
  cVar1 = FUN_007f5d60(param_1,0x65);
  if (cVar1 != '\0') {
    uVar2 = FUN_007f2170(param_2,0,0);
    uVar2 = FUN_007f2150(param_2,uVar2);
    cVar1 = FUN_007f2190(param_1,uVar2);
    if (cVar1 != '\0') {
      local_c = '\x01';
      goto LAB_007f52a1;
    }
  }
  local_c = '\0';
LAB_007f52a1:
  local_5 = local_c;
  if ((local_c != '\0') && (lVar3 < 10)) {
    local_5 = FUN_007f5d60(param_1,0x30);
  }
  if ((local_5 != '\0') && (cVar1 = FUN_007f5da0(param_1,lVar3), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}

