
void __thiscall FUN_00429da0(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  char *pcVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined1 local_6;
  undefined1 local_5;
  
  while( true ) {
    pcVar2 = (char *)FUN_004242d0(param_2,param_1);
    if (*pcVar2 != '\0') break;
    puVar3 = (undefined4 *)FUN_004242f0(param_2);
    FUN_00429da0(*puVar3);
    puVar3 = (undefined4 *)FUN_00417780(param_2);
    uVar1 = *puVar3;
    uVar4 = FUN_00424300(param_2);
    uVar4 = FUN_00417780(uVar4);
    Getal(&local_5);
    destroy<>(uVar4);
    uVar4 = 1;
    Getal(&local_6);
    deallocate(param_2,uVar4);
    param_2 = uVar1;
  }
  return;
}

