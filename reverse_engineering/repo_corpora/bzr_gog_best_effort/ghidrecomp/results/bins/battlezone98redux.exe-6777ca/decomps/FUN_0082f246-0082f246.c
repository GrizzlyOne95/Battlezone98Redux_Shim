
int FUN_0082f246(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if ((*(byte *)(param_1 + 0x38) & 2) != 0) {
    param_2 = (undefined4 *)FUN_0082ee9e(param_1,param_2);
  }
  iVar2 = *(int *)(param_1 + 0x14);
  *(undefined4 **)(param_1 + 0x14) = (undefined4 *)(iVar2 + -0x18);
  iVar1 = *(int *)(iVar2 + 0x10);
  puVar3 = *(undefined4 **)(iVar2 + 4);
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(iVar2 + -0x18);
  *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(iVar2 + -0xc);
  iVar2 = iVar1;
  for (; (iVar2 != 0 && (param_2 < *(undefined4 **)(param_1 + 8))); param_2 = param_2 + 4) {
    *puVar3 = *param_2;
    puVar3[1] = param_2[1];
    puVar3[2] = param_2[2];
    iVar2 = iVar2 + -1;
    puVar3 = puVar3 + 4;
  }
  for (; 0 < iVar2; iVar2 = iVar2 + -1) {
    puVar3[2] = 0;
    puVar3 = puVar3 + 4;
  }
  *(undefined4 **)(param_1 + 8) = puVar3;
  return iVar1 + 1;
}

