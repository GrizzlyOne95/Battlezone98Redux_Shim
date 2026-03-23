
int FUN_005d2a20(float param_1,float param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  FUN_00461fd0((param_1 - DAT_009182f8) * 0.1);
  uVar1 = FUN_0083f040();
  FUN_00461fd0((param_2 - DAT_009182fc) * 0.1,uVar1);
  uVar2 = FUN_0083f040();
  iVar3 = FUN_005d2970(uVar1,uVar2);
  *(float *)(iVar3 + 8) = param_1;
  *(float *)(iVar3 + 0xc) = param_2;
  return iVar3;
}

