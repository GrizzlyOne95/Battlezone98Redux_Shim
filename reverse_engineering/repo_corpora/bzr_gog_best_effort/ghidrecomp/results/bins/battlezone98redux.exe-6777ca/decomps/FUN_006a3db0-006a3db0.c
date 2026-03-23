
void FUN_006a3db0(undefined4 param_1,undefined2 param_2)

{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_006a0810(param_1);
  if (cVar1 == '\0') {
    iVar2 = FUN_006a0a20(param_1);
    *(undefined2 *)(iVar2 + 0x66) = param_2;
  }
  else {
    iVar2 = FUN_006a12b0(param_1,0);
    *(undefined2 *)(iVar2 + 0x16) = param_2;
  }
  return;
}

