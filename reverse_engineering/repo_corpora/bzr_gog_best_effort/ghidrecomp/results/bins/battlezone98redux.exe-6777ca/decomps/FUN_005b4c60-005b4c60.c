
undefined4 __thiscall FUN_005b4c60(int param_1,undefined4 param_2)

{
  char extraout_AL;
  uint uVar1;
  undefined3 uVar2;
  undefined3 extraout_var;
  char local_10;
  char local_5;
  
  uVar1 = FUN_004cf520(param_2,param_1 + 0x3c,4,"undefptr");
  if ((uVar1 & 0xff) != 0) {
    uVar1 = FUN_0045c3c0(param_2,param_1 + 0x40,4,"fWhat");
    if ((uVar1 & 0xff) != 0) {
      uVar1 = FUN_004cd1b0(param_2,param_1 + 0x44,4,"lastHit");
      if ((uVar1 & 0xff) != 0) {
        uVar1 = FUN_004cd360(param_2,param_1 + 0x48,4,"attacked");
        if ((uVar1 & 0xff) != 0) {
          uVar1 = FUN_004cd360(param_2,param_1 + 0x4c,4,"waitToSetup");
          if ((uVar1 & 0xff) != 0) {
            local_10 = '\x01';
            goto LAB_005b4d22;
          }
        }
      }
    }
  }
  local_10 = '\0';
LAB_005b4d22:
  uVar2 = (undefined3)(uVar1 >> 8);
  local_5 = local_10;
  if (local_10 != '\0') {
    FUN_005b3640(param_2);
    uVar2 = extraout_var;
    local_5 = extraout_AL;
  }
  return CONCAT31(uVar2,local_5);
}

