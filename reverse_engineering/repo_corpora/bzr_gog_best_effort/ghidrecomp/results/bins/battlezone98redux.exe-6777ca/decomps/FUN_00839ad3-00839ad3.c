
void FUN_00839ad3(int param_1,int *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  bVar3 = false;
  iVar1 = *(int *)(param_1 + 0x30);
  iVar2 = *(int *)(iVar1 + 0x24);
  if (param_2 != (int *)0x0) {
    do {
      if (param_2[2] == 9) {
        if (param_2[4] == *(int *)(param_3 + 8)) {
          param_2[4] = iVar2;
          bVar3 = true;
        }
        if (param_2[5] == *(int *)(param_3 + 8)) {
          param_2[5] = iVar2;
          bVar3 = true;
        }
      }
      param_2 = (int *)*param_2;
    } while (param_2 != (int *)0x0);
    if (bVar3) {
      FUN_0083c5d2(iVar1,0,*(undefined4 *)(iVar1 + 0x24),*(undefined4 *)(param_3 + 8),0);
      FUN_0083cd31(iVar1,1);
    }
  }
  return;
}

