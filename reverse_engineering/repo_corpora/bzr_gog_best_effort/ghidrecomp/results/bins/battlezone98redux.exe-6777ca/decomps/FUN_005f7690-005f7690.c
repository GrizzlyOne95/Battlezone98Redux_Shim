
void __fastcall FUN_005f7690(int param_1)

{
  int iVar1;
  char cVar2;
  float10 fVar3;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x34) + 0x230);
  cVar2 = (**(code **)(**(int **)(param_1 + 0x34) + 0x6c))();
  if ((cVar2 != '\0') && (*(int *)(iVar1 + 0xe0) == 0)) {
    fVar3 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0x84) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x84)) {
      (**(code **)(**(int **)(param_1 + 0x34) + 0x60))();
    }
  }
  FUN_005fb450();
  return;
}

