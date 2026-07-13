
void FUN_006905d0(int param_1,uint param_2)

{
  char cVar1;
  
  *(int *)(*(int *)(&DAT_00930fc0 + param_1 * 4) + param_2 * 4) =
       *(int *)(*(int *)(&DAT_00930fc0 + param_1 * 4) + param_2 * 4) + -1;
  cVar1 = FUN_006a05c0(param_2 & 0xffff);
  if (cVar1 != '\0') {
    *(int *)(&DAT_02bfdfb0 + param_1 * 4) = *(int *)(&DAT_02bfdfb0 + param_1 * 4) + -1;
  }
  return;
}

