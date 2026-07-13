
undefined4 FUN_00505490(int *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 local_8;
  
  local_8 = 0;
  if ((*(byte *)(*param_1 + -1) & 0x1f) != 0) {
    uVar1 = *(undefined4 *)*param_1;
    *param_1 = *param_1 + 4;
    uVar1 = FUN_004b9ab0(uVar1);
    local_8 = FUN_00477590(uVar1);
  }
  FUN_004ff770(param_2,local_8);
  return 1;
}

