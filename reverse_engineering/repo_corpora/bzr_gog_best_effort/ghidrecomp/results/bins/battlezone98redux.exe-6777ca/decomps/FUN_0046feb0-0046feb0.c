
undefined4 __thiscall FUN_0046feb0(int param_1,undefined4 param_2)

{
  char extraout_AL;
  uint uVar1;
  undefined3 uVar2;
  undefined3 extraout_var;
  char local_10;
  char local_5;
  
  uVar1 = FUN_004cd1b0(param_2,param_1 + 0x300,4,"soldierCount");
  if ((uVar1 & 0xff) != 0) {
    uVar1 = FUN_0045c3c0(param_2,param_1 + 0x228,4,"state");
    if ((uVar1 & 0xff) != 0) {
      local_10 = '\x01';
      goto LAB_0046ff0f;
    }
  }
  local_10 = '\0';
LAB_0046ff0f:
  uVar2 = (undefined3)(uVar1 >> 8);
  local_5 = local_10;
  if (local_10 != '\0') {
    FUN_004ea280(param_2);
    uVar2 = extraout_var;
    local_5 = extraout_AL;
  }
  return CONCAT31(uVar2,local_5);
}

