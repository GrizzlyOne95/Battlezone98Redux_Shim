
void FUN_004dc710(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined1 local_1e4 [64];
  undefined1 local_1a4 [12];
  undefined1 local_198 [12];
  int local_18c;
  undefined4 local_188;
  undefined4 local_184;
  int local_180;
  int local_17c;
  float local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  undefined4 local_168;
  int local_164;
  int local_160;
  undefined4 local_15c;
  int local_158;
  void *local_154;
  short local_150 [2];
  int local_14c;
  int local_148;
  undefined4 *local_144;
  int *local_140;
  char local_139;
  undefined4 local_138 [16];
  undefined4 local_f8 [10];
  undefined8 local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined4 local_b8 [10];
  double local_90;
  double local_88;
  double local_80;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
  float local_5c;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined1 local_3c [40];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a13f;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_139 = 1;
  local_139 = FUN_004ce910(param_1,&local_164,4,local_14);
  local_178 = 0.2 / (float)local_164;
  local_148 = 0;
  while ((local_148 < local_164 && (local_139 != '\0'))) {
    FUN_007c9cf0((float)local_148 * local_178 + 0.25);
    if ((local_139 == '\0') || (cVar1 = FUN_004ce1c0(param_1,"[GameObject]"), cVar1 == '\0')) {
      local_168 = 0;
    }
    else {
      local_168 = 1;
    }
    local_139 = (char)local_168;
    if ((char)local_168 == '\0') break;
    if ((((((char)local_168 == '\0') || (cVar1 = FUN_004cf210(param_1,&local_188,8), cVar1 == '\0'))
         || (cVar1 = FUN_004ce820(param_1,local_150,2), cVar1 == '\0')) ||
        ((cVar1 = FUN_004ced10(param_1,&local_60,0xc), cVar1 == '\0' ||
         (cVar1 = FUN_004ce910(param_1,&local_174,4), cVar1 == '\0')))) ||
       ((cVar1 = FUN_004ce2f0(param_1,local_3c,0x28), cVar1 == '\0' ||
        (cVar1 = FUN_004ce910(param_1,&local_160,4), cVar1 == '\0')))) {
      local_170 = 0;
    }
    else {
      local_170 = 1;
    }
    local_139 = (char)local_170;
    if ((char)local_170 != '\0') {
      if (DAT_00917b20 < 0x3ea) {
        local_139 = FUN_004ce4e0(param_1,&local_16c,4);
        puVar3 = &DAT_008fe1e0;
        puVar5 = local_b8;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar5 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar5 = puVar5 + 1;
        }
        local_90 = (double)local_60;
        local_88 = (double)local_5c;
        local_80 = (double)local_58;
      }
      else {
        cVar1 = FUN_004cf7b0(param_1,&local_16c,4);
        if ((cVar1 == '\0') || (cVar1 = FUN_004cef70(param_1,local_b8,0x40), cVar1 == '\0')) {
          local_15c = 0;
        }
        else {
          local_15c = 1;
        }
        local_139 = (char)local_15c;
      }
    }
    if ((local_139 == '\0') || (local_14c = FUN_004e0f70(local_188,local_184), local_14c == 0))
    break;
    FUN_007d6a70("(%s) is loading (obj #%d)\n",local_14c + 100,local_148);
    local_18c = local_14c + 0x30;
    local_140 = (int *)FUN_004e1190(local_b8,local_174,local_160,(int)local_150[0],local_3c);
    local_139 = (**(code **)(*local_140 + 0x50))(param_1);
    if (local_139 == '\0') break;
    local_154 = operator_new(8);
    local_8 = 0;
    if (local_154 == (void *)0x0) {
      local_158 = 0;
    }
    else {
      local_158 = FUN_004cc910(local_16c,local_140);
    }
    local_17c = local_158;
    local_8 = 0xffffffff;
    local_180 = local_158;
    if (local_158 == 0) break;
    if (local_160 != 0) {
      DAT_00917afc = local_140;
      uVar2 = (**(code **)(local_140[6] + 0x2c))();
      FUN_0062c190(uVar2);
    }
    local_144 = (undefined4 *)FUN_0045c4d0();
    puVar3 = (undefined4 *)FUN_004795e0(local_198,local_144);
    local_78 = *puVar3;
    local_74 = puVar3[1];
    local_70 = puVar3[2];
    local_54 = local_78;
    local_50 = local_74;
    local_4c = local_70;
    puVar3 = (undefined4 *)FUN_004560b0(local_1a4,local_144);
    local_6c = *puVar3;
    local_68 = puVar3[1];
    local_64 = puVar3[2];
    local_48 = local_6c;
    local_44 = local_68;
    local_40 = local_64;
    puVar3 = (undefined4 *)FUN_0081f920(local_1e4,&local_78,&local_6c);
    puVar5 = local_138;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar3 = local_138;
    puVar5 = local_f8;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    local_d0 = *(undefined8 *)(local_144 + 10);
    local_c8 = *(undefined8 *)(local_144 + 0xc);
    local_c0 = *(undefined8 *)(local_144 + 0xe);
    puVar3 = local_f8;
    puVar5 = local_144;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    FUN_004db100();
    local_148 = local_148 + 1;
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

