
void FUN_0082c7d3(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  
  piVar4 = (int *)FUN_0082c4a6(param_1,param_2);
  iVar1 = piVar4[2];
  if ((iVar1 == 6) || (iVar1 == 7)) {
    puVar2 = *(undefined4 **)(param_1 + 8);
    uVar3 = *(undefined4 *)(*piVar4 + 0xc);
    puVar2[2] = 5;
    *puVar2 = uVar3;
  }
  else if (iVar1 == 8) {
    iVar1 = *piVar4;
    puVar2 = *(undefined4 **)(param_1 + 8);
    *puVar2 = *(undefined4 *)(iVar1 + 0x48);
    puVar2[1] = *(undefined4 *)(iVar1 + 0x4c);
    puVar2[2] = *(undefined4 *)(iVar1 + 0x50);
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 8) + 8) = 0;
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  return;
}

