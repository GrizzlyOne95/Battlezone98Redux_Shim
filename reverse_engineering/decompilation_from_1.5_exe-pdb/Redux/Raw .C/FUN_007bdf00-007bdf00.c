
undefined4 * FUN_007bdf00(undefined4 *param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 in_stack_00000018;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00861b00;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  while( true ) {
    cVar1 = FUN_0066e6d0(&stack0x00000008,&stack0x00000010,uVar2);
    if (cVar1 == '\0') break;
    uVar3 = FUN_007be100();
    std::allocator<char>::allocator<char>((allocator<char> *)&stack0x00000018);
    FUN_007be150(uVar3);
    std::allocator<char>::allocator<char>((allocator<char> *)&stack0x00000018);
    FUN_007be120();
  }
  *param_1 = in_stack_00000018;
  local_8 = local_8 & 0xffffff00;
  FUN_00667660();
  local_8 = 0xffffffff;
  FUN_00667660();
  ExceptionList = local_10;
  return param_1;
}

