
undefined4 FUN_0083c9bd(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = param_1;
  uVar1 = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x20) = 0xffffffff;
  param_1 = FUN_0083c5ff(param_1,0x16,0,0x1fffe);
  FUN_0083c626(iVar2,&param_1,uVar1);
  return param_1;
}

