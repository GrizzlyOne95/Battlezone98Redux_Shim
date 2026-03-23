
void FUN_0068b340(undefined4 param_1)

{
  int iVar1;
  MaterialManager *this;
  char *pcVar2;
  undefined4 *puVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_4e8 [8];
  undefined4 local_4e0;
  undefined4 local_4dc;
  float local_4d8;
  undefined4 local_4d4;
  uint local_4d0;
  float local_4cc;
  uint local_4c8;
  uint local_4c4;
  int local_4c0;
  char *local_4bc;
  int local_4b8;
  char *local_4b4;
  int local_4b0;
  short *local_4ac;
  int local_4a8;
  int local_4a4;
  int local_4a0;
  uint local_49c;
  char *local_498;
  int local_494;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_490 [24];
  char local_478 [1024];
  char local_78 [16];
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 local_48;
  char local_44 [32];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f966;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_4b4 = (char *)FUN_00481af0(param_1,local_14);
  if (local_4b4 == (char *)0x0) {
LAB_0068b953:
    ExceptionList = local_10;
    FUN_0083e885();
    return;
  }
  iVar1 = FUN_00481a60(param_1);
  local_4bc = local_4b4 + iVar1;
  local_498 = local_4b4;
LAB_0068b3b3:
  while (local_498 < local_4bc) {
    while ((local_498 < local_4bc && (iVar1 = FUN_0068b310((int)*local_498), iVar1 != 0))) {
      local_498 = local_498 + 1;
    }
    local_49c = 0;
    while ((local_498 < local_4bc && (iVar1 = FUN_0068b310((int)*local_498), iVar1 == 0))) {
      if (local_49c < 0x3ff) {
        local_478[local_49c] = *local_498;
        local_49c = local_49c + 1;
        local_498 = local_498 + 1;
      }
    }
    local_4d0 = local_49c;
    if (0x3ff < local_49c) {
      ___report_rangecheckfailure();
    }
    local_478[local_4d0] = '\0';
    local_68 = 0;
    local_64 = 0;
    local_60 = 0;
    local_5c = 0;
    local_58 = 0;
    local_54 = 0;
    local_50 = 0;
    local_4c = 0;
    local_48 = 0;
    iVar1 = sscanf(local_478,"@include \"%32[^\"]\"",&local_68);
    if (iVar1 != 1) {
      local_44[0] = '\0';
      local_44[1] = '\0';
      local_44[2] = '\0';
      local_44[3] = '\0';
      local_44[4] = '\0';
      local_44[5] = '\0';
      local_44[6] = '\0';
      local_44[7] = '\0';
      local_44[8] = '\0';
      local_44[9] = '\0';
      local_44[10] = '\0';
      local_44[0xb] = '\0';
      local_44[0xc] = '\0';
      local_44[0xd] = '\0';
      local_44[0xe] = '\0';
      local_44[0xf] = '\0';
      local_44[0x10] = '\0';
      local_44[0x11] = '\0';
      local_44[0x12] = '\0';
      local_44[0x13] = '\0';
      local_44[0x14] = '\0';
      local_44[0x15] = '\0';
      local_44[0x16] = '\0';
      local_44[0x17] = '\0';
      local_44[0x18] = '\0';
      local_44[0x19] = '\0';
      local_44[0x1a] = '\0';
      local_44[0x1b] = '\0';
      local_44[0x1c] = '\0';
      local_44[0x1d] = '\0';
      local_44[0x1e] = '\0';
      local_44[0x1f] = '\0';
      local_24 = 0;
      local_20 = 0;
      local_1c = 0;
      local_18 = 0;
      iVar1 = sscanf(local_478,"\"%32[^\"]\" %16s %d %d %d %d %d %d 0x%8x",local_44,&local_24,
                     &local_4a8,&local_4b0,&local_4b8,&local_4c0,&local_4a4,&local_4a0,&local_4d4);
      if (iVar1 != 9) goto LAB_0068b562;
      goto LAB_0068b6b4;
    }
    FUN_0068b340(&local_68);
  }
  goto LAB_0068b953;
LAB_0068b562:
  iVar1 = sscanf(local_478,"\"%32[^\"]\" %16s %hu %hu %hu %hu 0x%8x",local_44,&local_24,&local_4a8,
                 &local_4b0,&local_4b8,&local_4c0,&local_4d4);
  if (iVar1 == 7) {
    sprintf(local_78,"%.8s.MAP",&local_24);
    iVar1 = FUN_00481f10(local_78);
    if (iVar1 == 0) {
      iVar1 = FUN_006879a0(&local_4a4,&local_4a0,&local_24);
      if (iVar1 == 0) {
        local_4a4 = 0;
        local_4a0 = 0;
        FUN_007d6c70("Sprite texture file \"%s\" not found\n",local_78);
      }
    }
    else {
      local_4ac = (short *)FUN_00481af0(local_78);
      local_4c4 = (uint)(0 < local_4ac[1]);
      local_4c8 = (uint)(2 < local_4ac[1]);
      local_4a4 = (int)*local_4ac >> (0 < local_4ac[1]) + (2 < local_4ac[1]);
      local_4a0 = *(int *)(local_4ac + 2);
      FUN_00481990(local_78);
    }
LAB_0068b6b4:
    local_494 = 1;
    while ((local_494 < DAT_00920f00 &&
           (iVar1 = _stricmp(&DAT_00920f08 + local_494 * 0x20,local_44), iVar1 != 0))) {
      local_494 = local_494 + 1;
    }
    if (local_494 == DAT_00920f00) {
      if (0x7ff < DAT_00920f00) {
        DAT_00920f00 = 0x800;
        FUN_007d6c70("Sprite table overflow\n");
        goto LAB_0068b3b3;
      }
      DAT_00920f00 = DAT_00920f00 + 1;
    }
    pcVar2 = local_44;
    puVar3 = (undefined4 *)(&DAT_00920f08 + local_494 * 0x20);
    for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      puVar3 = puVar3 + 1;
    }
    if ((local_4a4 == 0) || (local_4a0 == 0)) {
      FUN_0068b970(&DAT_025f8f38);
    }
    else {
      local_4cc = 1.0 / (float)local_4a4;
      local_4d8 = 1.0 / (float)local_4a0;
      basic_string<>(&local_24);
      local_8 = 0;
      pbVar5 = local_490;
      pbVar4 = local_4e8;
      this = Ogre::MaterialManager::getSingleton();
      local_4e0 = Ogre::MaterialManager::getByName(this,pbVar4,pbVar5);
      local_8._0_1_ = 1;
      local_4dc = local_4e0;
      FUN_00449910(local_4e0);
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_004499a0();
      local_8 = 0xffffffff;
      ~basic_string<>();
      *(undefined2 *)(&DAT_025f8f40 + local_494 * 0x24) = (undefined2)local_4a8;
      *(undefined2 *)(&DAT_025f8f42 + local_494 * 0x24) = (undefined2)local_4b0;
      *(undefined2 *)(&DAT_025f8f44 + local_494 * 0x24) = (undefined2)local_4b8;
      *(undefined2 *)(&DAT_025f8f46 + local_494 * 0x24) = (undefined2)local_4c0;
      *(float *)(&DAT_025f8f48 + local_494 * 0x24) = (float)local_4a8 * local_4cc;
      *(float *)(&DAT_025f8f4c + local_494 * 0x24) = (float)local_4b0 * local_4d8;
      *(float *)(&DAT_025f8f50 + local_494 * 0x24) = (float)(local_4a8 + local_4b8) * local_4cc;
      *(float *)(&DAT_025f8f54 + local_494 * 0x24) = (float)(local_4b0 + local_4c0) * local_4d8;
      *(undefined4 *)(&DAT_025f8f58 + local_494 * 0x24) = local_4d4;
    }
  }
  goto LAB_0068b3b3;
}

