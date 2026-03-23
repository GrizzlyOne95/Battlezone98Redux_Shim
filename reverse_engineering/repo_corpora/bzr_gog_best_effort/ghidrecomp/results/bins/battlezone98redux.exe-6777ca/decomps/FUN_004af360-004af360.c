
void FUN_004af360(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char *_Str1;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 local_a8;
  undefined4 local_a4;
  uint local_a0;
  undefined4 *local_98;
  char local_94 [64];
  char local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008496e6;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004e0450(param_1,param_2,param_3);
  local_8 = 0;
  *local_98 = CraftClass::vftable;
  FUN_00589430(local_98 + 0xe);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589800(0xc287c42b,0x487f8e17,local_98 + 0x54,*(undefined4 *)(param_1 + 0x150));
  FUN_00589800(0xc287c42b,0xde687e15,local_98 + 0x55,*(undefined4 *)(param_1 + 0x154));
  FUN_00589800(0xc287c42b,0xf91cc422,local_98 + 0x56,*(undefined4 *)(param_1 + 0x158));
  FUN_00589800(0xc287c42b,0x462d7284,local_98 + 0x57,*(undefined4 *)(param_1 + 0x15c));
  FUN_0047b6c0(0xc287c42b,0xe0d32ed5,local_98 + 0x7c,0);
  FUN_0047b6c0(0xc287c42b,0xed291e8a,local_98 + 0x7c,local_98 + 0x7c);
  FUN_0047b6c0(0xc287c42b,0x72695529,local_98 + 0x58,local_98 + 0x7c);
  FUN_0047b6c0(0xc287c42b,0xf62bf4f4,local_98 + 0x5c,local_98 + 0x7c);
  FUN_0047b6c0(0xc287c42b,0x30459269,local_98 + 0x60,local_98 + 0x7c);
  FUN_0047b6c0(0xc287c42b,0xae256912,local_98 + 100,local_98 + 0x7c);
  FUN_0047b6c0(0xc287c42b,0x121488aa,local_98 + 0x68,local_98 + 0x7c);
  FUN_0047b6c0(0xc287c42b,0xa3a7b4fe,local_98 + 0x6c,local_98 + 0x7c);
  FUN_0047b6c0(0xc287c42b,0xe1e44043,local_98 + 0x70,local_98 + 0x7c);
  FUN_0047b6c0(0xc287c42b,0x861dffe6,local_98 + 0x74,local_98 + 0x7c);
  FUN_0047b6c0(0xc287c42b,0xf5578de9,local_98 + 0x78,local_98 + 0x7c);
  FUN_0047b6c0(0xc287c42b,0x4438fcf2,local_98 + 0xac,0);
  FUN_0047b6c0(0xc287c42b,0xad7c767c,local_98 + 0x80,local_98 + 0xac);
  FUN_0047b6c0(0xc287c42b,0x3bb77f51,local_98 + 0x84,local_98 + 0xac);
  FUN_0047b6c0(0xc287c42b,0x6b8a29c1,local_98 + 0x88,local_98 + 0xac);
  FUN_0047b6c0(0xc287c42b,0xb0914f33,local_98 + 0x8c,local_98 + 0x88);
  FUN_0047b6c0(0xc287c42b,0x3b7848ba,local_98 + 0x90,local_98 + 0xac);
  FUN_0047b6c0(0xc287c42b,0x4207428d,local_98 + 0x94,local_98 + 0xac);
  FUN_0047b6c0(0xc287c42b,0x8dff63e5,local_98 + 0x98,local_98 + 0xac);
  FUN_0047b6c0(0xc287c42b,0x551927e5,local_98 + 0x9c,local_98 + 0xac);
  FUN_0047b6c0(0xc287c42b,0xbc02535b,local_98 + 0xa0,local_98 + 0xac);
  FUN_0047b6c0(0xc287c42b,0x9dc1ff0e,local_98 + 0xa4,local_98 + 0xac);
  FUN_0047b6c0(0xc287c42b,0x31b20a11,local_98 + 0xa8,local_98 + 0xac);
  FUN_0047b6c0(0xc287c42b,0x6dd9ab88,local_98 + 0xb0,0);
  FUN_0047b6c0(0xc287c42b,0xc3a9b516,local_98 + 0xb4,0);
  FUN_0047b6c0(0xc287c42b,0x13e9acc1,local_98 + 0xb8,0);
  FUN_0047b6c0(0xc287c42b,0x23f871f8,local_98 + 0xbc,0);
  uVar5 = (uint)*(byte *)(param_1 + 0x300);
  puVar6 = local_98 + 0xc0;
  uVar2 = FUN_00446460("cloakAllowed",0x811c9dc5,puVar6,uVar5);
  FUN_00589920(0xc287c42b,uVar2,puVar6,uVar5);
  uVar2 = *(undefined4 *)(param_1 + 0x304);
  puVar6 = local_98 + 0xc1;
  uVar3 = FUN_00446460("cloakTime",0x811c9dc5,puVar6,uVar2);
  FUN_00589800(0xc287c42b,uVar3,puVar6,uVar2);
  uVar2 = *(undefined4 *)(param_1 + 0x308);
  puVar6 = local_98 + 0xc2;
  uVar3 = FUN_00446460("forceCloak",0x811c9dc5,puVar6,uVar2);
  FUN_00589800(0xc287c42b,uVar3,puVar6,uVar2);
  cVar1 = FUN_00589c20(0xc287c42b,0x7bf0e342,&local_a8,0,0);
  if (cVar1 == '\0') {
    local_98[0xc3] = DAT_00917a4c;
  }
  else {
    uVar2 = FUN_004cb870(local_a8,local_a4);
    local_98[0xc3] = uVar2;
  }
  cVar1 = FUN_00589c20(0xc287c42b,0x583c507f,&local_a8,0,0);
  if (cVar1 == '\0') {
    local_98[0xc4] = DAT_00917a4c;
  }
  else {
    uVar2 = FUN_004cb870(local_a8,local_a4);
    local_98[0xc4] = uVar2;
  }
  cVar1 = FUN_00589c20(0xc287c42b,0x600814f,&local_a8,0,0);
  if (cVar1 == '\0') {
    local_98[0xc5] = DAT_00917a40;
  }
  else {
    uVar2 = FUN_004cb870(local_a8,local_a4);
    local_98[0xc5] = uVar2;
  }
  local_a0 = 0;
  do {
    if (3 < local_a0) {
      local_8 = local_8 & 0xffffff00;
      FUN_00589530();
      local_8 = 0xffffffff;
      ExceptionList = local_10;
      FUN_0083e885();
      return;
    }
    sprintf(local_54,"damageEffect%d",local_a0 + 1);
    uVar2 = *(undefined4 *)(param_1 + 0x318 + local_a0 * 4);
    puVar6 = local_98 + local_a0 + 0xc6;
    uVar3 = FUN_00446460(local_54,0x811c9dc5,puVar6,uVar2);
    FUN_00589fe0(0xc287c42b,uVar3,puVar6,uVar2);
    if (local_98[local_a0 + 0xc6] == 0) {
      uVar2 = FUN_00446460(local_54,0x811c9dc5);
      _Str1 = (char *)FUN_00589620(0xc287c42b,uVar2);
      if (_Str1 != (char *)0x0) {
        iVar4 = _stricmp(_Str1,"NULL");
        if (iVar4 != 0) goto LAB_004afb1e;
      }
      sprintf(local_94,"dmgvhcl%d",local_a0 + 1);
      uVar2 = FUN_0044e4c0(local_94);
      local_98[local_a0 + 0xc6] = uVar2;
    }
LAB_004afb1e:
    local_a0 = local_a0 + 1;
  } while( true );
}

