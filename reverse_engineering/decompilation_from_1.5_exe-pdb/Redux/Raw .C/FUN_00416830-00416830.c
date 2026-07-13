
undefined4 * __thiscall
FUN_00416830(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008449a8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004390b0(&param_2,param_3,1,0);
  local_8 = 0;
  *param_1 = CStreamingOggSound::vftable;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = param_5;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xb] = param_4;
  param_1[10] = 1;
  FUN_00416e10(*(undefined4 *)param_1[1],0);
  ExceptionList = local_10;
  return param_1;
}

