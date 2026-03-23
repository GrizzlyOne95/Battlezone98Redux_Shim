
void FUN_004f6c30(void)

{
  undefined4 *puVar1;
  int iVar2;
  size_t local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  undefined4 *local_6c;
  undefined4 *local_68;
  int local_64;
  int local_60;
  undefined4 *local_5c;
  int local_58;
  size_t local_54;
  int local_50;
  undefined4 local_4c;
  undefined4 local_44;
  char local_3f;
  char local_3e;
  char local_3d;
  undefined1 local_38 [4];
  char local_34 [15];
  undefined1 uStack_25;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined2 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a7b0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0050a970(local_14);
  if (*(char *)((int)local_38 + 0xa0) != '\0') {
    local_34[0] = '\0';
    local_34[1] = '\0';
    local_34[2] = '\0';
    local_34[3] = '\0';
    local_34[4] = '\0';
    local_34[5] = '\0';
    local_34[6] = '\0';
    local_34[7] = '\0';
    local_34[8] = '\0';
    local_34[9] = '\0';
    local_34[10] = '\0';
    local_34[0xb] = '\0';
    local_34[0xc] = '\0';
    local_34[0xd] = '\0';
    iVar2 = FUN_00434140(&DAT_00915540,0x2e);
    local_80 = iVar2 - 0x915540;
    if (8 < (int)local_80) {
      local_80 = 8;
    }
    strncpy(local_34,&DAT_00915540,local_80);
    puVar1 = (undefined4 *)(local_38 + 3);
    do {
      local_68 = puVar1;
      local_3f = *(char *)((int)local_68 + 1);
      puVar1 = (undefined4 *)((int)local_68 + 1);
    } while (local_3f != '\0');
    *(undefined4 *)((int)local_68 + 1) = 0x66646f2e;
    *(undefined1 *)((int)local_68 + 5) = 0;
    *(undefined1 *)((int)local_38 + 0xa0) = 0;
    iVar2 = FUN_00481f10(local_34);
    if (iVar2 != 0) {
      FUN_00589430(local_34);
      local_8 = 0;
      FUN_00589ab0(0,0x3986dd43,(int)local_38 + 0x90,*(undefined4 *)((int)local_38 + 0x90));
      FUN_00589ab0(0,0x2de2fe6c,(int)local_38 + 0x8c,*(undefined4 *)((int)local_38 + 0x8c));
      FUN_00589ab0(0,0x198af464,(int)local_38 + 0x84,*(undefined4 *)((int)local_38 + 0x84));
      FUN_00589ab0(0,0xc79eb669,(int)local_38 + 0x88,*(undefined4 *)((int)local_38 + 0x88));
      FUN_00589760(0,0x152e9876,(int)local_38 + 0x98,*(undefined4 *)((int)local_38 + 0x98));
      FUN_00589760(0,0x84d79505,(int)local_38 + 0x9c,*(undefined4 *)((int)local_38 + 0x9c));
      FUN_00589760(0,0xb4ef8667,(int)local_38 + 0x94,*(undefined4 *)((int)local_38 + 0x94));
      local_8 = 0xffffffff;
      FUN_00589530();
    }
  }
  if (*(char *)((int)local_38 + 100) != '\0') {
    *(undefined1 *)((int)local_38 + 100) = 0;
    local_24 = 0;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
    iVar2 = FUN_00434140(&DAT_00915540,0x2e);
    local_54 = iVar2 - 0x915540;
    if (8 < (int)local_54) {
      local_54 = 8;
    }
    strncpy((char *)&local_24,&DAT_00915540,local_54);
    puVar1 = (undefined4 *)&uStack_25;
    do {
      local_6c = puVar1;
      local_3e = *(char *)((int)local_6c + 1);
      puVar1 = (undefined4 *)((int)local_6c + 1);
    } while (local_3e != '\0');
    *(undefined4 *)((int)local_6c + 1) = 0x66646f2e;
    *(undefined1 *)((int)local_6c + 5) = 0;
    local_58 = 0;
    local_64 = 0x1e;
    local_50 = 0x1e;
    local_60 = 0x2d;
    iVar2 = FUN_00481f10(&local_24);
    if (iVar2 != 0) {
      FUN_00589430(&local_24);
      local_8 = 1;
      FUN_00589760(0,0x8af01d94,&local_58,local_58);
      FUN_00589760(0,0xb2ce525c,&local_64,local_64);
      FUN_00589760(0,0xa5739020,&local_50,local_50);
      FUN_00589760(0,0xc4283588,&local_60,local_60);
      FUN_00589800(0,0x1752b305,(int)local_38 + 0x6c,*(undefined4 *)((int)local_38 + 0x6c));
      local_8 = 0xffffffff;
      FUN_00589530();
    }
    local_44 = FUN_005e0bc0(1);
    local_70 = FUN_0045bba0();
    local_70 = local_58 - local_70;
    if (local_70 < 0) {
      local_70 = 0;
    }
    FUN_005e1240(local_70);
    FUN_005e11b0(local_58);
    local_4c = FUN_005e0bc0(2);
    local_7c = FUN_0045bba0();
    local_7c = local_64 - local_7c;
    if (local_7c < 0) {
      local_7c = 0;
    }
    FUN_005e1240(local_7c);
    FUN_005e11b0(local_64);
    local_78 = FUN_005e1190();
    local_78 = local_50 - local_78;
    if (local_78 < 0) {
      local_78 = 0;
    }
    FUN_005e10f0(local_78);
    FUN_005e1010(local_50);
    local_74 = FUN_005e1190();
    local_74 = local_60 - local_74;
    if (local_74 < 0) {
      local_74 = 0;
    }
    FUN_005e10f0(local_74);
    FUN_005e1010(local_60);
    local_24 = 0;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
    strncpy((char *)&local_24,&DAT_00915540,local_54);
    puVar1 = (undefined4 *)&uStack_25;
    do {
      local_5c = puVar1;
      local_3d = *(char *)((int)local_5c + 1);
      puVar1 = (undefined4 *)((int)local_5c + 1);
    } while (local_3d != '\0');
    *puVar1 = 0x7069612e;
    *(undefined1 *)((int)local_5c + 5) = 0;
    local_5c = puVar1;
    iVar2 = FUN_00481f10(&local_24);
    if (iVar2 == 0) {
      local_24 = 0x6e73696d;
      local_20 = 0x612e3431;
      local_1c = CONCAT13(local_1c._3_1_,0x7069);
    }
    FUN_005cb2d0(&local_24,2);
    if (**(char **)((int)local_38 + 0x90) != '\0') {
      FUN_00437d30(*(undefined4 *)((int)local_38 + 0x90));
    }
    FUN_004f6aa0();
    FUN_004f6ab0(*(undefined4 *)((int)local_38 + 0x8c),DAT_0091755c,0x41000000,0);
    if (0.1 <= *(float *)((int)local_38 + 0x6c)) {
      FUN_004f6ae0((int)*(float *)((int)local_38 + 0x6c),0x2d,0xf);
      *(undefined1 *)((int)local_38 + 0x66) = 1;
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

