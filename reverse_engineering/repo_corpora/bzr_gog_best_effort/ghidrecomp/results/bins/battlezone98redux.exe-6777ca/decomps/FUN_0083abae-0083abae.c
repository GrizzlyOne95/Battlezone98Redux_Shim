
void FUN_0083abae(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined2 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x30);
  if (200 < (int)(*(byte *)(iVar1 + 0x32) + 1 + param_3)) {
    FUN_0083a089(iVar1,200,"local variables");
  }
  uVar2 = FUN_0083b012(param_1,param_2);
  *(undefined2 *)(iVar1 + 0xac + ((uint)*(byte *)(iVar1 + 0x32) + param_3) * 2) = uVar2;
  return;
}

