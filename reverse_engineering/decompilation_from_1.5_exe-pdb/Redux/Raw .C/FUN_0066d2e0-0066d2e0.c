
void __thiscall FUN_0066d2e0(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  char *pcVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  
  while( true ) {
    pcVar2 = (char *)FUN_004242d0(param_2,param_1);
    if (*pcVar2 != '\0') break;
    puVar3 = (undefined4 *)FUN_004242f0(param_2);
    FUN_0066d2e0(*puVar3);
    puVar3 = (undefined4 *)FUN_00417780(param_2);
    uVar1 = *puVar3;
    uVar4 = FUN_00424300(param_2);
    uVar4 = FUN_00417780(uVar4);
    FUN_004b4350(uVar4);
    FUN_0066f110(uVar4);
    uVar4 = 1;
    FUN_004b4350(param_2,1);
    FUN_004b3230(param_2,uVar4);
    param_2 = uVar1;
  }
  return;
}

