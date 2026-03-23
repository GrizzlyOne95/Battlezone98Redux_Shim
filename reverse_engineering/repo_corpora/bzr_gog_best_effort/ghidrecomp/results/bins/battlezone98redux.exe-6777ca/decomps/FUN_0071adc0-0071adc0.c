
undefined4 * __thiscall FUN_0071adc0(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  void *pvVar2;
  undefined4 uVar3;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845f6c;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pvVar2 = operator_new(0x10);
  local_8 = 0;
  if (pvVar2 == (void *)0x0) {
    local_18 = 0;
  }
  else {
    uVar3 = FUN_00417780(param_2,uVar1);
    local_18 = FUN_0071bb50(uVar3);
  }
  *param_1 = local_18;
  ExceptionList = local_10;
  return param_1;
}

