
undefined4 FUN_004ccbd0(FILE *param_1,undefined4 param_2,uint param_3,char *param_4)

{
  long lVar1;
  size_t sVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  char *local_18;
  int local_14;
  undefined1 local_10 [2];
  undefined2 local_e;
  uint local_c;
  undefined1 local_5;
  
  local_c = param_3;
  FUN_004cc300(1,param_2,param_3);
  local_10[0] = (undefined1)param_2;
  local_e = (undefined2)local_c;
  if ((local_c & 0xffff) != local_c) {
    lVar1 = ftell(param_1);
    FUN_007d6b70("out_data type=%d size=%d @%d: data larger than 65535\n",param_2,local_c,lVar1);
  }
  sVar2 = fwrite(local_10,1,4,param_1);
  if (sVar2 == 4) {
    local_18 = param_4;
    uVar3 = 4;
    for (local_14 = 0; local_14 < (int)local_c; local_14 = local_14 + 1) {
      local_5 = *local_18 != '\0';
      uVar5 = (uint)(byte)local_5;
      sVar2 = fwrite(&local_5,1,1,param_1);
      if (sVar2 != 1) {
        uVar4 = uVar3;
        lVar1 = ftell(param_1);
        FUN_007d6c70("out_data type=%d size=%d @%d: could only write %d bytes\n",param_2,local_c,
                     lVar1,uVar3,uVar4,uVar5);
        return 0;
      }
      local_18 = local_18 + 1;
    }
    uVar3 = 1;
  }
  else {
    lVar1 = ftell(param_1);
    FUN_007d6c70("out_data type=%d size=%d @%d: could not write data header\n",param_2,local_c,lVar1
                );
    uVar3 = 0;
  }
  return uVar3;
}

