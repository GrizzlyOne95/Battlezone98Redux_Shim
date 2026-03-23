
int FUN_0082fba1(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar1 = param_2 * 4 + 0x14;
  iVar2 = FUN_00838869(param_1,0,0,iVar1);
  FUN_0083010b(param_1,iVar2,6);
  *(undefined1 *)(iVar2 + 6) = 0;
  *(undefined4 *)(iVar2 + 0xc) = param_3;
  *(char *)(iVar2 + 7) = (char)param_2;
  if (param_2 != 0) {
    puVar3 = (undefined4 *)(iVar1 + iVar2);
    do {
      puVar3 = puVar3 + -1;
      *puVar3 = 0;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return iVar2;
}

