
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004fa380(void)

{
  undefined2 uVar1;
  char cVar2;
  MaterialManager *this;
  int iVar3;
  undefined2 *puVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar6;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_10b0 [8];
  undefined1 local_10a8 [8];
  undefined4 local_10a0;
  undefined4 local_109c;
  undefined4 local_1098;
  undefined4 local_1094;
  int local_1090;
  int local_108c;
  int local_1088;
  int local_1084;
  undefined2 local_1080;
  byte local_107e;
  uint local_107c;
  uint local_1078;
  uint local_1074;
  int local_1070;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_106c [24];
  undefined1 local_1054 [4096];
  char local_54 [32];
  char local_34 [32];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a991;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  DAT_009b7ca4 = FUN_00787ac0("LightningBolt","Bolts",0,&DAT_02cc40c0,local_14);
  FUN_00787a30("LightningBolt",&DAT_0087b984,&DAT_008a1ad8,local_54,0x20,&DAT_02cc40c0);
  if (local_54[0] != '\0') {
    basic_string<>(local_54);
    local_8 = 0;
    pbVar6 = local_106c;
    pbVar5 = local_10b0;
    this = Ogre::MaterialManager::getSingleton();
    local_10a0 = Ogre::MaterialManager::getByName(this,pbVar5,pbVar6);
    local_8._0_1_ = 1;
    local_1094 = local_10a0;
    FUN_00449910(local_10a0);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004499a0();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  cVar2 = FUN_004c85a0();
  if (cVar2 != '\0') {
    local_109c = FUN_00685480(local_10a8);
    local_8 = 2;
    local_1098 = local_109c;
    FUN_00449910(local_109c);
    local_8 = 0xffffffff;
    FUN_004499a0();
  }
  _DAT_009b7cb0 = DAT_0091755c;
  FUN_00787a30("LightningBolt","Color",&DAT_008a1ad8,local_34,0x20,&DAT_02cc40c0);
  if (local_34[0] == '\0') goto LAB_004fa76e;
  local_1078 = 0xff;
  local_107c = 0xff;
  local_1074 = 0xff;
  local_108c = 0xff;
  local_1090 = 0;
  iVar3 = sscanf(local_34,"\"%d %d %d %d\"",&local_1078,&local_107c,&local_1074,&local_108c);
  if (iVar3 != 4) {
    iVar3 = sscanf(local_34,"%d %d %d %d",&local_1078,&local_107c,&local_1074,&local_108c);
    if (iVar3 != 4) {
      iVar3 = sscanf(local_34,"\"%d %d %d\"",&local_1078,&local_107c,&local_1074);
      if (iVar3 != 3) {
        iVar3 = sscanf(local_34,"%d %d %d",&local_1078,&local_107c,&local_1074);
        if (iVar3 != 3) {
          iVar3 = sscanf(local_34,"%d",&local_1090);
          if (iVar3 == 1) {
            FUN_00787a30("Color","Palette",&DAT_008a1ad8,local_1054,0x1000,&DAT_02cc40c0);
            local_1088 = FUN_00481af0(local_1054);
            if (local_1088 == 0) {
              local_1088 = FUN_00481af0("objects.act");
              if (local_1088 == 0) goto LAB_004fa76e;
            }
            puVar4 = (undefined2 *)(local_1090 * 3 + local_1088);
            uVar1 = *puVar4;
            local_107e = *(byte *)(puVar4 + 1);
            local_1080._0_1_ = (byte)uVar1;
            local_1080._1_1_ = (byte)((ushort)uVar1 >> 8);
            _DAT_009b7cb0 =
                 (uint)(byte)local_1080 << 0x10 | 0xff000000 | (uint)local_1080._1_1_ << 8 |
                 (uint)local_107e;
            local_1080 = uVar1;
            FUN_00481990(local_1054);
          }
          goto LAB_004fa76e;
        }
      }
      _DAT_009b7cb0 =
           (local_1078 & 0xff) << 0x10 | 0xff000000 | (local_107c & 0xff) << 8 | local_1074 & 0xff;
      goto LAB_004fa76e;
    }
  }
  _DAT_009b7cb0 =
       local_108c << 0x18 | (local_1078 & 0xff) << 0x10 | (local_107c & 0xff) << 8 |
       local_1074 & 0xff;
LAB_004fa76e:
  iVar3 = FUN_00787ac0("LightningBolt","minDelay",5000,&DAT_02cc40c0);
  _DAT_009b7cb4 = (float)iVar3 * 0.001;
  iVar3 = FUN_00787ac0("LightningBolt","maxDelay",10000,&DAT_02cc40c0);
  DAT_009b7cb8 = (float)iVar3 * 0.001;
  iVar3 = FUN_00787ac0("LightningBolt","Duration",200,&DAT_02cc40c0);
  DAT_009b7cbc = (float)iVar3 * 0.001;
  iVar3 = FUN_00787ac0("LightningBolt","Distance",100,&DAT_02cc40c0);
  DAT_009b7cc0 = (float)iVar3;
  _DAT_009b7cc4 = 0;
  _DAT_009b7cc8 = 0;
  _DAT_009b7ccc = 0;
  _DAT_009b7cd0 = 0;
  FUN_00787a30("LightningBolt","Sound",&DAT_008a1ad8,&DAT_009b7cc4,0x10,&DAT_02cc40c0);
  if (0x10 < DAT_009b7ca4) {
    DAT_009b7ca4 = 0x10;
  }
  for (local_1070 = 0; local_1070 < 0x10; local_1070 = local_1070 + 1) {
    *(int *)(local_1084 + 0x28 + local_1070 * 4) = local_1084 + 0x6c + local_1070 * 0x103c;
  }
  *(undefined4 *)(local_1084 + 0x68) = 0;
  for (local_1070 = 0; local_1070 < DAT_009b7ca4; local_1070 = local_1070 + 1) {
    FUN_004fab60(0);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

