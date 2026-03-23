
void __thiscall FUN_0076f0f0(_Container_base12 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_18;
  undefined1 local_6;
  undefined1 local_5;
  
  std::_Container_base12::_Orphan_all(param_1);
  if (*(uint *)(param_1 + 8) <= *(int *)(param_1 + 0x10) + 1U) {
    FUN_00752f70(1);
  }
  *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 8) - 1U & *(uint *)(param_1 + 0xc);
  if (*(int *)(param_1 + 0xc) == 0) {
    local_18 = *(int *)(param_1 + 8);
  }
  else {
    local_18 = *(int *)(param_1 + 0xc);
  }
  iVar1 = FUN_007485a0(local_18 + -1);
  if (*(int *)(*(int *)(param_1 + 4) + iVar1 * 4) == 0) {
    uVar2 = 1;
    Getal(&local_5);
    uVar2 = allocate(uVar2);
    *(undefined4 *)(*(int *)(param_1 + 4) + iVar1 * 4) = uVar2;
  }
  uVar2 = *(undefined4 *)(*(int *)(param_1 + 4) + iVar1 * 4);
  Getal(&local_6);
  construct<>(uVar2,param_2);
  *(int *)(param_1 + 0xc) = local_18 + -1;
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  return;
}

