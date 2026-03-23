
void __thiscall
FUN_0081da30(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  uVar1 = get(param_1);
  uVar2 = FUN_00417780(param_5);
  uVar2 = FUN_00417780(param_4,uVar2);
  uVar2 = FUN_00417780(param_3,uVar2);
  puVar3 = (undefined4 *)FUN_004242e0(uVar1,uVar2);
  uVar2 = FUN_0081dc80(uVar1,*puVar3);
  FUN_0081db40(1);
  puVar3 = (undefined4 *)FUN_004242e0(uVar1);
  *puVar3 = uVar2;
  puVar3 = (undefined4 *)FUN_004242e0(uVar2);
  puVar3 = (undefined4 *)FUN_00417780(*puVar3);
  *puVar3 = uVar2;
  return;
}

