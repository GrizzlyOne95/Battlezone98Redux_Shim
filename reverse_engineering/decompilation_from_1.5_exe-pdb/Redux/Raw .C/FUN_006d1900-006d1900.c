
void FUN_006d1900(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_28 [4];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853178;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = CXMLNode<>(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  local_1c = uVar1;
  local_18 = uVar1;
  FUN_0042de50(uVar1);
  FUN_006d5210(uVar1);
  local_8 = 0xffffffff;
  ~<>();
  local_20 = param_1;
  puVar2 = (undefined4 *)FUN_0042d8c0(local_28);
  local_24 = *puVar2;
  FUN_006d5150(local_24,local_14 + 4,local_20);
  ExceptionList = local_10;
  return;
}

