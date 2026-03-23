
/* WARNING: Removing unreachable block (ram,0x0070b134) */
/* WARNING: Removing unreachable block (ram,0x0070b189) */
/* WARNING: Removing unreachable block (ram,0x0070b16b) */
/* WARNING: Removing unreachable block (ram,0x0070b190) */

void __thiscall FUN_0070b070(undefined4 param_1,_func_bool_agent_status_ptr **param_2)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 local_28;
  allocator<char> local_12 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008575d2;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  bVar1 = std::_Test_callable<bool_(__cdecl*)(enum_Concurrency::agent_status_const&)>(param_2);
  if (bVar1) {
    iVar3 = forward<>(0xc,param_1,uVar2);
    local_8 = 0;
    if (iVar3 == 0) {
      local_28 = 0;
    }
    else {
      uVar4 = std::allocator<char>::allocator<char>(local_12);
      uVar5 = FUN_00417780(param_2,uVar4);
      local_28 = _Func_impl<>(uVar5,uVar4);
    }
    local_8 = 0xffffffff;
    Set(local_28);
  }
  else {
    Set(0);
  }
  ExceptionList = local_10;
  return;
}

