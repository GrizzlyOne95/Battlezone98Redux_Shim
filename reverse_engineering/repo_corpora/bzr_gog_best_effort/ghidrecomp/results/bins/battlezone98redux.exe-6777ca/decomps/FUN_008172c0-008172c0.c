
void __thiscall FUN_008172c0(allocator<char> *param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864d80;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_3 == 0) {
    FUN_00817468();
    return;
  }
  iVar1 = FUN_006e1d50();
  uVar2 = iVar1 - param_2 >> 5;
  if (uVar2 == 0) {
    uVar2 = param_3;
    uVar3 = std::allocator<char>::allocator<char>(param_1);
    FUN_00817480(uVar3,iVar1,uVar2);
    *(uint *)(param_1 + 4) = *(int *)(param_1 + 4) + param_3;
    FUN_00817468();
    return;
  }
  if (param_3 <= uVar2) {
    iVar4 = iVar1 + param_3 * -0x20;
    iVar5 = iVar1;
    iVar6 = iVar1;
    uVar3 = std::allocator<char>::allocator<char>(param_1);
    FUN_0070c4a0(uVar3,iVar4,iVar5,iVar6);
    *(uint *)(param_1 + 4) = *(int *)(param_1 + 4) + param_3;
    FUN_00817850(param_2,iVar1 + param_3 * -0x20,iVar1);
    uVar3 = std::allocator<char>::allocator<char>(param_1);
    FUN_008174b0(uVar3,param_2,param_3);
    FUN_00817468();
    return;
  }
  iVar4 = param_3 * 0x20 + param_2;
  iVar5 = param_2;
  iVar6 = iVar1;
  uVar3 = std::allocator<char>::allocator<char>(param_1);
  FUN_0070c4a0(uVar3,iVar5,iVar6,iVar4);
  local_8 = 0;
  uVar7 = uVar2;
  uVar3 = std::allocator<char>::allocator<char>(param_1);
  FUN_008174b0(uVar3,param_2,uVar7);
  iVar5 = param_3 - uVar2;
  uVar3 = std::allocator<char>::allocator<char>(param_1);
  FUN_00817480(uVar3,iVar1,iVar5);
  *(uint *)(param_1 + 4) = *(int *)(param_1 + 4) + param_3;
  FUN_00817458();
  return;
}

