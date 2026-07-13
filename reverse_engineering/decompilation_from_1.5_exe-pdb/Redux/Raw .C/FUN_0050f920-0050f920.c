
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void FUN_0050f920(char *param_1,uint param_2,uint param_3)

{
  uchar uVar1;
  undefined2 *puVar2;
  byte *pbVar3;
  float10 fVar4;
  Image local_c1a4 [44];
  undefined1 local_c178 [4];
  float local_c174;
  float local_c170;
  float local_c16c;
  float local_c168;
  int local_c164;
  int local_c160;
  char *local_c15c;
  int local_c158;
  int local_c154;
  float local_c150;
  int local_c14c;
  float local_c148;
  uint local_c144;
  float local_c140;
  uchar *local_c13c;
  undefined2 local_c137;
  byte local_c135;
  undefined2 local_c134;
  byte local_c132;
  int local_c130;
  int local_c12c;
  uchar *local_c128;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_c124 [24];
  uchar auStack_c10c [49152];
  char local_10c [256];
  undefined1 local_c [4];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  strncpy(local_10c,param_1,0x100);
  local_c15c = (char *)FUN_004fbaf0(local_10c,0x2e);
  if (local_c15c != (char *)0x0) {
    strncpy(local_c15c,".BMP",(size_t)(local_c + -(int)local_c15c));
  }
  local_c13c = Ogre::StdAllocPolicy::allocateBytes(param_2 * param_3 * 3,(char *)0x0,0,(char *)0x0);
  if (local_c13c != (uchar *)0x0) {
    FUN_007d6a70("Writing %dx%d shell map to %s\n",param_2,param_3,local_10c);
    for (local_c130 = 0; local_c130 < 0x40; local_c130 = local_c130 + 1) {
      puVar2 = (undefined2 *)FUN_00780fd0(local_c178,local_c130);
      local_c137 = *puVar2;
      local_c135 = *(byte *)(puVar2 + 1);
      local_c134 = local_c137;
      local_c132 = local_c135;
      for (local_c12c = 0; local_c12c < 0x100; local_c12c = local_c12c + 1) {
        uVar1 = FUN_0047fed0(0xff,(int)((uint)(byte)local_c134 * (local_c12c + 0x40)) / 0xff);
        auStack_c10c[local_c12c * 3 + local_c130 * 0x300] = uVar1;
        uVar1 = FUN_0047fed0(0xff,(int)((uint)local_c134._1_1_ * (local_c12c + 0x40)) / 0xff);
        auStack_c10c[local_c12c * 3 + local_c130 * 0x300 + 1] = uVar1;
        uVar1 = FUN_0047fed0(0xff,(int)((uint)local_c132 * (local_c12c + 0x40)) / 0xff);
        auStack_c10c[local_c12c * 3 + local_c130 * 0x300 + 2] = uVar1;
      }
    }
    local_c128 = local_c13c;
    local_c170 = ((DAT_00917394 - DAT_0091738c) * DAT_02cc50e4) / (float)(int)param_2;
    local_c168 = ((DAT_00917388 - DAT_00917390) * DAT_02cc50e4) / (float)(int)param_3;
    fVar4 = (float10)FUN_0044fb20(local_c170,local_c168);
    local_c140 = (float)fVar4;
    local_c174 = (DAT_00917394 + DAT_0091738c) * 0.5 * DAT_02cc50e4 -
                 (float)(int)param_2 * local_c140 * 0.5;
    local_c16c = (DAT_00917388 + DAT_00917390) * 0.5 * DAT_02cc50e4 +
                 (float)(int)param_3 * local_c140 * 0.5;
    local_c148 = local_c16c;
    for (local_c158 = 0; local_c158 < (int)param_3; local_c158 = local_c158 + 1) {
      local_c160 = (int)local_c148;
      local_c150 = local_c174;
      for (local_c14c = 0; local_c14c < (int)param_2; local_c14c = local_c14c + 1) {
        local_c164 = (int)local_c150;
        local_c154 = FUN_00780dc0(local_c164,local_c160);
        pbVar3 = (byte *)FUN_0050ce30(local_c164,local_c160);
        local_c144 = (uint)*pbVar3;
        *local_c128 = auStack_c10c[local_c144 * 3 + local_c154 * 0x300 + 2];
        local_c128[1] = auStack_c10c[local_c144 * 3 + local_c154 * 0x300 + 1];
        local_c128[2] = auStack_c10c[local_c144 * 3 + local_c154 * 0x300];
        local_c128 = local_c128 + 3;
        local_c150 = local_c150 + local_c140;
      }
      local_c148 = local_c148 - local_c140;
    }
    Ogre::Image::Image(local_c1a4);
    Ogre::Image::loadDynamicImage(local_c1a4,local_c13c,param_2,param_3,1,10,false,1,'\0');
    basic_string<>(local_10c);
    Ogre::Image::save(local_c1a4,local_c124);
    ~basic_string<>();
    free(local_c13c);
    Ogre::Image::~Image(local_c1a4);
  }
  FUN_0083e885();
  return;
}

