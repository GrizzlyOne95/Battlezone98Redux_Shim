
byte * FUN_006abe70(int *param_1,uint param_2)

{
  byte *pbVar1;
  byte local_10;
  
  if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
    pbVar1 = (byte *)*param_1;
    *param_1 = 0;
    if (param_2 <= *pbVar1) {
      pbVar1[param_2] = *pbVar1;
      return pbVar1;
    }
    operator_delete(pbVar1);
  }
  pbVar1 = operator_new(param_2 + 1);
  if (param_2 < 0x100) {
    local_10 = (byte)param_2;
  }
  else {
    local_10 = 0;
  }
  pbVar1[param_2] = local_10;
  return pbVar1;
}

