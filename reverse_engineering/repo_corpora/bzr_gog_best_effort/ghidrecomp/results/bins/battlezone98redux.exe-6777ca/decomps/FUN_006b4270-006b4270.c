
void __fastcall FUN_006b4270(int param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00850813;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x30),4,0xc1,FUN_006ca3f0);
  local_8 = local_8 & 0xffffff00;
  FUN_006ac0b0(uVar1);
  local_8 = 0xffffffff;
  FUN_006ad050();
  ExceptionList = local_10;
  return;
}

