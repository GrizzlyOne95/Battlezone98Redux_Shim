
void __fastcall FUN_007633a0(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  uVar1 = get();
  puVar2 = (undefined4 *)FUN_00417780(uVar1);
  puVar3 = (undefined4 *)FUN_004242e0(uVar1);
  puVar3 = (undefined4 *)FUN_00417780(*puVar3);
  *puVar3 = *puVar2;
  puVar2 = (undefined4 *)FUN_004242e0(uVar1);
  puVar3 = (undefined4 *)FUN_00417780(uVar1);
  puVar3 = (undefined4 *)FUN_004242e0(*puVar3);
  *puVar3 = *puVar2;
  FUN_0075ffe0(uVar1);
  *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -1;
  return;
}

