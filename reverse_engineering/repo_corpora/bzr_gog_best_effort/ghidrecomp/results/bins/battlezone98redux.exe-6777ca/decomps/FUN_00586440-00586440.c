
void __thiscall FUN_00586440(undefined4 *param_1,int param_2,uint param_3,uint param_4)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  float10 fVar10;
  uint uVar11;
  undefined4 *local_88;
  float local_84 [3];
  float local_78;
  uint local_74;
  undefined4 local_70;
  uint local_6c;
  undefined4 local_68;
  float local_64;
  uint local_60;
  undefined4 *local_5c;
  char *local_58;
  int local_54;
  char local_4e;
  char local_4d;
  int local_4c;
  int local_48;
  undefined4 *local_40;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_3c [24];
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084bcb0;
  local_10 = ExceptionList;
  uVar5 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = OrdnanceClass::vftable;
  param_1[2] = param_2;
  local_88 = param_1;
  local_40 = param_1;
  local_14 = uVar5;
  FUN_0041fe40(&local_88);
  local_40[3] = *(undefined4 *)(param_2 + 0xc);
  local_40[4] = *(undefined4 *)(param_2 + 0x10);
  local_40[6] = param_3 & 0x7f7f7f7f;
  local_40[7] = param_4 & 0x7f7f7f7f;
  strncpy((char *)(local_40 + 8),(char *)(local_40 + 6),8);
  *(undefined1 *)(local_40 + 10) = 0;
  puVar8 = (undefined4 *)((int)local_40 + 0x1f);
  do {
    local_5c = puVar8;
    local_4e = *(char *)((int)local_5c + 1);
    puVar8 = (undefined4 *)((int)local_5c + 1);
  } while (local_4e != '\0');
  *puVar8 = 0x66646f2e;
  *(undefined1 *)((int)local_5c + 5) = 0;
  local_5c = puVar8;
  FUN_00589430(local_40 + 8);
  local_8 = 0;
  uVar6 = FUN_0062ccc0(0,"fun3d\\OrdnanceClass.cpp",uVar5);
  local_40[0xe] = uVar6;
  uVar6 = FUN_0062ccc0(0,"fun3d\\OrdnanceClass.cpp");
  local_40[0xc] = uVar6;
  *(undefined4 *)(local_40[0xc] + 0x14) = 0;
  puVar8 = &DAT_008fe1e0;
  puVar9 = (undefined4 *)(local_40[0xc] + 0x20);
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar9 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar9 = puVar9 + 1;
  }
  *(undefined4 *)(local_40[0xc] + 100) = 0;
  *(undefined4 *)(local_40[0xc] + 0x84) = 0x33;
  FUN_0047b6c0(0xd59a9357,0x6f31d8a1,local_24,0);
  if (local_24[0] != '\0') {
    iVar7 = FUN_004e3290(local_40[0xc],local_24,0,0);
    if (iVar7 == 0) {
      FUN_007d6b70("Ordnance \"%s\" could not add geometry \"%s\"\n",local_40 + 8,local_24);
    }
    FUN_0062e650(local_40[0xc],local_40[0xc] + 0xb0,local_40[0xc] + 0xbc);
    *(float *)(local_40[0xc] + 0xa0) =
         (*(float *)(local_40[0xc] + 0xb0) + *(float *)(local_40[0xc] + 0xbc)) * 0.5;
    *(float *)(local_40[0xc] + 0xa4) =
         (*(float *)(local_40[0xc] + 0xb4) + *(float *)(local_40[0xc] + 0xc0)) * 0.5;
    *(float *)(local_40[0xc] + 0xa8) =
         (*(float *)(local_40[0xc] + 0xb8) + *(float *)(local_40[0xc] + 0xc4)) * 0.5;
    iVar7 = local_40[0xc];
    fVar10 = (float10)FUN_0062e590(local_40[0xc],*(undefined4 *)(iVar7 + 0xa0),
                                   *(undefined4 *)(iVar7 + 0xa4),*(undefined4 *)(iVar7 + 0xa8));
    *(float *)(local_40[0xc] + 0xac) = (float)fVar10;
  }
  local_54 = FUN_0062ccc0(0,"fun3d\\OrdnanceClass.cpp");
  *(undefined4 *)(local_54 + 8) = local_40[6];
  *(undefined4 *)(local_54 + 0xc) = local_40[7];
  *(undefined4 *)(local_54 + 0x14) = 0x101;
  *(undefined4 *)(local_54 + 0x84) = 0x33;
  *(undefined4 *)(local_54 + 0x88) = 0;
  *(undefined4 *)(local_54 + 0x7c) = 0;
  *(undefined4 *)(local_54 + 0x80) = 0;
  uVar6 = FUN_0062c4a0(local_54,0,0,0);
  local_40[0xd] = uVar6;
  local_58 = local_24;
  do {
    local_4d = *local_58;
    local_58 = local_58 + 1;
  } while (local_4d != '\0');
  if (local_58 != local_24 + 1) {
    basic_string<>(&DAT_008a1ad8);
    local_8 = CONCAT31(local_8._1_3_,1);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
              (local_3c,local_24);
    iVar7 = FUN_005871b0(&DAT_008752b0,0);
    if (iVar7 != -1) {
      uVar11 = 0xffffffff;
      uVar5 = FUN_00489f20(&DAT_008752b0,0xffffffff);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
                (local_3c,uVar5,uVar11);
    }
    uVar6 = FUN_0041f870();
    sprintf((char *)(local_40[0xd] + 0x84),"%s",uVar6);
    FUN_0067eea0(local_40[0xd] + 0x84);
    local_8 = local_8 & 0xffffff00;
    ~basic_string<>();
  }
  FUN_00589c20(0xd59a9357,0x5acba4c4,&local_4c,0,0);
  if (local_4c == 0 && local_48 == 0) {
    local_40[0xf] = *(undefined4 *)(param_2 + 0x3c);
  }
  else {
    uVar6 = FUN_004cb870(local_4c,local_48);
    local_40[0xf] = uVar6;
  }
  FUN_00589c20(0xd59a9357,0x1564c7e9,&local_4c,0,0);
  if (local_4c == 0 && local_48 == 0) {
    local_40[0x10] = *(undefined4 *)(param_2 + 0x40);
  }
  else {
    uVar6 = FUN_004cb870(local_4c,local_48);
    local_40[0x10] = uVar6;
  }
  FUN_00589c20(0xd59a9357,0x427beb6f,&local_4c,0,0);
  if (local_4c == 0 && local_48 == 0) {
    local_40[0x11] = *(undefined4 *)(param_2 + 0x44);
  }
  else {
    uVar6 = FUN_004cb870(local_4c,local_48);
    local_40[0x11] = uVar6;
  }
  FUN_00589c20(0xd59a9357,0x77adb2b4,&local_4c,0,0);
  if (local_4c == 0 && local_48 == 0) {
    local_40[0x12] = *(undefined4 *)(param_2 + 0x48);
  }
  else {
    uVar6 = FUN_004cb870(local_4c,local_48);
    local_40[0x12] = uVar6;
  }
  FUN_00589800(0xd59a9357,0x7c7c544b,local_40 + 0x14,*(undefined4 *)(param_2 + 0x50));
  FUN_00589800(0xd59a9357,0xcafe92d0,local_40 + 0x15,*(undefined4 *)(param_2 + 0x54));
  FUN_00589760(0xd59a9357,0xe4af0ab6,local_40 + 0x13,*(undefined4 *)(param_2 + 0x4c));
  local_40[0x16] = *(undefined4 *)(param_2 + 0x58);
  *(undefined2 *)(local_40 + 0x17) = *(undefined2 *)(param_2 + 0x5c);
  cVar1 = FUN_00589800(0xd59a9357,0x5be2a777,&local_78,0);
  cVar2 = FUN_00589800(0xd59a9357,0x7c8a1300,local_84 + 2,0);
  cVar3 = FUN_00589800(0xd59a9357,0x52fd4a53,local_84,0);
  cVar4 = FUN_00589800(0xd59a9357,0x38720d72,&local_64,0);
  if (((cVar1 != '\0' || cVar2 != '\0') || cVar3 != '\0') || cVar4 != '\0') {
    local_40[0x16] = local_78 + local_84[2] + local_84[0] + local_64;
    local_74 = (uint)(local_78 != 0.0);
    if (local_84[2] == 0.0) {
      local_70 = 0;
    }
    else {
      local_70 = 2;
    }
    if (local_84[0] == 0.0) {
      local_84[1] = 0.0;
    }
    else {
      local_84[1] = 5.60519e-45;
    }
    if (local_64 == 0.0) {
      local_68 = 0;
    }
    else {
      local_68 = 8;
    }
    *(ushort *)(local_40 + 0x17) =
         (ushort)(local_78 != 0.0) | (ushort)local_70 | SUB42(local_84[1],0) | (ushort)local_68;
  }
  FUN_0047b6c0(0xd59a9357,0x541f3a64,(int)local_40 + 0x5f,param_2 + 0x5f);
  local_60 = (uint)*(byte *)(param_2 + 0x5e);
  FUN_00589760(0xd59a9357,0x92dacba,&local_60,local_60);
  local_6c = (uint)(local_60 != 0);
  *(bool *)((int)local_40 + 0x5e) = local_60 != 0;
  FUN_00589fe0(0xd59a9357,0xca3ece0e,local_40 + 0x1c,*(undefined4 *)(param_2 + 0x70));
  local_8 = 0xffffffff;
  FUN_00589530();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

