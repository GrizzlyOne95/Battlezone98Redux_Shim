
void FUN_0055e1e0(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  float10 fVar3;
  int extraout_var;
  int in_stack_fffffff0;
  float fVar4;
  float fVar5;
  
  iVar2 = FUN_005c8800(param_1);
  if (iVar2 == 2) {
    iVar2 = extraout_var;
    cVar1 = FUN_005c8410(param_1,"avmine");
    if (cVar1 != '\0') {
      fVar4 = 99999.0;
      fVar3 = (float10)FUN_005c9800(param_1,&DAT_00882c00,1);
      fVar5 = (float)fVar3;
      if (fVar5 < fVar4) {
        in_stack_fffffff0 = 0;
        FUN_005cb960(param_1,&DAT_00882bfc,1);
        fVar4 = fVar5;
      }
      fVar3 = (float10)FUN_005c9800(param_1,&DAT_00882c08,1);
      fVar5 = (float)fVar3;
      if (fVar5 < fVar4) {
        in_stack_fffffff0 = 1;
        FUN_005cb960(param_1,&DAT_00882c04,1);
        fVar4 = fVar5;
      }
      fVar3 = (float10)FUN_005c9800(param_1,&DAT_00882c10,1);
      if ((float)fVar3 < fVar4) {
        in_stack_fffffff0 = 2;
        FUN_005cb960(param_1,&DAT_00882c0c,1,iVar2,2,(float)fVar3);
      }
      *(undefined4 *)(iVar2 + 0xa8 + in_stack_fffffff0 * 4) = param_1;
      *(int *)(iVar2 + 0xc4) = in_stack_fffffff0;
    }
  }
  return;
}

