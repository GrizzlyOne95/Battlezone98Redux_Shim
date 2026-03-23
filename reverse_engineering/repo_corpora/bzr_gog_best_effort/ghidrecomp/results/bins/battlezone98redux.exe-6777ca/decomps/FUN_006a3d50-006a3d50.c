
undefined2 FUN_006a3d50(undefined4 param_1)

{
  undefined2 uVar1;
  char cVar2;
  undefined2 *puVar3;
  int iVar4;
  
  cVar2 = FUN_006a0810(param_1);
  if (cVar2 == '\0') {
    iVar4 = FUN_006a0a20(param_1);
    uVar1 = *(undefined2 *)(iVar4 + 0x5a);
  }
  else {
    puVar3 = (undefined2 *)FUN_006a12b0(param_1,0);
    uVar1 = *puVar3;
  }
  return uVar1;
}

