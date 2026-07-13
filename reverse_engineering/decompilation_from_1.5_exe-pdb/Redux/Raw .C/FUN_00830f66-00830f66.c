
int FUN_00830f66(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_00838869(param_1,0,0,0x20);
  FUN_0083010b(param_1,iVar1,5);
  *(undefined4 *)(iVar1 + 8) = 0;
  *(undefined2 *)(iVar1 + 6) = 0xff;
  *(undefined4 *)(iVar1 + 0xc) = 0;
  *(undefined4 *)(iVar1 + 0x1c) = 0;
  *(undefined **)(iVar1 + 0x10) = &DAT_0086eef0;
  FUN_008315d2(param_1,iVar1,param_2);
  FUN_00831635(param_1,iVar1,param_3);
  return iVar1;
}

