
/* WARNING: Removing unreachable block (ram,0x0070b574) */
/* WARNING: Removing unreachable block (ram,0x0070b5c9) */
/* WARNING: Removing unreachable block (ram,0x0070b5ab) */
/* WARNING: Removing unreachable block (ram,0x0070b5d0) */

void __thiscall FUN_0070b4b0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 local_28;
  allocator<char> local_12 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008575d2;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  cVar1 = _Test_callable<>(param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (cVar1 == '\0') {
    Set(0);
  }
  else {
    iVar2 = forward<>(0x10,param_1);
    local_8 = 0;
    if (iVar2 == 0) {
      local_28 = 0;
    }
    else {
      uVar3 = std::allocator<char>::allocator<char>(local_12);
      uVar4 = FUN_00417780(param_2,uVar3);
      local_28 = _Func_impl<>(uVar4,uVar3);
    }
    local_8 = 0xffffffff;
    Set(local_28);
  }
  ExceptionList = local_10;
  return;
}

