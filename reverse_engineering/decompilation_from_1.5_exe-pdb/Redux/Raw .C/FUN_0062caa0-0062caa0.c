
void FUN_0062caa0(undefined8 *param_1,int *param_2)

{
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined8 local_14;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_c = param_2[5];
  if (*param_2 == 0) {
    local_14 = FUN_0045c460(param_2[2],param_2[3],param_2[4]);
  }
  else {
    FUN_00820180(&local_20,param_2 + 2,1,*param_2 + 0x20);
    local_14 = FUN_0045c460(local_20,local_1c,local_18);
  }
  *param_1 = local_14;
  *(int *)(param_1 + 1) = local_c;
  FUN_0083e885();
  return;
}

