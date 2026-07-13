
undefined4 * __fastcall FUN_00808ac0(undefined4 *param_1)

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
  pvVar2 = operator_new(0x68);
  local_8 = 0;
  if (pvVar2 == (void *)0x0) {
    local_18 = 0;
  }
  else {
    uVar3 = FUN_00421ec0(uVar1);
    local_18 = FUN_00809380(uVar3);
  }
  *param_1 = local_18;
  ExceptionList = local_10;
  return param_1;
}

