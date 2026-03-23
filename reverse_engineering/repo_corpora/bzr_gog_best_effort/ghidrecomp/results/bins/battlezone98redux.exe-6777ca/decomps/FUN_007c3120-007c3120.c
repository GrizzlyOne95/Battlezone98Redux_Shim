
char * __thiscall FUN_007c3120(char *param_1,char *param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x40) = param_3;
  strncpy(param_1,param_2,0x40);
  return param_1;
}

