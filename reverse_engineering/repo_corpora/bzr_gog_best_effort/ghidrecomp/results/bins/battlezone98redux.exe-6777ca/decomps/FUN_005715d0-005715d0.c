
void FUN_005715d0(void)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_78 [4];
  int local_74;
  undefined4 local_70;
  int *local_6c;
  undefined1 local_68 [4];
  int local_64;
  char local_5d;
  int *local_5c;
  uint local_58;
  int local_54;
  undefined1 local_50 [24];
  undefined1 local_38 [24];
  undefined2 local_20 [6];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b740;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  uVar3 = FUN_007659f0(uVar2);
  local_58 = FUN_00822e60(uVar2,uVar3);
  *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) & 0xfffffff7;
  *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) & 0xfffffffd;
  *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) & 0xfffffffb;
  *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) & 0xfffffffe;
  DAT_025cfa1c = DAT_008e9078;
  DAT_009183f4 = 0;
  DAT_009454b8 = 0;
  if (*(uint *)(local_54 + 0x86c) < local_58) {
    FUN_00626be0();
    *(uint *)(local_54 + 0x86c) = local_58 + 1000;
    DAT_00917fa8 = DAT_008e8c04;
  }
  FUN_005732d0();
  FUN_00764a10();
  local_70 = *(undefined4 *)(local_54 + 8);
  switch(local_70) {
  case 0:
    goto LAB_00571b06;
  case 2:
    if (DAT_00917f78 == '\0') {
      *(undefined4 *)(local_54 + 8) = 3;
    }
    else {
      *(undefined4 *)(local_54 + 8) = 4;
    }
    break;
  case 3:
    if (*(char *)(local_54 + 0x41c) != '\0') {
      *(undefined4 *)(local_54 + 8) = 4;
    }
    break;
  case 5:
  case 6:
    goto LAB_00571b06;
  }
  if (DAT_02cc2bc0 < local_58) {
    DAT_02cc2bc0 = local_58 + 20000;
    cVar1 = FUN_0056fc40(DAT_009180d4);
    if (cVar1 != '\0') {
      FUN_005738a0();
    }
  }
  if (local_58 + 500 < *(uint *)(local_54 + 0x434)) {
    *(uint *)(local_54 + 0x434) = local_58;
  }
  if ((DAT_02a13bb4 == 0) && (*(uint *)(local_54 + 0x434) < local_58)) {
    if (*(int *)(local_54 + 0x434) == 0) {
      FUN_00577460();
    }
    *(uint *)(local_54 + 0x434) = local_58 + 500;
    local_5d = FUN_00577510();
    if (local_5d != '\0') {
      FUN_007d6a70("sentsencs completed\n");
      DAT_02a13bb4 = 1;
    }
  }
  if (((*(char *)(local_54 + 0x864) != '\0') && (*(int *)(local_54 + 8) == 4)) &&
     (cVar1 = FUN_005776c0(), cVar1 != '\0')) {
    *(undefined1 *)(local_54 + 0x864) = 0;
  }
  if (((DAT_00917f78 != '\0') && (2000 < local_58 - *(int *)(local_54 + 0x42c))) &&
     ((local_74 = FUN_005771b0(DAT_009180d4), local_74 != 0 &&
      (cVar1 = FUN_0056f940(), cVar1 == '\0')))) {
    *(uint *)(local_54 + 0x42c) = local_58;
    FUN_005769d0();
  }
  if (((*(char *)(local_54 + 0x864) == '\0') &&
      (*(uint *)(local_54 + 0x430) < local_58 - *(int *)(local_54 + 0x428))) && (DAT_009180d4 != 0))
  {
    if (*(uint *)(local_54 + 0x430) < 3000) {
      *(int *)(local_54 + 0x430) = *(int *)(local_54 + 0x430) + 10;
    }
    *(uint *)(local_54 + 0x428) = local_58;
    if (DAT_009180d4 != 0) {
      FUN_00576b70();
    }
    FUN_0056fc80();
    FUN_0056fa50();
  }
  iVar4 = FUN_00434160();
  if (((iVar4 == 5) && (*(int *)(local_54 + 8) == 4)) && (iVar4 = FUN_0045ca50(), iVar4 != 0)) {
    FUN_005704d0();
  }
  if (((*(float *)(local_54 + 0x868) == 0.0) && (DAT_00917f8e != '\0')) &&
     (cVar1 = FUN_00577d50(), cVar1 != '\0')) {
    local_6c = (int *)FUN_00764760();
    (**(code **)(*local_6c + 0x34))(1);
    fVar5 = (float10)FUN_00822da0();
    *(float *)(local_54 + 0x868) = (float)fVar5 + 0.5;
  }
  else if (((*(float *)(local_54 + 0x868) != 0.0) &&
           (fVar5 = (float10)FUN_00822da0(),
           *(float *)(local_54 + 0x868) <= (float)fVar5 &&
           (float)fVar5 != *(float *)(local_54 + 0x868))) && (DAT_00917f4c == '\0')) {
    DAT_00917f4c = '\x01';
    FUN_005d48b0();
    goto LAB_00571b06;
  }
  if (((DAT_00917f4c != '\0') && (DAT_00917f78 != '\0')) && (iVar4 = FUN_00434160(), iVar4 == 5)) {
    local_20[0] = 0x5347;
    FUN_00575890(local_20,2,1,0);
    local_5c = (int *)FUN_00764760();
    if (local_5c != (int *)0x0) {
      (**(code **)(*local_5c + 0x34))(1);
      local_64 = FUN_0056f900();
      if (local_64 != 0) {
        basic_string<>(&DAT_00873ef0);
        local_8 = 0;
        basic_string<>("gameended");
        local_8._0_1_ = 1;
        (**(code **)(*local_5c + 0x20))(local_64 + 0x10,local_50,local_38);
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
        FUN_0042d8c0(local_68);
        FID_conflict_begin(local_78);
        while (cVar1 = FUN_00420f10(local_78), cVar1 != '\0') {
          iVar4 = FUN_0042da60();
          if (*(char *)(iVar4 + 0x7c) == '\0') {
            uVar3 = FUN_0042de50();
            FUN_00746e80(uVar3);
          }
          FUN_0042da80();
        }
      }
    }
  }
LAB_00571b06:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

