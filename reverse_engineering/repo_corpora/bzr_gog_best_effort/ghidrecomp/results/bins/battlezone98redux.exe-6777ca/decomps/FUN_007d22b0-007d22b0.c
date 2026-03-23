
void FUN_007d22b0(void)

{
  int iVar1;
  int *piVar2;
  int local_8;
  
  for (local_8 = 0; iVar1 = size(), local_8 < iVar1; local_8 = local_8 + 1) {
    piVar2 = (int *)FUN_004200d0(local_8);
    if ((undefined4 *)*piVar2 != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)*piVar2)(1);
    }
  }
  FUN_0041ff50();
  return;
}

