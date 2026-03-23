
void FUN_0050a270(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  float10 fVar4;
  double local_3c;
  int local_34;
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  char *local_24;
  uint local_20;
  uint local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  float *local_c;
  undefined1 local_6;
  byte local_5;
  
  if (param_3 < 0) {
    iVar2 = FUN_0082c8f6();
    param_3 = param_3 + 1 + iVar2;
  }
  cVar1 = FUN_0082d490(param_2,param_3);
  local_5 = cVar1 + 0x30;
  FUN_004cd010(param_1,&local_5,1,&DAT_0087d178);
  local_5 = local_5 - 0x30;
  local_1c = (uint)local_5;
  switch(local_1c) {
  case 0:
    FUN_007d6a70();
    break;
  case 1:
    iVar2 = FUN_0082d2e8(param_2,param_3);
    local_6 = iVar2 != 0;
    local_20 = (uint)(byte)local_6;
    if ((bool)local_6) {
      local_24 = "true";
    }
    else {
      local_24 = "false";
    }
    FUN_007d6a70();
    FUN_004ccf20(param_1,&local_6,1,&DAT_0087d180);
    break;
  case 2:
    local_28 = FUN_004ff750(param_2,param_3);
    FUN_007d6a70(&DAT_0087d0f0,local_28);
    FUN_004cd1b0(param_1,&local_28,4,&DAT_0087d184);
    break;
  case 3:
    fVar4 = (float10)FUN_0082d3e1(param_2,param_3);
    local_3c = (double)fVar4;
    FUN_007d6a70();
    FUN_004cd440(param_1,&local_3c,8,&DAT_0087d188);
    break;
  case 4:
    local_2c = FUN_0082d377();
    FUN_007d6a70();
    FUN_004cd1b0(param_1,&local_14,4,&DAT_0087d18c);
    FUN_004cce90(param_1,local_2c,local_14,&DAT_0087d260);
    break;
  case 5:
    local_18 = 0;
    FUN_0082cd45();
    while (iVar2 = FUN_0082cb08(param_2,param_3), iVar2 != 0) {
      local_18 = local_18 + 1;
      FUN_0082d226();
    }
    FUN_004cd1b0(param_1,&local_18,4,"count");
    FUN_0082cd45();
    FUN_007d6a70();
    while (iVar2 = FUN_0082cb08(param_2,param_3), iVar2 != 0) {
      FUN_007d6a70();
      FUN_0050a270(param_1,param_2,0xfffffffe);
      FUN_007d6a70();
      FUN_0050a270(param_1,param_2,0xffffffff);
      FUN_0082d226();
    }
    FUN_007d6a70();
    break;
  case 6:
    uVar3 = FUN_0082d311(param_2,param_3);
    FUN_007d6a70("func%p",uVar3);
    break;
  case 7:
    iVar2 = FUN_0082c882(param_2,param_3);
    if (iVar2 != 0) {
      FUN_0082c82c();
      uVar3 = FUN_0082ba59(param_2,0xffffffff,0,0x811c9dc5);
      local_30 = FUN_00446460(uVar3);
      FUN_0082d226(param_2,0xfffffffd);
      FUN_004cd290(param_1,&local_30,4,"undefint");
      local_34 = local_30;
      if (local_30 == 0xe3f3088) {
        local_10 = FUN_004ff7a0(param_2,param_3);
        FUN_007d6a70();
        FUN_004cd520(param_1,local_10,0xc,"undefvector_3d");
      }
      else if (local_30 == 0x247e1851) {
        local_c = (float *)FUN_004ff820(param_2,param_3);
        FUN_007d6a70("{right_x=%f, right_y=%f, right_z=%f, up_x=%f, up_y=%f, up_z=%f, front_x=%f, front_y=%f, front_z=%f, posit_x=%f, posit_y=%f, posit_z=%f}"
                     ,(double)*local_c,(double)local_c[1],(double)local_c[2],(double)local_c[3],
                     (double)local_c[4],(double)local_c[5],(double)local_c[6],(double)local_c[7],
                     (double)local_c[8],*(undefined8 *)(local_c + 10),*(undefined8 *)(local_c + 0xc)
                     ,*(undefined8 *)(local_c + 0xe));
        FUN_004cd790(param_1,local_c,0x40,"undefmat_3d");
      }
    }
    break;
  case 8:
    uVar3 = FUN_0082d447(param_2,param_3);
    FUN_007d6a70("thread%p",uVar3);
  }
  return;
}

