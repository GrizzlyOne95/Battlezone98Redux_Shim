
void FUN_0069cfa0(undefined4 param_1,undefined4 param_2,undefined4 *param_3,char *param_4)

{
  char cVar1;
  char *_Source;
  char *local_110;
  char local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  _Source = (char *)FUN_0069c4d0(param_1,param_2);
  if (_Source == (char *)0x0) {
    *param_3 = 0xffffffff;
    sprintf(local_108,"Config or AIP string parameter \'%s\' not found.",param_2);
    FUN_00699180(local_108,1);
  }
  else {
    local_110 = _Source;
    do {
      cVar1 = *local_110;
      local_110 = local_110 + 1;
    } while (cVar1 != '\0');
    strncpy(param_4,_Source,(size_t)(local_110 + (1 - (int)(_Source + 1))));
    *param_3 = 0;
  }
  FUN_0083e885();
  return;
}

