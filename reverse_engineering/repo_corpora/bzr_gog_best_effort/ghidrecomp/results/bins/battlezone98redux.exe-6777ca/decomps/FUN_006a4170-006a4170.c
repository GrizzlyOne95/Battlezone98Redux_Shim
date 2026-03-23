
void FUN_006a4170(void)

{
  int *piVar1;
  undefined4 uVar2;
  int local_8;
  
  for (local_8 = 0; local_8 < DAT_009310c4; local_8 = local_8 + 1) {
    uVar2 = DAT_02c00ec0;
    FUN_004200d0(local_8);
    piVar1 = (int *)FUN_004200d0(uVar2);
    if (*piVar1 != 0) {
      if ((undefined4 *)*piVar1 != (undefined4 *)0x0) {
        (*(code *)**(undefined4 **)*piVar1)(1);
      }
      *piVar1 = 0;
    }
  }
  DAT_009310c4 = 0;
  if (DAT_0093101c != 0) {
    operator_delete__((void *)DAT_0093101c);
    DAT_0093101c = 0;
  }
  return;
}

