
void FUN_004b7150(undefined4 *param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int *local_8;
  
  local_8 = DAT_00917554;
  (**(code **)(*DAT_00917554 + 0x24))(*param_1,param_1[2],&local_18,&local_14);
  (**(code **)(*local_8 + 0x24))(*param_2,param_2[2],&local_10,&local_c);
  FUN_0068af40(DAT_00917580,local_18,local_14,local_10,local_c,param_3,0);
  return;
}

