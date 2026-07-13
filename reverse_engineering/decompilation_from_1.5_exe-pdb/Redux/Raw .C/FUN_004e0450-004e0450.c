
void FUN_004e0450(int param_1,uint param_2,uint param_3)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 local_d4;
  undefined4 local_d0;
  int local_cc;
  undefined4 *local_c8;
  void *local_c4;
  int local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 *local_b4;
  int local_b0;
  int local_ac;
  char *local_a8;
  size_t local_a4;
  char *local_a0;
  char *local_9c;
  int local_98;
  int local_94;
  int local_90;
  int local_8c;
  char local_85;
  char local_84;
  undefined1 local_83;
  char local_82;
  undefined1 local_81;
  int local_80;
  undefined4 *local_78;
  char local_74 [32];
  char local_54 [16];
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a210;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004dab30(local_14);
  local_8 = 0;
  *local_78 = GameObjectClass::vftable;
  local_78[8] = param_1;
  local_c8 = local_78;
  FUN_0041fe40(&local_c8);
  uVar2 = get();
  FUN_00477530(uVar2);
  local_78[5] = *(undefined4 *)(param_1 + 0x14);
  local_78[6] = *(undefined4 *)(param_1 + 0x18);
  local_78[7] = *(undefined4 *)(param_1 + 0x1c);
  local_78[0xc] = param_2 & 0x7f7f7f7f;
  local_78[0xd] = param_3 & 0x7f7f7f7f;
  sprintf((char *)(local_78 + 0xe),"%.8s.odf",&param_2);
  iVar3 = FUN_00481f10(local_78 + 0xe);
  if (iVar3 == 0) {
    FUN_007d6c70("Missing game object %s",local_78 + 0xe);
  }
  FUN_00589430(local_78 + 0xe);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589c20(0xd3dd9cec,0x794b13b,local_78 + 10,local_78[0xc],local_78[0xd]);
  FUN_00589760(0xd3dd9cec,0x9de6f3f3,local_78 + 0x12,*(undefined4 *)(param_1 + 0x48));
  FUN_00589760(0xd3dd9cec,0x262c569b,local_78 + 0x13,*(undefined4 *)(param_1 + 0x4c));
  FUN_00589760(0xd3dd9cec,0xcdb7d0f4,local_78 + 0x14,*(undefined4 *)(param_1 + 0x50));
  FUN_00589800(0xd3dd9cec,0xed76d3a,local_78 + 0x15,*(undefined4 *)(param_1 + 0x54));
  FUN_00589760(0xd3dd9cec,0x19971f1b,local_78 + 0x16,*(undefined4 *)(param_1 + 0x58));
  FUN_00589760(0xd3dd9cec,0x21c4ff9b,local_78 + 0x17,*(undefined4 *)(param_1 + 0x5c));
  FUN_004cbc10(0xd3dd9cec,0x45a8bc04,local_78 + 0x19,param_1 + 100);
  if (*(char *)(local_78 + 0x19) == '\0') {
    local_78[0x18] = 0;
  }
  else {
    uVar2 = FUN_0068bed0(local_78 + 0x19);
    local_78[0x18] = uVar2;
  }
  FUN_004cbc10(0xd3dd9cec,0x98d7239c,local_78 + 0x21,param_1 + 0x84);
  FUN_004cbc10(0xd3dd9cec,0x48ad2aea,local_78 + 0x29,param_1 + 0xa4);
  FUN_00589760(0xd3dd9cec,0xba10bbdd,local_78 + 0x31,*(undefined4 *)(param_1 + 0xc4));
  FUN_00589800(0xd3dd9cec,&DAT_020844ad,local_78 + 0x32,*(undefined4 *)(param_1 + 200));
  cVar1 = FUN_004cbc10(0xd3dd9cec,0x3957bd3a,local_74,0);
  if (cVar1 == '\0') {
    iVar3 = _stricmp((char *)(local_78 + 0xe),"player.odf");
    if (iVar3 == 0) {
      *(undefined1 *)(local_78 + 0x33) = 0x61;
    }
    else {
      iVar3 = tolower((int)*(char *)(local_78 + 0xe));
      *(char *)(local_78 + 0x33) = (char)iVar3;
    }
  }
  else {
    iVar3 = tolower((int)local_74[0]);
    *(char *)(local_78 + 0x33) = (char)iVar3;
  }
  if ((int)local_78[0x14] < 1) {
    local_78[0x34] = 0;
    local_78[0x35] = 0;
  }
  else {
    local_8c = 0x6f6c;
    local_90 = CONCAT31(0x697073,*(undefined1 *)(local_78 + 0x33));
    sprintf(local_54,"%.8s.odf",&local_90);
    cVar1 = FUN_00571c40();
    if (((cVar1 != '\0') && (DAT_008e8c0d == '\0')) || (iVar3 = FUN_00481f10(local_54), iVar3 == 0))
    {
      if ((*(char *)(local_78 + 0x33) == 'c') || (*(char *)(local_78 + 0x33) == 's')) {
        local_81 = 0x73;
      }
      else {
        local_81 = 0x61;
      }
      local_90 = CONCAT31(local_90._1_3_,local_81);
    }
    FUN_00589c20(0xd3dd9cec,0xde331a5a,&local_90,local_90,local_8c);
    if (local_90 == 0 && local_8c == 0) {
      local_78[0x34] = 0;
    }
    else {
      uVar2 = FUN_004e0f70(local_90,local_8c);
      local_78[0x34] = uVar2;
    }
    local_94 = 0x7265;
    local_98 = CONCAT31(0x737573,*(undefined1 *)(local_78 + 0x33));
    sprintf(local_54,"%.8s.odf",&local_98);
    cVar1 = FUN_00571c40();
    if (((cVar1 != '\0') && (DAT_008e8c0d == '\0')) || (iVar3 = FUN_00481f10(local_54), iVar3 == 0))
    {
      if ((*(char *)(local_78 + 0x33) == 'c') || (*(char *)(local_78 + 0x33) == 's')) {
        local_83 = 0x73;
      }
      else {
        local_83 = 0x61;
      }
      local_98 = CONCAT31(local_98._1_3_,local_83);
    }
    FUN_00589c20(0xd3dd9cec,0x4eaf15b9,&local_98,local_98,local_94);
    if (local_98 == 0 && local_94 == 0) {
      local_78[0x35] = 0;
    }
    else {
      uVar2 = FUN_004e0f70(local_98,local_94);
      local_78[0x35] = uVar2;
    }
  }
  FUN_00589800(0xd3dd9cec,0x21c2c4f0,local_78 + 0x36,*(undefined4 *)(param_1 + 0xd8));
  FUN_00589800(0xd3dd9cec,0xf52cb94f,local_78 + 0x37,*(undefined4 *)(param_1 + 0xdc));
  FUN_00589800(0xd3dd9cec,0xb1c56677,local_78 + 0x38,*(undefined4 *)(param_1 + 0xe0));
  for (local_80 = 0; local_80 < 5; local_80 = local_80 + 1) {
    uVar6 = 0;
    puVar5 = local_78 + local_80 + 0x39;
    uVar2 = FUN_00446440(local_80 + 0x31,0x157ba160,puVar5,0);
    FUN_004e1c70(0xd3dd9cec,uVar2,puVar5,uVar6);
    uVar7 = 0;
    uVar6 = 0;
    piVar4 = &local_b0;
    uVar2 = FUN_00446440(local_80 + 0x31,0xfbf47dba,piVar4,0,0);
    FUN_00589c20(0xd3dd9cec,uVar2,piVar4,uVar6,uVar7);
    if (local_b0 == 0 && local_ac == 0) {
      local_78[local_80 + 0x3e] = 0;
    }
    else {
      uVar2 = FUN_00611e30(local_b0,local_ac);
      local_78[local_80 + 0x3e] = uVar2;
      if (((local_78[local_80 + 0x3e] != 0) && (cVar1 = FUN_00571c40(), cVar1 != '\0')) &&
         (((DAT_009175bf == '\0' && (*(int *)(local_78[local_80 + 0x3e] + 0xc) == 0x534e4950)) ||
          ((((DAT_008e8c0c == '\0' && (cVar1 = FUN_00571c50(), cVar1 == '\0')) &&
            (local_b0 == 0x6c707367)) && (local_ac == 0x746e69)))))) {
        local_78[local_80 + 0x3e] = 0;
      }
    }
  }
  local_78[0x43] = *(undefined4 *)(param_1 + 0x10c);
  local_78[0x44] = *(undefined4 *)(param_1 + 0x110);
  local_78[0x45] = *(undefined4 *)(param_1 + 0x114);
  local_78[0x46] = *(undefined4 *)(param_1 + 0x118);
  local_78[0x47] = *(undefined4 *)(param_1 + 0x11c);
  local_78[0x48] = *(undefined4 *)(param_1 + 0x120);
  local_78[0x49] = *(undefined4 *)(param_1 + 0x124);
  local_78[0x4a] = *(undefined4 *)(param_1 + 0x128);
  local_78[0x4b] = *(undefined4 *)(param_1 + 300);
  local_78[0x4c] = *(undefined4 *)(param_1 + 0x130);
  local_78[0x4f] = *(undefined4 *)(param_1 + 0x13c);
  local_78[0x50] = *(undefined4 *)(param_1 + 0x140);
  cVar1 = FUN_00589c20(0xd3dd9cec,0x9b30e763,&local_d4,0,0);
  if (cVar1 == '\0') {
    local_78[0x51] = *(undefined4 *)(param_1 + 0x144);
  }
  else {
    uVar2 = FUN_004cb870(local_d4,local_d0);
    local_78[0x51] = uVar2;
  }
  sprintf((char *)&local_24,"%.8s.inf",&param_2);
  local_84 = '\0';
  iVar3 = FUN_004344a0();
  if (iVar3 == 2) {
    sprintf((char *)&local_44,"%.8s.ios",&param_2);
    iVar3 = FUN_00481f10(&local_44);
    if (iVar3 != 0) {
      local_24 = local_44;
      local_20 = local_40;
      local_1c = local_3c;
      local_18 = local_38;
      local_84 = '\x01';
    }
  }
  if ((local_84 == '\0') && (iVar3 = FUN_00481f10(&local_24), iVar3 == 0)) {
    sprintf((char *)&local_34,"%.8s.inf",local_78 + 10);
    iVar3 = FUN_00481f10(&local_34);
    if (iVar3 != 0) {
      local_24 = local_34;
      local_20 = local_30;
      local_1c = local_2c;
      local_18 = local_28;
    }
  }
  local_a4 = FUN_00481a60(&local_24);
  if (local_a4 == 0) {
    local_9c = (char *)&local_24;
    local_c0 = (int)&local_24 + 1;
    do {
      local_85 = *local_9c;
      local_9c = local_9c + 1;
    } while (local_85 != '\0');
    local_cc = (int)local_9c - local_c0;
    local_bc = FUN_0083d92c(local_cc + 1);
    local_78[0x52] = local_bc;
    local_a8 = (char *)&local_24;
    local_a0 = (char *)local_78[0x52];
    do {
      local_82 = *local_a8;
      *local_a0 = local_82;
      local_a8 = local_a8 + 1;
      local_a0 = local_a0 + 1;
    } while (local_82 != '\0');
  }
  else {
    local_b8 = FUN_0083d92c(local_a4 + 1);
    local_78[0x52] = local_b8;
    local_c4 = (void *)FUN_00481af0(&local_24);
    memcpy((void *)local_78[0x52],local_c4,local_a4);
    *(undefined1 *)(local_78[0x52] + local_a4) = 0;
    FUN_00481990(&local_24);
  }
  if (DAT_008e7732 != '\0') {
    FUN_004e17a0();
  }
  local_b4 = local_78;
  if (local_78[10] != 0 || local_78[0xb] != 0) {
    FUN_0067eef0(local_78[10],local_78[0xb]);
  }
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

