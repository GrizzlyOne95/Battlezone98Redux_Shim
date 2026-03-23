
void FUN_007ea0e0(void)

{
  uint uVar1;
  void *pvVar2;
  undefined4 *in_stack_00000024;
  undefined4 extraout_var;
  undefined4 uVar3;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00863e04;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  pvVar2 = operator_new(0x20);
  local_8 = CONCAT31(local_8._1_3_,1);
  uVar3 = extraout_var;
  if (pvVar2 == (void *)0x0) {
    local_18 = 0;
  }
  else {
    local_18 = FUN_007dd560(&stack0x00000004);
  }
  *in_stack_00000024 = local_18;
  local_8 = 0xffffffff;
  FUN_007db9d0(uVar1,uVar3);
  ExceptionList = local_10;
  return;
}

