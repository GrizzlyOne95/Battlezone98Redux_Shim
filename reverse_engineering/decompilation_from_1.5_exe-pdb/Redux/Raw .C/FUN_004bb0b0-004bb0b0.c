
void __thiscall FUN_004bb0b0(_Container_base12 *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 local_6;
  undefined1 local_5;
  
  std::_Container_base12::_Orphan_all(param_1);
  if (((uint)(*(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10)) % 2 == 0) &&
     (*(uint *)(param_1 + 8) <= *(int *)(param_1 + 0x10) + 2U >> 1)) {
    FUN_004bb5a0(1);
  }
  *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 8) * 2 - 1U & *(uint *)(param_1 + 0xc);
  iVar3 = *(int *)(param_1 + 0xc);
  iVar1 = *(int *)(param_1 + 0x10);
  iVar2 = FUN_004bb930(iVar3 + iVar1);
  if (*(int *)(*(int *)(param_1 + 4) + iVar2 * 4) == 0) {
    uVar4 = 2;
    Getal(&local_5);
    uVar4 = allocate(uVar4);
    *(undefined4 *)(*(int *)(param_1 + 4) + iVar2 * 4) = uVar4;
  }
  uVar4 = FUN_00417780(param_2);
  iVar3 = ((uint)(iVar3 + iVar1) % 2) * 6 + *(int *)(*(int *)(param_1 + 4) + iVar2 * 4);
  Getal(&local_6);
  construct<>(iVar3,uVar4);
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  return;
}

