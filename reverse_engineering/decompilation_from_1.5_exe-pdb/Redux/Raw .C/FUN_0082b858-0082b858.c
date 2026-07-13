
void FUN_0082b858(undefined4 param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = param_2;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  FUN_0082b81b(param_1,param_2,(int)pcVar2 - (int)(param_2 + 1));
  return;
}

