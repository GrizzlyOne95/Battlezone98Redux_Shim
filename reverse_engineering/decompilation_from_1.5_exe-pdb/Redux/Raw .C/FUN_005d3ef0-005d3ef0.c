
char __thiscall FUN_005d3ef0(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  char local_5;
  
  uVar1 = FUN_005c5fd0(*(undefined4 *)(param_1 + 0x238));
  *(undefined4 *)(param_1 + 0x23c) = uVar1;
  local_5 = FUN_004cf520(param_2,param_1 + 0x23c,4,"undefptr");
  if (local_5 != '\0') {
    local_5 = FUN_0047ebf0(param_2);
  }
  return local_5;
}

