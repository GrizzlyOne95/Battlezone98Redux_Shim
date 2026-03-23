
void FUN_00822830(void)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  int local_8;
  
  for (local_8 = 0; local_8 < 0x100; local_8 = local_8 + 1) {
    fVar1 = (float10)FUN_004a7890();
    fVar2 = (float10)FUN_004a7890();
    fVar3 = (float10)FUN_004a7890();
    fVar4 = (float10)FUN_004a7890();
    fVar5 = (float10)FUN_004a7890();
    *(float *)(&DAT_02cc3ba0 + local_8 * 4) =
         ((float)fVar1 + (float)fVar2 + (float)fVar3 + (float)fVar4 + (float)fVar5) * 0.2;
  }
  return;
}

