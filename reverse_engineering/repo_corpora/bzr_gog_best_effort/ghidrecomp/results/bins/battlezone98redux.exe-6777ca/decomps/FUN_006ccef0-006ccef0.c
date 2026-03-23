
undefined4 FUN_006ccef0(void)

{
  undefined4 *puVar1;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852c98;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  vector<>(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  puVar1 = (undefined4 *)FUN_006dd0e0(local_18,local_14);
  FUN_006dd100(local_1c,"not-a-date-time",&DAT_0089628b,*puVar1);
  ExceptionList = local_10;
  return local_14;
}

