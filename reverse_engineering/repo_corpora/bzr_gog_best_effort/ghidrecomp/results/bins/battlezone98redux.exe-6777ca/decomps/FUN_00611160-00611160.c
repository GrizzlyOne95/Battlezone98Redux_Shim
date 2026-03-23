
void FUN_00611160(void)

{
  char cVar1;
  int *piVar2;
  
  while (cVar1 = FUN_0042d8f0(), cVar1 == '\0') {
    piVar2 = (int *)FUN_0045e220();
    if ((undefined4 *)*piVar2 != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)*piVar2)(1);
    }
  }
  return;
}

