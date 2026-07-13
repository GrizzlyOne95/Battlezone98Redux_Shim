
void __fastcall FUN_0044d5c0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0084677e;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = MultiRender::vftable;
  local_8 = 1;
  if ((param_1[0x5e] != 0) && (param_1[0x5e] != 0)) {
    FUN_0044d550(3);
  }
  local_8 = local_8 & 0xffffff00;
  _eh_vector_destructor_iterator_(param_1 + 0x1e,4,0x40,FUN_0044dc30);
  local_8 = 0xffffffff;
  FUN_0044ddc0(uVar1);
  ExceptionList = local_10;
  return;
}

