
/* WARNING: Removing unreachable block (ram,0x00734998) */
/* WARNING: Removing unreachable block (ram,0x00734a05) */
/* WARNING: Removing unreachable block (ram,0x00734a24) */
/* WARNING: Removing unreachable block (ram,0x00734a16) */

allocator<char> * __thiscall FUN_00734900(allocator<char> *param_1,allocator<char> *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859a78;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = std::allocator<char>::allocator<char>(param_1);
  uVar3 = std::allocator<char>::allocator<char>(param_2);
  operator==<>(uVar2,uVar3,uVar1);
  FUN_0072d4c0();
  FUN_00734a50(param_2);
  uVar2 = std::allocator<char>::allocator<char>(param_2);
  uVar2 = FUN_00417780(uVar2);
  std::allocator<char>::allocator<char>(param_1);
  FUN_00734a80(uVar2);
  ExceptionList = local_10;
  return param_1;
}

