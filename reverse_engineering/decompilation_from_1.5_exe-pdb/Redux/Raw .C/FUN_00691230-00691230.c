
undefined4 FUN_00691230(undefined2 param_1,undefined1 param_2)

{
  char cVar1;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  
  cVar1 = FUN_006a05c0(param_1);
  if (cVar1 != '\0') {
    puVar2 = (undefined2 *)FUN_006a0670(param_1);
    if (*(undefined2 **)(puVar2 + 2) != (undefined2 *)0x0) {
      iVar3 = FUN_006a0210(**(undefined2 **)(puVar2 + 2),param_2);
      iVar4 = FUN_006a0210(*puVar2,param_2);
      if (iVar4 < iVar3) {
        return 1;
      }
    }
  }
  return 0;
}

