
void __thiscall FUN_00726350(_Container_base12 *param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int local_18;
  undefined1 local_6;
  undefined1 local_5;
  
  std::_Container_base12::_Orphan_all(param_1);
  if ((*(uint *)(param_1 + 0xc) % 0x10 == 0) &&
     (*(uint *)(param_1 + 8) <= *(int *)(param_1 + 0x10) + 0x10U >> 4)) {
    FUN_00726ea0(1);
  }
  *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 8) * 0x10 - 1U & *(uint *)(param_1 + 0xc);
  if (*(int *)(param_1 + 0xc) == 0) {
    local_18 = *(int *)(param_1 + 8) << 4;
  }
  else {
    local_18 = *(int *)(param_1 + 0xc);
  }
  uVar1 = local_18 - 1;
  iVar2 = FUN_00713d00(uVar1);
  if (*(int *)(*(int *)(param_1 + 4) + iVar2 * 4) == 0) {
    uVar3 = 0x10;
    Getal(&local_5);
    uVar3 = allocate(uVar3);
    *(undefined4 *)(*(int *)(param_1 + 4) + iVar2 * 4) = uVar3;
  }
  iVar2 = uVar1 % 0x10 + *(int *)(*(int *)(param_1 + 4) + iVar2 * 4);
  Getal(&local_6);
  construct<>(iVar2,param_2);
  *(uint *)(param_1 + 0xc) = uVar1;
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  return;
}

