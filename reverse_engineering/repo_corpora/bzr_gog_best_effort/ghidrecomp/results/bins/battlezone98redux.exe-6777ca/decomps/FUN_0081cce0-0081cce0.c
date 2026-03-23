
undefined4 FUN_0081cce0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = FUN_0081c600(param_1,param_2);
  puVar2 = (undefined4 *)FUN_0044eb20(local_10,&local_c);
  local_8 = *puVar2;
  uVar3 = FUN_0044eaa0(local_14);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 != '\0') {
    iVar4 = FUN_0081dee0();
    iVar4 = iVar4 + -1;
    FUN_004305e0(iVar4);
    FUN_006cf480(iVar4);
    param_2 = FUN_0041f870();
  }
  return param_2;
}

