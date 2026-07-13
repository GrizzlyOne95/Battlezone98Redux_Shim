
void __thiscall
FUN_00432670(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5,
            int param_6)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if (param_1 != param_3) {
    FUN_00430530(param_6);
    *(int *)(param_3 + 4) = *(int *)(param_3 + 4) - param_6;
  }
  uVar1 = get();
  uVar2 = get();
  puVar3 = (undefined4 *)FUN_004242e0(uVar2);
  puVar3 = (undefined4 *)FUN_00417780(*puVar3);
  *puVar3 = uVar1;
  uVar1 = get();
  uVar2 = get();
  puVar3 = (undefined4 *)FUN_004242e0(uVar2);
  puVar3 = (undefined4 *)FUN_00417780(*puVar3);
  *puVar3 = uVar1;
  uVar1 = get();
  uVar2 = get();
  puVar3 = (undefined4 *)FUN_004242e0(uVar2);
  puVar3 = (undefined4 *)FUN_00417780(*puVar3);
  *puVar3 = uVar1;
  uVar1 = get();
  puVar3 = (undefined4 *)FUN_004242e0(uVar1);
  uVar1 = *puVar3;
  uVar2 = get();
  puVar3 = (undefined4 *)FUN_004242e0(uVar2);
  uVar2 = get();
  puVar4 = (undefined4 *)FUN_004242e0(uVar2);
  *puVar4 = *puVar3;
  uVar2 = get();
  puVar3 = (undefined4 *)FUN_004242e0(uVar2);
  uVar2 = get();
  puVar4 = (undefined4 *)FUN_004242e0(uVar2);
  *puVar4 = *puVar3;
  uVar2 = get();
  puVar3 = (undefined4 *)FUN_004242e0(uVar2);
  *puVar3 = uVar1;
  return;
}

