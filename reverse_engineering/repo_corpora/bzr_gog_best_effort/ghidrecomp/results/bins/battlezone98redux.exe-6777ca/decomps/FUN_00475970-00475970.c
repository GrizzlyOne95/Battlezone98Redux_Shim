
void __fastcall FUN_00475970(int param_1)

{
  int iVar1;
  char cVar2;
  float10 fVar3;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x34) + 0x230);
  cVar2 = (**(code **)(**(int **)(param_1 + 0x34) + 0x6c))();
  if ((cVar2 == '\0') || (*(int *)(iVar1 + 0xe0) != 0)) {
    FUN_005fb450();
  }
  else {
    fVar3 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0x54) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x54)) {
      (**(code **)(**(int **)(param_1 + 0x34) + 0x60))();
    }
    *(undefined4 *)(iVar1 + 0xd0) = 0;
    *(undefined4 *)(iVar1 + 0xc4) = 0;
    *(undefined4 *)(iVar1 + 0xcc) = 0;
    *(undefined4 *)(iVar1 + 0xd4) = 0;
    *(undefined4 *)(iVar1 + 0xd8) = 0;
  }
  return;
}

