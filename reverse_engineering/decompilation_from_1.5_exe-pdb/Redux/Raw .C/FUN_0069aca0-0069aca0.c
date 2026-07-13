
void FUN_0069aca0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,char *param_5
                 )

{
  char cVar1;
  char *pcVar2;
  char *local_60;
  char local_59 [81];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_2 == 1) {
    local_60 = param_5;
    pcVar2 = param_5 + 1;
    do {
      cVar1 = *local_60;
      local_60 = local_60 + 1;
    } while (cVar1 != '\0');
    if ((*param_5 == '\"') && (param_5[(int)(local_60 + (-1 - (int)pcVar2))] == '\"')) {
      strncpy(local_59 + 1,param_5 + 1,(size_t)(local_60 + (-2 - (int)pcVar2)));
      if ((char *)0x4f < local_60 + (-2 - (int)pcVar2)) {
        ___report_rangecheckfailure();
      }
      local_59[(int)(local_60 + (-2 - (int)pcVar2) + 1)] = '\0';
      FUN_0069c830(local_59 + 1,param_1);
    }
  }
  FUN_0083e885();
  return;
}

