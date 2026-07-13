
void FUN_0067f240(void)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined1 local_6c [8];
  undefined1 local_64 [4];
  undefined1 local_60 [4];
  undefined1 local_5c [4];
  undefined1 local_58 [8];
  undefined1 local_50 [4];
  int local_4c;
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  undefined4 local_40;
  undefined4 local_3c;
  undefined1 local_38 [4];
  int local_34;
  undefined1 local_30 [4];
  int *local_2c;
  char local_28 [32];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_2c = (int *)FUN_0045ca50();
  if (local_2c == (int *)0x0) {
    DAT_008e8c0f = 1;
  }
  else {
    local_40 = (**(code **)(*local_2c + 0x50))();
    FUN_00424640(local_38);
    FID_conflict_begin(local_48);
    while (cVar1 = FUN_00420f10(local_48), cVar1 != '\0') {
      puVar2 = (undefined4 *)FUN_004237d0();
      FUN_004e0f70(*puVar2,puVar2[1]);
      FUN_00422190();
    }
    DAT_008e8c0f = 1;
    local_3c = (**(code **)(*local_2c + 0x4c))();
    puVar2 = (undefined4 *)FID_conflict_begin(local_5c);
    uVar5 = *puVar2;
    puVar2 = (undefined4 *)FUN_00424640(local_60);
    FUN_00683d40(*puVar2,uVar5);
    puVar2 = (undefined4 *)FID_conflict_begin(local_50);
    uVar5 = *puVar2;
    puVar2 = (undefined4 *)FUN_00424640(local_64);
    FUN_00683d40(*puVar2,uVar5);
    FUN_00424640(local_30);
    FID_conflict_begin(local_44);
    iVar3 = FUN_00416410();
    iVar4 = FUN_00416410();
    uVar5 = FUN_00416410(iVar3 - iVar4);
    FUN_007d6a70("Preloading Meshes.  %d automatically identified, %d manually identified\n",uVar5);
    local_28[0] = '\0';
    local_28[1] = '\0';
    local_28[2] = '\0';
    local_28[3] = '\0';
    local_28[4] = '\0';
    local_28[5] = '\0';
    local_28[6] = '\0';
    local_28[7] = '\0';
    local_28[8] = '\0';
    local_28[9] = '\0';
    local_28[10] = '\0';
    local_28[0xb] = '\0';
    local_28[0xc] = '\0';
    local_28[0xd] = '\0';
    local_28[0xe] = '\0';
    local_28[0xf] = '\0';
    local_28[0x10] = '\0';
    local_28[0x11] = '\0';
    local_28[0x12] = '\0';
    local_28[0x13] = '\0';
    local_28[0x14] = '\0';
    local_28[0x15] = '\0';
    local_28[0x16] = '\0';
    local_28[0x17] = '\0';
    local_28[0x18] = '\0';
    local_28[0x19] = '\0';
    local_28[0x1a] = '\0';
    local_28[0x1b] = '\0';
    local_28[0x1c] = '\0';
    local_28[0x1d] = '\0';
    local_28[0x1e] = '\0';
    local_28[0x1f] = 0;
    local_4c = FUN_00416410();
    local_34 = 0;
    while (cVar1 = FUN_00420f10(local_44), cVar1 != '\0') {
      FUN_00421ea0();
      uVar5 = FUN_0041f870();
      sprintf(local_28,"%s.mesh",uVar5);
      uVar5 = FUN_004237d0();
      FUN_004222f0(local_6c,uVar5);
      FUN_0067f090(local_58,local_28);
      FUN_004499a0();
      local_34 = local_34 + 1;
      FUN_007c9cf0(((float)local_34 * 0.5) / (float)local_4c + 0.5);
      FUN_00422190();
    }
  }
  FUN_0083e885();
  return;
}

