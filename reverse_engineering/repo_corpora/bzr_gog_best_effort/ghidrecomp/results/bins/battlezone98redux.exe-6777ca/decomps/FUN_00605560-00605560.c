
void __fastcall FUN_00605560(int param_1)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  
  if (*(int *)(param_1 + 0xb8) != 0) {
    if (*(float *)(param_1 + 0x98) <= 3.0 && *(float *)(param_1 + 0x98) != 3.0) {
      (**(code **)(**(int **)(param_1 + 0xb8) + 0xc))();
    }
    else {
      bVar1 = false;
      iVar3 = *(int *)(*(int *)(*(int *)(param_1 + 0xb8) + 8) + 0xc);
      if (iVar3 == 0x49524546) {
        fVar4 = (float10)FUN_00822d80();
        fVar5 = (float10)FUN_0046d040();
        if ((float)fVar4 - (float)fVar5 < 10.0) {
          fVar4 = (float10)FUN_00497890();
          fVar5 = (float10)FUN_0046d040();
          if ((float)fVar4 == (float)fVar5) {
            bVar1 = true;
          }
          else if ((*(int *)(*(int *)(param_1 + 0x10) + 0x98) != 0) &&
                  ((*(int *)(*(int *)(*(int *)(param_1 + 0x10) + 0x98) + 0xc) == 0x494d474d ||
                   (*(int *)(*(int *)(*(int *)(param_1 + 0x10) + 0x98) + 0xc) == 0x54484d4d)))) {
            bVar1 = true;
          }
        }
      }
      else if (iVar3 == 0x52444d50) {
        if ((*(int *)(param_1 + 0x7c) == 0) ||
           (iVar3 = (*(code *)**(undefined4 **)(*(int *)(param_1 + 0x7c) + 0x18))(),
           *(int *)(iVar3 + 0x14) != 0x544f5250)) {
          fVar4 = (float10)FUN_00822d80();
          fVar5 = (float10)FUN_0046d040();
          if ((float)fVar4 - (float)fVar5 < 10.0) {
            fVar4 = (float10)FUN_00497890();
            fVar5 = (float10)FUN_0046d040();
            if ((float)fVar4 == (float)fVar5) {
              bVar1 = true;
            }
          }
        }
        else {
          bVar1 = true;
        }
      }
      if ((bVar1) && (cVar2 = (**(code **)(**(int **)(param_1 + 0xb8) + 0x10))(), cVar2 == '\0')) {
        (**(code **)(**(int **)(param_1 + 0xb8) + 8))();
      }
    }
  }
  return;
}

