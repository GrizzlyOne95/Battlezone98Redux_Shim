
void FUN_004b9da0(int param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  undefined4 *puVar6;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar7;
  uint uVar8;
  char **ppcVar9;
  float10 fVar10;
  float fVar11;
  char *apcStack_5f4 [6];
  float fVar12;
  uint uVar13;
  code *pcVar14;
  undefined1 local_5a8 [16];
  double local_598;
  undefined4 local_590;
  double local_58c;
  double local_584;
  double local_57c;
  double local_574;
  double local_56c;
  double local_564;
  double local_55c;
  double local_554;
  float *local_54c;
  undefined2 *local_548;
  undefined2 *local_544;
  float *local_540;
  int local_53c;
  int local_538;
  uint local_534;
  undefined4 *local_530;
  int local_52c;
  int local_528;
  int local_524;
  float *local_520;
  int local_51c;
  undefined4 *local_518;
  int local_514;
  int local_510;
  int local_50c;
  undefined1 *local_508;
  float *local_504;
  undefined2 *local_500;
  float *local_4fc;
  int local_4f8;
  float *local_4f4;
  uint local_4f0;
  byte *local_4ec;
  uint local_4e8;
  uint local_4e4;
  uint local_4e0;
  float local_4dc;
  float *local_4d8;
  int local_4d4;
  int local_4d0;
  int local_4cc;
  int local_4c8;
  char local_4c2;
  char local_4c1;
  int local_4c0;
  size_t local_4bc;
  float local_4b8;
  float local_4b4;
  uint local_4b0;
  float *local_4ac;
  uint local_4a8;
  int local_4a4;
  char local_49d;
  float *local_49c;
  undefined4 local_498;
  undefined4 local_494;
  undefined4 local_490;
  undefined2 local_48c;
  undefined1 local_488 [1152];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>();
  local_534 = FUN_00573100();
  local_4e0 = DAT_009180d0;
  local_4b0 = FUN_004b75b0();
  if ((int)local_4b0 < 1) {
    local_4b0 = 1;
  }
  local_4b0 = local_4b0 - 1;
  local_4b4 = (float)FUN_00822e60();
  local_50c = (int)local_4b4 - DAT_009180dc;
  local_57c = (double)local_50c + (double)(&DAT_008a2fd0)[-(local_50c >> 0x1f)];
  local_4b8 = (float)local_57c / 1000.0;
  if (local_4b8 == 0.0) {
    local_4b8 = 0.001;
  }
  local_544 = &DAT_009175c0;
  if ((DAT_00917f8d & 1) != 0) {
    DAT_00917f8d = DAT_00917f8d + 1;
  }
  DAT_009175c0._0_1_ = 0x5f;
  local_508 = (undefined1 *)((int)&DAT_009175c0 + 1);
  DAT_009175c0._1_1_ = DAT_00917f8d;
  local_4fc = (float *)&DAT_009175c2;
  local_49c = local_4fc;
  fVar10 = (float10)FUN_00822d80();
  *local_4fc = (float)fVar10;
  local_49c = local_4fc + 1;
  local_54c = local_4fc + -0x245d6f;
  if (DAT_00917f8d != 0) {
    memcpy(local_49c,&DAT_00917fc0,(uint)DAT_00917f8d);
    local_49c = (float *)((uint)DAT_00917f8d + (int)local_49c);
    DAT_00917f8d = 0;
  }
  local_4a8 = local_534;
  if (local_534 < local_4e0) {
    local_4e0 = local_534;
  }
  local_538 = local_534 - local_4e0;
  local_584 = (double)local_538 + (double)(&DAT_008a2fd0)[-(local_538 >> 0x1f)];
  local_4dc = (float)local_584 / local_4b8;
  local_4d4 = local_538;
  if (DAT_009180d8 != 0) {
    FUN_0081e820();
    FUN_0081e710();
  }
  if (DAT_009175b4 == (char *)0x0) {
    local_53c = DAT_008e8d14;
    local_598 = (double)DAT_008e8d14 + (double)(&DAT_008a2fd0)[-(DAT_008e8d14 >> 0x1f)];
    if (((float)local_598 < local_4dc) || ((int)local_4b4 - (int)DAT_009180c8 < 0))
    goto LAB_004ba91c;
  }
  if ((uint)DAT_009180c8 <= (uint)local_4b4) {
    DAT_009180c8 = (float)((int)DAT_009180c8 + DAT_008e8c04);
    if ((uint)DAT_009180c8 <= (uint)local_4b4) {
      DAT_009180c8 = (float)((int)local_4b4 + DAT_008e8c04);
    }
    if (DAT_009180d8 != 0) {
      FUN_0081e820();
      FUN_0081e710();
    }
  }
  while ((cVar1 = FUN_0041f890(), cVar1 == '\0' &&
         (uVar8 = (int)local_49c - 0x9175ba, uVar3 = FUN_004b75e0(), uVar8 < uVar3))) {
    pfVar4 = (float *)std::
                      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                      front((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)&DAT_0097a2c4);
    *local_49c = *pfVar4;
    *(undefined2 *)(local_49c + 1) = *(undefined2 *)(pfVar4 + 1);
    local_49c = (float *)((int)local_49c + 6);
    FUN_004bb2e0();
  }
  local_4f8 = 0;
  for (local_4c8 = 0;
      (local_4c8 < param_2 && (local_4a4 = *(int *)(param_1 + local_4c8 * 8), local_4a4 != 0));
      local_4c8 = local_4c8 + 1) {
    local_4d0 = (**(code **)(*(int *)(local_4a4 + 0x18) + 0x30))();
    local_49d = FUN_004b7650();
    local_4ac = local_49c;
    local_4d8 = local_49c;
    if (local_49d == '\0') {
      local_520 = local_49c + 7;
      local_4bc = 0x1c;
    }
    else {
      local_520 = (float *)((int)local_49c + 0x15);
      local_4bc = 0x15;
    }
    local_4ec = (byte *)((int)local_49c + 1);
    local_518 = (undefined4 *)((int)local_49c + 6);
    local_530 = (undefined4 *)((int)local_49c + 2);
    local_540 = local_49c;
    iVar5 = FUN_00417c70();
    local_4e8 = (uint)(local_4a4 == iVar5);
    local_590 = (*(code *)**(undefined4 **)(local_4a4 + 0x18))();
    if ((*(uint *)(local_4d0 + 0x14) & 0x200) == 0) {
      uVar3 = local_4e8 & 1;
      bVar2 = (**(code **)(*(int *)(local_4a4 + 0x18) + 4))();
      *local_4ec = (byte)(uVar3 << 7) | (bVar2 & 0xf) << 2;
    }
    else if ((*(uint *)(local_4d0 + 0x14) & 0x1000000) == 0) {
      *local_4ec = (byte)((local_4e8 & 1) << 7) | 1;
    }
    else {
      *local_4ec = (byte)((local_4e8 & 1) << 7) | 5;
    }
    puVar6 = (undefined4 *)(local_4d0 + 0x20);
    ppcVar9 = apcStack_5f4;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *ppcVar9 = (char *)*puVar6;
      puVar6 = puVar6 + 1;
      ppcVar9 = ppcVar9 + 1;
    }
    puVar6 = (undefined4 *)FUN_006255b0(local_5a8);
    local_498 = *puVar6;
    local_494 = puVar6[1];
    local_490 = puVar6[2];
    local_48c = *(undefined2 *)(puVar6 + 3);
    *local_518 = local_498;
    local_518[1] = local_494;
    local_518[2] = local_490;
    *(undefined2 *)(local_518 + 3) = local_48c;
    *local_530 = *(undefined4 *)(local_4a4 + 0x7c);
    if (local_49d == '\0') {
      local_4ac[5] = *(float *)(local_4d0 + 8);
      local_4ac[6] = *(float *)(local_4d0 + 0xc);
      for (local_4e4 = 0; local_4e4 < 8; local_4e4 = local_4e4 + 1) {
        *(byte *)((int)local_4ac + local_4e4 + 0x14) =
             *(byte *)((int)local_4ac + local_4e4 + 0x14) & 0x7f;
      }
    }
    else {
      *(char *)(local_4d8 + 5) = local_49d;
    }
    if ((*(uint *)(local_4d0 + 0x14) & 0x200) == 0) {
      (**(code **)(*(int *)(local_4a4 + 0x18) + 0x3c))();
    }
    *(undefined1 *)local_540 = (undefined1)local_4bc;
    local_500 = (undefined2 *)0x0;
    local_4f4 = local_49c + -0x245d70;
    local_4f0 = 0xffffffff;
    if (0 < (int)local_4b0) {
      local_528 = DAT_008e8d14;
      local_56c = (double)DAT_008e8d14 + (double)(&DAT_008a2fd0)[-(DAT_008e8d14 >> 0x1f)];
      iVar5 = FUN_008445c0();
      local_4f0 = (iVar5 - (local_4a8 - local_4e0)) / local_4b0;
    }
    uVar3 = FUN_004b75e0();
    if (uVar3 < local_4f0) {
      local_4f0 = FUN_004b75e0();
    }
    if (local_4f0 < (int)local_4f4 + local_4bc) {
      local_500 = &DAT_009175c0;
    }
    if (local_500 != (undefined2 *)0x0) {
      memcpy(local_488,local_49c,local_4bc);
      local_4a8 = FUN_00573100();
      local_510 = (local_4a8 - local_4e0) + (int)local_4f4 * local_4b0;
      local_58c = (double)local_510 + (double)(&DAT_008a2fd0)[-(local_510 >> 0x1f)];
      local_4dc = (float)local_58c / local_4b8;
      local_514 = DAT_008e8d14;
      local_554 = (double)DAT_008e8d14 + (double)(&DAT_008a2fd0)[-(DAT_008e8d14 >> 0x1f)];
      local_4d4 = local_510;
      if ((((float)local_554 < local_4dc) && (DAT_009175b4 == (char *)0x0)) ||
         (local_4c2 = FUN_004baa40(), local_4c2 == '\0')) goto LAB_004ba91c;
      for (local_4cc = local_4f8; local_4cc <= local_4c8; local_4cc = local_4cc + 1) {
        fVar10 = (float10)FUN_00822da0();
        *(float *)(*(int *)(param_1 + local_4cc * 8) + 0x84) = (float)fVar10;
        fVar10 = (float10)(**(code **)(*(int *)(*(int *)(param_1 + local_4cc * 8) + 0x18) + 0x1c))()
        ;
        *(float *)(*(int *)(param_1 + local_4cc * 8) + 0x8c) = (float)fVar10;
      }
      local_4f8 = local_4c8 + 1;
      local_4a8 = FUN_00573100();
      *local_508 = 0;
      local_49c = local_4fc + 1;
      memcpy(local_49c,local_488,local_4bc);
    }
    local_49c = (float *)((int)local_49c + local_4bc);
  }
  local_548 = &DAT_009175c0;
  local_504 = local_49c + -0x245d70;
  if (local_54c < local_504) {
    local_4a8 = FUN_00573100();
    local_51c = (local_4a8 - local_4e0) + (int)local_504 * local_4b0;
    local_55c = (double)local_51c + (double)(&DAT_008a2fd0)[-(local_51c >> 0x1f)];
    local_4dc = (float)local_55c / local_4b8;
    local_524 = DAT_008e8d14;
    local_564 = (double)DAT_008e8d14 + (double)(&DAT_008a2fd0)[-(DAT_008e8d14 >> 0x1f)];
    local_4d4 = local_51c;
    if (((local_4dc <= (float)local_564) || (DAT_009175b4 != (char *)0x0)) &&
       (local_4c1 = FUN_004baa40(), local_4c1 != '\0')) {
      for (local_4c0 = local_4f8; local_4c0 < local_4c8; local_4c0 = local_4c0 + 1) {
        fVar10 = (float10)FUN_00822da0();
        *(float *)(*(int *)(param_1 + local_4c0 * 8) + 0x84) = (float)fVar10;
        fVar10 = (float10)(**(code **)(*(int *)(*(int *)(param_1 + local_4c0 * 8) + 0x18) + 0x1c))()
        ;
        *(float *)(*(int *)(param_1 + local_4c0 * 8) + 0x8c) = (float)fVar10;
      }
    }
  }
