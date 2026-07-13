
undefined4 FUN_007606d0(uint *param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 local_8;
  
  if ((param_3 == 0) || (3 < param_3)) {
    local_8 = 0x20;
    while (local_8 != 0) {
      local_8 = local_8 + -8;
      uVar1 = *param_1;
      puVar3 = (undefined1 *)FUN_00421ec0();
      *puVar3 = (char)(uVar1 >> ((byte)local_8 & 0x1f));
      FUN_004f5330();
    }
    uVar2 = 4;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

