
int __thiscall FUN_00605270(undefined4 param_1,undefined4 *param_2)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int local_c;
  
  iVar2 = FUN_00417ca0(param_1);
  if (iVar2 != 0) {
    for (local_c = 0; local_c < 5; local_c = local_c + 1) {
      piVar3 = (int *)FUN_00417f60(local_c);
      if ((piVar3 != (int *)0x0) &&
         ((*(int *)(piVar3[2] + 0xc) == 0x49524546 || (*(int *)(piVar3[2] + 0xc) == 0x52444d50)))) {
        if (0.0 < (float)*(int *)(piVar3[2] + 0x34)) {
          *param_2 = piVar3;
          return local_c;
        }
        cVar1 = (**(code **)(*piVar3 + 0x10))();
        if (cVar1 == '\0') {
          (**(code **)(*piVar3 + 8))();
        }
      }
    }
  }
  *param_2 = 0;
  return -1;
}

