
void FUN_00589df0(undefined4 param_1,undefined4 param_2,float *param_3,float param_4,float param_5,
                 float param_6,float param_7)

{
  char cVar1;
  char *_Src;
  char *pcVar2;
  char *local_114;
  char *local_110;
  char local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  _Src = (char *)FUN_00589620(param_1,param_2);
  if (_Src == (char *)0x0) {
    if (param_3 != (float *)0x0) {
      *param_3 = param_4;
      param_3[1] = param_5;
      param_3[2] = param_6;
      param_3[3] = param_7;
    }
  }
  else if (param_3 != (float *)0x0) {
    local_114 = setlocale(4,(char *)0x0);
    pcVar2 = local_108;
    local_110 = pcVar2;
    do {
      cVar1 = *local_114;
      *local_110 = cVar1;
      local_114 = local_114 + 1;
      local_110 = local_110 + 1;
    } while (cVar1 != '\0');
    setlocale(4,"C");
    *param_3 = param_4 * 255.0;
    param_3[1] = param_5 * 255.0;
    param_3[2] = param_6 * 255.0;
    param_3[3] = param_7 * 255.0;
    sscanf(_Src,"%f %f %f %f",param_3,param_3 + 1,param_3 + 2,param_3 + 3,pcVar2);
    *param_3 = *param_3 / 255.0;
    param_3[1] = param_3[1] / 255.0;
    param_3[2] = param_3[2] / 255.0;
    param_3[3] = param_3[3] / 255.0;
    setlocale(4,local_108);
  }
  FUN_0083e885();
  return;
}

