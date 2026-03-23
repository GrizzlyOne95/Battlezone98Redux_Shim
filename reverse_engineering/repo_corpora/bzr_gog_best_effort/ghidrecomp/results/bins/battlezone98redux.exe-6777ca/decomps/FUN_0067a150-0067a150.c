
int __thiscall FUN_0067a150(int *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (0x10000U - param_2 < (uint)param_1[0x75]) {
    (**(code **)(*param_1 + 0x48))();
    uVar1 = FUN_0041f870();
    FUN_007d6a70("%s: vertex buffer is full\n",uVar1);
    iVar2 = 0;
  }
  else {
    iVar2 = param_1[0x73];
    param_1[0x73] = param_2 * param_1[0x53] + param_1[0x73];
    param_1[0x75] = param_1[0x75] + param_2;
  }
  return iVar2;
}

