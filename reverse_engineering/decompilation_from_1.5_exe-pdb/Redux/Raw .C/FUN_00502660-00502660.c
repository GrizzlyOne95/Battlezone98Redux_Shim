
undefined4 FUN_00502660(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int local_8;
  
  local_8 = FUN_0082d338(param_1,0xffffd8ed);
  iVar2 = FUN_004ff240();
  do {
    iVar3 = FUN_004ff220();
    if (iVar3 <= local_8) {
      return 0;
    }
    uVar1 = *(undefined4 *)(iVar2 + local_8 * 4);
    local_8 = local_8 + 1;
    iVar3 = FUN_00462630(uVar1);
  } while ((iVar3 == 0) ||
          (iVar3 = (**(code **)(*(int *)(iVar3 + 0x18) + 0x30))(),
          (*(uint *)(iVar3 + 0x14) & 0x200) != 0));
  FUN_0082ccca(param_1,local_8);
  FUN_0082cfd8(param_1,0xffffd8ed);
  FUN_004ff770(param_1,uVar1);
  return 1;
}

