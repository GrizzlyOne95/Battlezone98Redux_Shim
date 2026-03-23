
void __thiscall FUN_00726500(_Container_base12 *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 local_6;
  undefined1 local_5;
  
  std::_Container_base12::_Orphan_all(param_1);
  if (((uint)(*(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10)) % 0x10 == 0) &&
     (*(uint *)(param_1 + 8) <= *(int *)(param_1 + 0x10) + 0x10U >> 4)) {
    FUN_00726ea0(1);
  }
  *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 8) * 0x10 - 1U & *(uint *)(param_1 + 0xc);
  iVar3 = *(int *)(param_1 + 0xc);
  iVar1 = *(int *)(param_1 + 0x10);
  iVar2 = FUN_00713d00(iVar3 + iVar1);
  if (*(int *)(*(int *)(param_1 + 4) + iVar2 * 4) == 0) {
    uVar4 = 0x10;
    Getal(&local_5);
    uVar4 = allocate(uVar4);
    *(undefined4 *)(*(int *)(param_1 + 4) + iVar2 * 4) = uVar4;
  }
  iVar3 = (uint)(iVar3 + iVar1) % 0x10 + *(int *)(*(int *)(param_1 + 4) + iVar2 * 4);
  Getal(&local_6);
  construct<>(iVar3,param_2);
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  return;
}

