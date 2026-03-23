
void FUN_0068ba00(undefined4 param_1)

{
  uint uVar1;
  uint uVar2;
  MaterialManager *this;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar6;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_74 [8];
  undefined4 local_6c;
  undefined4 local_68;
  uint local_64;
  undefined4 *local_60;
  float local_5c;
  float local_58;
  uint local_54;
  int local_50;
  undefined4 *local_4c;
  int local_48;
  short *local_44;
  undefined4 *local_40;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_3c [24];
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f9a0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_4c = (undefined4 *)0x0;
  local_60 = (undefined4 *)0x0;
  local_40 = (undefined4 *)0x0;
  local_14 = uVar1;
  local_4c = (undefined4 *)FUN_00481af0(param_1,uVar1);
  if (local_4c != (undefined4 *)0x0) {
    uVar2 = FUN_00481a60(param_1);
    local_60 = local_4c + (uVar2 / 0x34) * 0xd;
    for (local_40 = local_4c; local_40 < local_60; local_40 = local_40 + 0xd) {
      local_24[0] = '\0';
      local_24[1] = '\0';
      local_24[2] = '\0';
      local_24[3] = '\0';
      local_24[4] = '\0';
      local_24[5] = '\0';
      local_24[6] = '\0';
      local_24[7] = '\0';
      local_24[8] = '\0';
      local_24[9] = '\0';
      local_24[10] = '\0';
      local_24[0xb] = '\0';
      local_24[0xc] = '\0';
      local_24[0xd] = '\0';
      local_24[0xe] = '\0';
      local_24[0xf] = 0;
      local_48 = 0;
      local_50 = 0;
      if (0x7ff < DAT_00920f00) {
        DAT_00920f00 = 0x800;
        FUN_007d6c70("Sprite table overflow\n");
        break;
      }
      puVar4 = local_40;
      puVar5 = (undefined4 *)(&DAT_00920f08 + DAT_00920f00 * 0x20);
      for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      sprintf(local_24,"%.8s.MAP",local_40 + 8);
      local_44 = (short *)FUN_00481af0(local_24,uVar1);
      if (local_44 == (short *)0x0) {
        FUN_006879a0(&local_48,&local_50,local_24);
      }
      else {
        local_64 = (uint)(0 < local_44[1]);
        local_54 = (uint)(2 < local_44[1]);
        local_48 = (int)*local_44 >> (0 < local_44[1]) + (2 < local_44[1]);
        local_50 = *(int *)(local_44 + 2);
      }
      local_44 = (short *)0x0;
      FUN_00481990(local_24);
      if ((local_48 == 0) || (local_50 == 0)) {
        FUN_007d6c70("Sprite texture file \"%s\" not found\n",local_24);
        FUN_0068b970(&DAT_025f8f38);
      }
      else {
        local_5c = 1.0 / (float)local_48;
        local_58 = 1.0 / (float)local_50;
        basic_string<>(local_24);
        local_8 = 0;
        pbVar7 = local_3c;
        pbVar6 = local_74;
        this = Ogre::MaterialManager::getSingleton();
        local_6c = Ogre::MaterialManager::getByName(this,pbVar6,pbVar7);
        local_8._0_1_ = 1;
        local_68 = local_6c;
        FUN_00449910(local_6c);
        local_8 = (uint)local_8._1_3_ << 8;
        FUN_004499a0();
        local_8 = 0xffffffff;
        ~basic_string<>();
        *(undefined2 *)(&DAT_025f8f40 + DAT_00920f00 * 0x24) = *(undefined2 *)(local_40 + 10);
        *(undefined2 *)(&DAT_025f8f42 + DAT_00920f00 * 0x24) = *(undefined2 *)((int)local_40 + 0x2a)
        ;
        *(undefined2 *)(&DAT_025f8f44 + DAT_00920f00 * 0x24) = *(undefined2 *)(local_40 + 0xb);
        *(undefined2 *)(&DAT_025f8f46 + DAT_00920f00 * 0x24) = *(undefined2 *)((int)local_40 + 0x2e)
        ;
        *(float *)(&DAT_025f8f48 + DAT_00920f00 * 0x24) =
             (float)*(ushort *)(local_40 + 10) * local_5c;
        *(float *)(&DAT_025f8f4c + DAT_00920f00 * 0x24) =
             (float)*(ushort *)((int)local_40 + 0x2a) * local_58;
        *(float *)(&DAT_025f8f50 + DAT_00920f00 * 0x24) =
             (float)((uint)*(ushort *)(local_40 + 10) + (uint)*(ushort *)(local_40 + 0xb)) *
             local_5c;
        *(float *)(&DAT_025f8f54 + DAT_00920f00 * 0x24) =
             (float)((uint)*(ushort *)((int)local_40 + 0x2a) +
                    (uint)*(ushort *)((int)local_40 + 0x2e)) * local_58;
        *(undefined4 *)(&DAT_025f8f58 + DAT_00920f00 * 0x24) = local_40[0xc];
      }
      DAT_00920f00 = DAT_00920f00 + 1;
    }
    FUN_00481990(param_1);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

