
/* WARNING: Restarted to delay deadcode elimination for space: stack */

int __thiscall FUN_00736d50(allocator<char> *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085a4f0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_00710240(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  uVar2 = std::allocator<char>::allocator<char>(param_1);
  FUN_00416430(iVar1,uVar2);
  local_8 = 0;
  uVar2 = FUN_00417780(param_2);
  uVar2 = FUN_00417780(iVar1 + 0x10,uVar2);
  uVar3 = std::allocator<char>::allocator<char>(param_1);
  FUN_00737a40(uVar3,uVar2);
  FUN_00703d50();
  uVar2 = FUN_00417780(iVar1);
  iVar4 = forward<>(0xc,uVar2,0);
  local_8._0_1_ = 1;
  if (iVar4 != 0) {
    FUN_00710210();
  }
  local_8 = 0xffffffff;
  FUN_00711860();
  ExceptionList = local_10;
  return iVar1;
}

