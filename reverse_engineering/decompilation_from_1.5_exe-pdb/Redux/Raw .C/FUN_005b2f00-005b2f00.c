
char __thiscall FUN_005b2f00(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  char local_5;
  
  uVar1 = FUN_005c5fd0(*(undefined4 *)(param_1 + 0x370));
  *(undefined4 *)(param_1 + 0x374) = uVar1;
  local_5 = FUN_004cf520(param_2,param_1 + 0x374,4,"undefptr");
  if (local_5 != '\0') {
    local_5 = FUN_005aff90(param_2);
  }
  return local_5;
}

