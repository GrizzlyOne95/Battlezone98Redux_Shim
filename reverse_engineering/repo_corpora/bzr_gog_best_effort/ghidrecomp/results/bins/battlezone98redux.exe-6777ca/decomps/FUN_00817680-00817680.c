
void __thiscall
FUN_00817680(allocator<char> *param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  iVar7 = param_2;
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855ca0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_18 = param_2;
  uVar3 = param_3;
  uVar2 = std::allocator<char>::allocator<char>(param_1);
  FUN_004324a0(param_2,uVar2,uVar3);
  local_8 = 0;
  uVar2 = 0;
  uVar3 = std::allocator<char>::allocator<char>(param_1);
  FUN_004324a0(param_2,uVar3,uVar2);
  local_8 = CONCAT31(local_8._1_3_,1);
  iVar4 = FUN_006d0da0(uVar1);
  if (iVar4 != 0) {
    uVar3 = FUN_006d0da0(param_4,iVar7);
    uVar2 = std::allocator<char>::allocator<char>(param_1);
    local_18 = FUN_0070c4a0(uVar2,uVar3);
    FUN_00703da0(local_18 - iVar7 >> 5);
  }
  iVar7 = local_18;
  iVar5 = param_5;
  uVar3 = std::allocator<char>::allocator<char>(param_1);
  FUN_00817480(uVar3,iVar7,iVar5);
  iVar7 = param_5 * 0x20 + local_18;
  FUN_00703da0(iVar7 - local_18 >> 5);
  local_18 = iVar7;
  if (iVar4 != 0) {
    iVar5 = *(int *)(param_1 + 4) * 0x20 + iVar4;
    uVar3 = param_4;
    uVar2 = std::allocator<char>::allocator<char>(param_1);
    local_18 = FUN_0070c4a0(uVar2,uVar3,iVar5,iVar7);
    uVar3 = FUN_006d0d10(iVar4,*(undefined4 *)(param_1 + 4));
    FUN_006dcea0(uVar3);
    puVar6 = (undefined4 *)FUN_004b4350();
    uVar3 = *puVar6;
    puVar6 = (undefined4 *)std::allocator<char>::allocator<char>(param_1);
    uVar2 = *puVar6;
    std::allocator<char>::allocator<char>(param_1);
    FUN_00417180(uVar2,uVar3);
  }
  FUN_00700920(&param_2);
  *(int *)(param_1 + 4) = local_18 - param_2 >> 5;
  FUN_00700940(&param_3);
  FUN_00703d50();
  FUN_00703d50();
  local_8 = local_8 & 0xffffff00;
  FUN_00703dc0();
  local_8 = 0xffffffff;
  FUN_00703d70();
  ExceptionList = local_10;
  return;
}

