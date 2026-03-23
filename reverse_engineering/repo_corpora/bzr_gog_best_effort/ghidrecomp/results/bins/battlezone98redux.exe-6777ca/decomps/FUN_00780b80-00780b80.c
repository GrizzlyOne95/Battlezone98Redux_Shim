
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00780b80(int param_1,int param_2,int param_3,int param_4)

{
  undefined4 local_c;
  undefined4 local_8;
  
  for (local_8 = param_2; local_8 <= param_4; local_8 = local_8 + 1) {
    for (local_c = param_1; local_c <= param_3; local_c = local_c + 1) {
      FUN_0077dc00(local_c,local_8);
    }
  }
  FUN_007777f0(param_1,param_2,param_3,param_4);
  _DAT_009454c0 = 1;
  return;
}

