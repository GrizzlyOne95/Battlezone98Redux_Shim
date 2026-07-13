
undefined4 FUN_00760670(undefined4 param_1,undefined4 param_2,uint param_3)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 local_8;
  
  if ((param_3 == 0) || (7 < param_3)) {
    local_8 = 0x40;
    while (local_8 != 0) {
      local_8 = local_8 + -8;
      uVar1 = __aullshr();
      puVar3 = (undefined1 *)FUN_00421ec0();
      *puVar3 = uVar1;
      FUN_004f5330();
    }
    uVar2 = 8;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

