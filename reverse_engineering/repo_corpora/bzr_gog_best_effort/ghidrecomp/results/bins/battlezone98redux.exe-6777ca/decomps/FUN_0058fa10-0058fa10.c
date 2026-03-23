
int FUN_0058fa10(void)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  wchar_t *pwVar4;
  int local_20;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084be5b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_0058bca0(0x34,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (iVar1 == 0) {
    local_20 = 0;
  }
  else {
    local_20 = FUN_00592010();
  }
  local_8 = 0xffffffff;
  *(undefined4 *)(local_20 + 0x10) = 0;
  *(undefined4 *)(local_20 + 0x14) = 0;
  local_14 = 0;
  while( true ) {
    uVar2 = FUN_0046b240();
    if (uVar2 <= local_14) break;
    uVar3 = FUN_005111d0(local_14);
    FUN_00592230(uVar3);
    local_14 = local_14 + 1;
  }
  local_14 = 0;
  while( true ) {
    uVar2 = FUN_0046b240();
    if (uVar2 <= local_14) break;
    uVar3 = FUN_005111d0(local_14);
    FUN_00592230(uVar3);
    local_14 = local_14 + 1;
  }
  *(undefined4 *)(local_20 + 0x14) = 0;
  pwVar4 = std::
           basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
           back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                 *)(local_20 + 4));
  uVar3 = *(undefined4 *)(pwVar4 + 2);
  *(undefined4 *)(local_20 + 0x18) = *(undefined4 *)pwVar4;
  *(undefined4 *)(local_20 + 0x1c) = uVar3;
  ExceptionList = local_10;
  return local_20;
}

