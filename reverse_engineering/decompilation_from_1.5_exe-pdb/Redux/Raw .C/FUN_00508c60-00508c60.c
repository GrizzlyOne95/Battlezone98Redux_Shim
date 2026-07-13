
void FUN_00508c60(undefined4 param_1)

{
  float *pfVar1;
  char local_408 [1024];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pfVar1 = (float *)FUN_004ff820(param_1,1);
  if (pfVar1 != (float *)0x0) {
    sprintf(local_408,
            "{right_x=%f, right_y=%f, right_z=%f, up_x=%f, up_y=%f, up_z=%f, front_x=%f, front_y=%f, front_z=%f, posit_x=%f, posit_y=%f, posit_z=%f}"
            ,(double)*pfVar1,(double)pfVar1[1],(double)pfVar1[2],(double)pfVar1[3],(double)pfVar1[4]
            ,(double)pfVar1[5],(double)pfVar1[6],(double)pfVar1[7],(double)pfVar1[8],
            *(undefined8 *)(pfVar1 + 10),*(undefined8 *)(pfVar1 + 0xc),*(undefined8 *)(pfVar1 + 0xe)
           );
    FUN_0082cd77(param_1,local_408);
  }
  FUN_0083e885();
  return;
}

