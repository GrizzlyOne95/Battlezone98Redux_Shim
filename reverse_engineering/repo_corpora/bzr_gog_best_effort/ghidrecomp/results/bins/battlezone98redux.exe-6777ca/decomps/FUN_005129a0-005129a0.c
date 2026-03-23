
undefined4 __fastcall FUN_005129a0(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  float10 extraout_ST0;
  
  if (*(int *)(*(int *)(param_1 + 0x40) + 0x10) == 3) {
    uVar2 = 0;
  }
  else {
    iVar3 = *(int *)(*(int *)(param_1 + 0x40) + 4) + -1;
    puVar1 = *(undefined4 **)(*(int *)(param_1 + 0x40) + 8);
    fVar4 = (float10)FUN_00512960(*puVar1,puVar1[1],puVar1[iVar3 * 2],puVar1[iVar3 * 2 + 1]);
    FUN_00461110();
    if ((float)extraout_ST0 <= (float)fVar4 * 2.0) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