LAB_004ba91c:
  if (2 < DAT_009180d8) {
    pcVar14 = FUN_004bc8c0;
    local_52c = local_4d4;
    local_574 = (double)local_4d4 + (double)(&DAT_008a2fd0)[-(local_4d4 >> 0x1f)];
    fVar11 = (float)local_574 / local_4b8;
    apcStack_5f4[5] = "TempStateSendAll Prev Bytes: ";
    apcStack_5f4[4] = (char *)0x4ba9b3;
    uVar3 = local_534;
    uVar8 = local_4a8;
    fVar12 = local_4b8;
    uVar13 = DAT_008e8d14;
    FUN_0081e820();
    apcStack_5f4[4] = (char *)0x4ba9ba;
    apcStack_5f4[4] = (char *)FUN_0081e660();
    apcStack_5f4[3] = (char *)0x4ba9c0;
    pbVar7 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
    apcStack_5f4[5] = (char *)0x4ba9cb;
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar7,uVar3);
    apcStack_5f4[5] = (char *)0x4ba9d1;
    pbVar7 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar7,uVar8);
    pbVar7 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar7,fVar12);
    pbVar7 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar7,fVar11);
    pbVar7 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
    pbVar7 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar7,uVar13);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar7,pcVar14);
  }
  FUN_00584530();
  FUN_0083e885();
  return;
}

