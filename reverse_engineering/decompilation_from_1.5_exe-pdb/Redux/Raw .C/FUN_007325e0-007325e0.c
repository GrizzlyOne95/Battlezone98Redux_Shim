
undefined4 * FUN_007325e0(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 local_c;
  undefined4 *local_8;
  
  uVar1 = FUN_00417780(param_2);
  allocator<>(uVar1);
  *local_8 = 0;
  local_8[1] = param_3;
  local_8[2] = 0;
  if (param_3 != 0) {
    local_c = 0;
    local_8[2] = param_3;
    uVar1 = FUN_00732c20(1,param_3,local_8 + 2,&local_c);
    *local_8 = uVar1;
  }
  return local_8;
}

