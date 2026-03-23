
void FUN_0069a090(int *param_1,int *param_2,char param_3)

{
  void *pvVar1;
  
  if ((param_3 != ' ') || ((*param_2 != 0 && (*(char *)(*param_1 + -1 + *param_2) != ' ')))) {
    *(char *)(*param_1 + *param_2) = param_3;
    *param_2 = *param_2 + 1;
    pvVar1 = realloc((void *)*param_1,*param_2 + 1);
    *param_1 = (int)pvVar1;
    if (*param_1 == 0) {
      FUN_00699180("YUCK. Bad. Puke.",1);
    }
  }
  return;
}

