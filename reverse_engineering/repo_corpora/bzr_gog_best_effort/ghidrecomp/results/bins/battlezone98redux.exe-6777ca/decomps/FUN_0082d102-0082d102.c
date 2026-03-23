
void FUN_0082d102(int param_1,undefined4 param_2,char *param_3)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  undefined4 local_14 [2];
  undefined4 local_c;
  
  uVar2 = FUN_0082c4a6(param_1,param_2);
  pcVar3 = param_3;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  local_14[0] = FUN_008309f4(param_1,param_3,(int)pcVar3 - (int)(param_3 + 1));
  local_c = 4;
  FUN_0083321b(param_1,uVar2,local_14,*(int *)(param_1 + 8) + -0x10);
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0x10;
  return;
}

