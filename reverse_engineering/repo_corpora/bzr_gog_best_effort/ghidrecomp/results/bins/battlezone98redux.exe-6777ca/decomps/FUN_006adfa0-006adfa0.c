
allocator<char> * __fastcall FUN_006adfa0(allocator<char> *param_1)

{
  uint _FileHandle;
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085029c;
  local_10 = ExceptionList;
  _FileHandle = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  std::allocator<char>::allocator<char>(param_1);
  local_8 = 0;
  FUN_006c8c80(1);
  local_8._0_1_ = 1;
  pvVar1 = operator_new(0x20);
  local_8._0_1_ = 2;
  if (pvVar1 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    iVar2 = eof(_FileHandle);
    local_1c = FUN_006d8bb0(param_1,0,iVar2);
  }
  local_8 = CONCAT31(local_8._1_3_,1);
  *(undefined4 *)(param_1 + 4) = local_1c;
  uVar3 = FUN_004f6a80();
  *(undefined4 *)(param_1 + 8) = uVar3;
  ExceptionList = local_10;
  return param_1;
}

