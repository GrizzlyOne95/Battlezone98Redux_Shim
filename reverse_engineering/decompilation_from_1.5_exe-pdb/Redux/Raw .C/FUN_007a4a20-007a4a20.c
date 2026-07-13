
void __fastcall FUN_007a4a20(undefined4 param_1)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = FUN_007cb1a0(param_1);
  if (iVar3 != 0) {
    uVar4 = FUN_0056b910();
    FUN_006b6010(uVar4);
    cVar1 = FUN_0073ba10(uVar4);
    if (cVar1 != '\0') {
      uVar2 = FUN_0056f920("/kick");
      FUN_006247a0(uVar2);
    }
  }
  return;
}

