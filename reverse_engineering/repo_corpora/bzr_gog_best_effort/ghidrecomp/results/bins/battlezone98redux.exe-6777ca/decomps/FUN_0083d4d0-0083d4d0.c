
int * __fastcall FUN_0083d4d0(int param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  void *pvVar4;
  int *piVar5;
  uint local_8;
  
  if (*(int *)(param_1 + 0x3c) == 0) {
    FUN_0083d5d0(*(undefined4 *)(param_1 + 0x2c),*(undefined4 *)(param_1 + 0x28),
                 *(undefined4 *)(param_1 + 0x30));
  }
  piVar1 = (int *)(param_1 + 0x44);
  if (*(int *)(param_1 + 0x44) == 0) {
    piVar5 = (int *)(param_1 + 0x10);
    DAT_00914cc0 = 1;
    if (0xf < *(uint *)(param_1 + 0x24)) {
      piVar5 = (int *)*piVar5;
    }
    FUN_00844220("%s(%d): Memory pool \"%s\" is full; raise count to at least %d\n",
                 "RedMemoryPool.cpp",0xe0,piVar5,*(int *)(param_1 + 0x2c) + *(int *)(param_1 + 0x30)
                );
    iVar3 = *(int *)(param_1 + 0x30);
    pvVar4 = _aligned_malloc(*(int *)(param_1 + 0x28) * iVar3,0x10);
    *piVar1 = (int)pvVar4;
    if (pvVar4 == (void *)0x0) {
      return (int *)0x0;
    }
    *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + iVar3;
    local_8 = 0;
    if (iVar3 != 1) {
      do {
        uVar2 = local_8 + 1;
        *(uint *)(*(int *)(param_1 + 0x28) * local_8 + *piVar1) =
             uVar2 * *(int *)(param_1 + 0x28) + *piVar1;
        local_8 = uVar2;
      } while (uVar2 < *(int *)(param_1 + 0x30) - 1U);
    }
    *(undefined4 *)((*(int *)(param_1 + 0x30) + -1) * *(int *)(param_1 + 0x28) + *piVar1) = 0;
    if (*(int *)(param_1 + 0x3c) == 0) {
      *(int *)(param_1 + 0x3c) = *piVar1;
    }
    else {
      FUN_0083d830(piVar1);
    }
  }
  piVar5 = (int *)*piVar1;
  iVar3 = *piVar5;
  *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 1;
  *piVar1 = iVar3;
  if (*(uint *)(param_1 + 0x38) < *(uint *)(param_1 + 0x34)) {
    *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x34);
  }
  return piVar5;
}

