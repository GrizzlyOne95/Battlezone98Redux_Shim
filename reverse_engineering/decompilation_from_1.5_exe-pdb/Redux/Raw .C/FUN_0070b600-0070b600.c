
/* WARNING: Removing unreachable block (ram,0x0070b65c) */
/* WARNING: Removing unreachable block (ram,0x0070b6a3) */
/* WARNING: Removing unreachable block (ram,0x0070b680) */
/* WARNING: Removing unreachable block (ram,0x0070b6aa) */

void FUN_0070b600(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined4 local_30;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008575d2;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  cVar1 = _Test_callable<>(param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (cVar1 == '\0') {
    Set(0);
  }
  else {
    allocator<>(&stack0x00000008);
    uVar2 = allocate(1);
    iVar3 = forward<>(0x14,uVar2);
    local_8 = 1;
    if (iVar3 == 0) {
      local_30 = 0;
    }
    else {
      puVar4 = &local_11;
      uVar2 = FUN_00417780(param_1,puVar4);
      local_30 = _Func_impl<>(uVar2,puVar4);
    }
    local_8 = 0xffffffff;
    Set(local_30);
  }
  ExceptionList = local_10;
  return;
}

