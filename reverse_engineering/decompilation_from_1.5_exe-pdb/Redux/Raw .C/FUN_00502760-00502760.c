
undefined4 FUN_00502760(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0082d338(param_1,0xffffd8ed);
  do {
    if (DAT_00917af8 <= iVar1) {
      return 0;
    }
  } while ((*(int *)(&DAT_00917a78 + iVar1 * 4) == 0) ||
          (iVar2 = (**(code **)(*(int *)(*(int *)(&DAT_00917a78 + iVar1 * 4) + 0x18) + 0x30))(),
          (*(uint *)(iVar2 + 0x14) & 0x200) != 0));
  FUN_0082ccca(param_1,iVar1);
  FUN_0082cfd8(param_1,0xffffd8ed);
  uVar3 = FUN_00462380();
  FUN_004ff770(param_1,uVar3);
  return 1;
}

