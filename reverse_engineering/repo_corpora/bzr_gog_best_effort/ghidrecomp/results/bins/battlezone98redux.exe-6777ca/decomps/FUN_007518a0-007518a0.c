
void FUN_007518a0(undefined4 *param_1)

{
  undefined1 local_30 [16];
  undefined1 local_20 [8];
  undefined1 local_18 [12];
  int *local_c;
  undefined1 local_5;
  
  FUN_0073a590(*param_1,param_1[1]);
  FUN_0073a6e0(local_18);
  local_c = (int *)FUN_006aa1d0();
  FUN_0073a970(local_20);
  FUN_0073a590(*param_1,param_1[1]);
  local_5 = (**(code **)(*local_c + 0x68))();
  FUN_0073e7e0(local_30,param_1[2],local_5);
  return;
}

