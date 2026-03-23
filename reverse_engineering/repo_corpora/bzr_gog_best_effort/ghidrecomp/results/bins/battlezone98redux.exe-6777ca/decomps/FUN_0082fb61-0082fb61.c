
int FUN_0082fb61(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_00838869(param_1,0,0,param_2 * 0x10 + 0x18);
  FUN_0083010b(param_1,iVar1,6);
  *(char *)(iVar1 + 7) = (char)param_2;
  *(undefined1 *)(iVar1 + 6) = 1;
  *(undefined4 *)(iVar1 + 0xc) = param_3;
  return iVar1;
}

