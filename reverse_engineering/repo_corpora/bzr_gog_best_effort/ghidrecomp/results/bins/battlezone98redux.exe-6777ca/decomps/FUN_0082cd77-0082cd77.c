
void FUN_0082cd77(int param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  
  if (param_2 == (char *)0x0) {
    *(undefined4 *)(*(int *)(param_1 + 8) + 8) = 0;
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
    return;
  }
  pcVar2 = param_2;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  FUN_0082cd08(param_1,param_2,(int)pcVar2 - (int)(param_2 + 1));
  return;
}

