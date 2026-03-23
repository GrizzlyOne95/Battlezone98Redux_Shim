
char FUN_007f5140(undefined4 param_1,double param_2,int param_3,int param_4)

{
  char cVar1;
  double _X;
  double local_1c;
  double local_14;
  char local_5;
  
  cVar1 = FUN_007f4fd0(param_2);
  if (cVar1 == '\0') {
    _X = param_2;
    __libm_sse2_log10();
    local_1c = floor(_X);
  }
  else {
    local_1c = 0.0;
  }
  local_5 = '\x01';
  while (local_14 = local_1c + 1.0, local_5 != '\0') {
    if ((double)param_3 + (double)(&DAT_008a2fd0)[-(param_3 >> 0x1f)] <= local_14) break;
    local_5 = FUN_007f5d60(param_1,0x30);
    local_1c = local_14;
  }
  if ((param_4 != 0) && (local_5 != '\0')) {
    local_5 = FUN_007f5ce0(param_1,param_2);
  }
  return local_5;
}

