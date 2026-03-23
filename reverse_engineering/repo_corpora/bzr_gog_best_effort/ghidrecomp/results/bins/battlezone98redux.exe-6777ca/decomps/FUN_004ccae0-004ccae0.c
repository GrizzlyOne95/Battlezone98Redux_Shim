
undefined4 FUN_004ccae0(FILE *param_1,undefined4 param_2,uint param_3,void *param_4)

{
  long lVar1;
  undefined4 uVar2;
  size_t sVar3;
  undefined1 local_c [2];
  undefined2 local_a;
  size_t local_8;
  
  FUN_004cc300(1,param_2,param_3);
  local_c[0] = (undefined1)param_2;
  local_a = (undefined2)param_3;
  if ((param_3 & 0xffff) != param_3) {
    lVar1 = ftell(param_1);
    FUN_007d6b70("out_data type=%d size=%d @%d: data larger than 65535\n",param_2,param_3,lVar1);
  }
  local_8 = fwrite(local_c,1,4,param_1);
  if (local_8 == 4) {
    sVar3 = fwrite(param_4,1,param_3,param_1);
    if (sVar3 == param_3) {
      uVar2 = 1;
    }
    else {
      local_8 = sVar3;
      lVar1 = ftell(param_1);
      FUN_007d6c70("out_data type=%d size=%d @%d: could only write %d bytes\n",param_2,param_3,lVar1
                   ,sVar3);
      uVar2 = 0;
    }
  }
  else {
    lVar1 = ftell(param_1);
    FUN_007d6c70("out_data type=%d size=%d @%d: could not write data header\n",param_2,param_3,lVar1
                );
    uVar2 = 0;
  }
  return uVar2;
}

