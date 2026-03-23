
void FUN_00839600(int param_1,undefined1 param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  piVar1 = *(int **)(param_1 + 0x3c);
  if ((uint)piVar1[2] < piVar1[1] + 1U) {
    if (0x7ffffffd < (uint)piVar1[2]) {
      FUN_00838ef5(param_1,"lexical element too long",0);
    }
    iVar2 = piVar1[2] * 2;
    if (iVar2 + 1U < 0xfffffffe) {
      iVar3 = FUN_00838869(*(undefined4 *)(param_1 + 0x34),*piVar1,piVar1[2],iVar2);
    }
    else {
      iVar3 = FUN_008388ab(*(undefined4 *)(param_1 + 0x34));
    }
    piVar1[2] = iVar2;
    *piVar1 = iVar3;
  }
  *(undefined1 *)(piVar1[1] + *piVar1) = param_2;
  piVar1[1] = piVar1[1] + 1;
  return;
}

