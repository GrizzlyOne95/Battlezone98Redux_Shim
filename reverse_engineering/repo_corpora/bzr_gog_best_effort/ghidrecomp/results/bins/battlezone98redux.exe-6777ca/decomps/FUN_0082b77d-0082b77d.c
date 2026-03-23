
undefined2 * FUN_0082b77d(undefined4 param_1,int *param_2,size_t *param_3)

{
  undefined2 *puVar1;
  int iVar2;
  size_t sVar3;
  
  if (*param_2 == 0) {
    iVar2 = feof((FILE *)param_2[1]);
    if (iVar2 == 0) {
      sVar3 = fread(param_2 + 2,1,0x200,(FILE *)param_2[1]);
      *param_3 = sVar3;
      puVar1 = (undefined2 *)(-(uint)(sVar3 != 0) & (uint)(param_2 + 2));
    }
    else {
      puVar1 = (undefined2 *)0x0;
    }
  }
  else {
    *param_2 = 0;
    *param_3 = 1;
    puVar1 = &DAT_0087a44c;
  }
  return puVar1;
}

