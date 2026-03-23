
void __thiscall FUN_004caf20(undefined4 *param_1,int param_2,uint param_3,uint param_4)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  undefined4 *local_16c;
  undefined4 local_168;
  float local_164 [3];
  undefined4 local_158;
  float local_154;
  float local_150;
  uint local_14c;
  undefined4 *local_148;
  char local_141;
  int local_140;
  undefined4 *local_138;
  char local_134 [64];
  char local_f4 [64];
  char local_b4 [64];
  char local_74 [64];
  char local_34 [32];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849e4b;
  local_10 = ExceptionList;
  uVar5 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = ExplosionClass::vftable;
  param_1[10] = param_2;
  local_16c = param_1;
  local_138 = param_1;
  local_14 = uVar5;
  FUN_0041fe40(&local_16c);
  local_138[2] = *(undefined4 *)(param_2 + 8);
  local_138[4] = param_3 & 0x7f7f7f7f;
  local_138[5] = param_4 & 0x7f7f7f7f;
  strncpy((char *)(local_138 + 6),(char *)(local_138 + 4),8);
  *(undefined1 *)(local_138 + 8) = 0;
  puVar9 = (undefined4 *)((int)local_138 + 0x17);
  do {
    local_148 = puVar9;
    local_141 = *(char *)((int)local_148 + 1);
    puVar9 = (undefined4 *)((int)local_148 + 1);
  } while (local_141 != '\0');
  *puVar9 = 0x66646f2e;
  *(undefined1 *)((int)local_148 + 5) = 0;
  local_148 = puVar9;
  uVar6 = FUN_0062ccc0(0,"fun3d\\ExplosionClass.cpp",uVar5);
  local_138[0xb] = uVar6;
  FUN_00589430(local_138 + 6);
  local_8 = 0;
  FUN_004cbc10(0xca0c1378,0x9c646a05,local_34,0);
  if (local_34[0] == '\0') {
    local_138[0xc] = *(undefined4 *)(param_2 + 0x30);
  }
  else {
    uVar6 = FUN_0068bed0(local_34);
    local_138[0xc] = uVar6;
  }
  FUN_00589760(0xca0c1378,0xe67274d5,local_138 + 0xd,*(undefined4 *)(param_2 + 0x34));
  if ((int)local_138[0xd] < 1) {
    local_138[0xd] = 1;
  }
  FUN_00589800(0xca0c1378,0xc7dc5ce9,local_138 + 0xe,1.0 / *(float *)(param_2 + 0x38));
  if (0.0 < (float)local_138[0xe]) {
    local_138[0xe] = 1.0 / (float)local_138[0xe];
  }
  FUN_00589800(0xca0c1378,0x18c612d2,local_138 + 0xf,*(undefined4 *)(param_2 + 0x3c));
  FUN_0047b6c0(0xca0c1378,0xa38eb173,local_138 + 0x10,param_2 + 0x40);
  FUN_00589800(0xca0c1378,0xb68798a6,local_138 + 0x14,*(undefined4 *)(param_2 + 0x50));
  local_138[0x15] = *(undefined4 *)(param_2 + 0x54);
  *(undefined2 *)(local_138 + 0x16) = *(undefined2 *)(param_2 + 0x58);
  cVar1 = FUN_00589800(0xca0c1378,0x5be2a777,local_164,0);
  cVar2 = FUN_00589800(0xca0c1378,0x7c8a1300,&local_150,0);
  cVar3 = FUN_00589800(0xca0c1378,0x52fd4a53,&local_154,0);
  cVar4 = FUN_00589800(0xca0c1378,0x38720d72,local_164 + 2,0);
  if (((cVar1 != '\0' || cVar2 != '\0') || cVar3 != '\0') || cVar4 != '\0') {
    local_138[0x15] = local_164[0] + local_150 + local_154 + local_164[2];
    local_14c = (uint)(local_164[0] != 0.0);
    if (local_150 == 0.0) {
      local_168 = 0;
    }
    else {
      local_168 = 2;
    }
    if (local_154 == 0.0) {
      local_164[1] = 0.0;
    }
    else {
      local_164[1] = 5.60519e-45;
    }
    if (local_164[2] == 0.0) {
      local_158 = 0;
    }
    else {
      local_158 = 8;
    }
    *(ushort *)(local_138 + 0x16) =
         (ushort)(local_164[0] != 0.0) | (ushort)local_168 | SUB42(local_164[1],0) |
         (ushort)local_158;
  }
  FUN_00589800(0xca0c1378,0x63c6a1be,local_138 + 0x17,*(undefined4 *)(param_2 + 0x5c));
  FUN_00589fe0(0xca0c1378,0xca3ece0e,local_138 + 0x19,*(undefined4 *)(param_2 + 100));
  FUN_005896c0(0xca0c1378,0x5c75569c,local_138 + 0x1a,*(undefined4 *)(param_2 + 0x68));
  if (0x10 < (int)local_138[0x1a]) {
    local_138[0x1a] = 0x10;
  }
  for (local_140 = 0; local_140 < (int)local_138[0x1a]; local_140 = local_140 + 1) {
    sprintf(local_134,"particleClass%d",local_140 + 1);
    sprintf(local_f4,"particleCount%d",local_140 + 1);
    sprintf(local_b4,"particleVeloc%d",local_140 + 1);
    sprintf(local_74,"particleBias%d",local_140 + 1);
    uVar6 = *(undefined4 *)(param_2 + 0x22c + local_140 * 4);
    puVar9 = local_138 + local_140 + 0x8b;
    uVar7 = FUN_00446460(local_134,0x811c9dc5,puVar9,uVar6);
    FUN_0058a050(0xca0c1378,uVar7,puVar9,uVar6);
    uVar6 = *(undefined4 *)(param_2 + 0x6c + local_140 * 4);
    puVar9 = local_138 + local_140 + 0x1b;
    uVar7 = FUN_00446460(local_f4,0x811c9dc5,puVar9,uVar6);
    FUN_00589760(0xca0c1378,uVar7,puVar9,uVar6);
    puVar9 = (undefined4 *)(param_2 + 0xac + local_140 * 0xc);
    uVar6 = *puVar9;
    uVar7 = puVar9[1];
    uVar10 = puVar9[2];
    puVar9 = local_138 + local_140 * 3 + 0x2b;
    uVar8 = FUN_00446460(local_b4,0x811c9dc5,puVar9,uVar6,uVar7,uVar10);
    FUN_00589ca0(0xca0c1378,uVar8,puVar9,uVar6,uVar7,uVar10);
    puVar9 = (undefined4 *)(param_2 + 0x16c + local_140 * 0xc);
    uVar6 = *puVar9;
    uVar7 = puVar9[1];
    uVar10 = puVar9[2];
    puVar9 = local_138 + local_140 * 3 + 0x5b;
    uVar8 = FUN_00446460(local_74,0x811c9dc5,puVar9,uVar6,uVar7,uVar10);
    FUN_00589ca0(0xca0c1378,uVar8,puVar9,uVar6,uVar7,uVar10);
  }
  local_8 = 0xffffffff;
  FUN_00589530();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

