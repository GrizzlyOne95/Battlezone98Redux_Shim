
void FUN_00787b60(char *param_1,char *param_2,undefined4 param_3,char *param_4)

{
  int iVar1;
  undefined4 local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = param_3;
  if (((*param_4 != '\0') && (*param_1 != '\0')) && (*param_2 != '\0')) {
    iVar1 = FUN_00787370(param_4);
    if (iVar1 != 0) {
      iVar1 = FUN_00787660(param_1,param_2,local_18,0x10);
      if (-1 < iVar1) {
        sscanf(local_18,"%f",&local_1c);
      }
    }
  }
  FUN_0083e885();
  return;
}

