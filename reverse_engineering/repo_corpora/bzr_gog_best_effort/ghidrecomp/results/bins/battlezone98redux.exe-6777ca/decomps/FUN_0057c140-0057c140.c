
void FUN_0057c140(undefined4 param_1,undefined4 param_2,int *param_3)

{
  char cVar1;
  
  while( true ) {
    cVar1 = FUN_00420f10(&param_2);
    if (cVar1 == '\0') break;
    *param_3 = *param_3 + 1;
    FUN_00422190();
  }
  return;
}

