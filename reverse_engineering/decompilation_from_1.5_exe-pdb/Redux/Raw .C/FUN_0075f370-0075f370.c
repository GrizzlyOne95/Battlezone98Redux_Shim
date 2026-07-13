
void FUN_0075f370(undefined4 param_1,char param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined1 local_90 [8];
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined1 local_78 [4];
  undefined4 local_74;
  undefined4 local_70;
  undefined1 local_68 [4];
  undefined4 *local_64;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085cd90;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_0042d8c0(local_68);
  FID_conflict_begin(local_78);
  do {
    cVar1 = FUN_00420f10(local_78);
    if (cVar1 == '\0') {
LAB_0075f528:
      ExceptionList = local_10;
      FUN_0083e885();
      return;
    }
    local_64 = (undefined4 *)FUN_0042de50(uVar2);
    local_64 = (undefined4 *)*local_64;
    cVar1 = FUN_0056f780(param_1);
    if (cVar1 != '\0') {
      if (param_2 == '\0') {
        FUN_006b29f0(2);
        local_64[8] = local_88;
        local_64[9] = local_84;
        *(undefined2 *)(local_64 + 7) = 0;
        local_74 = FUN_0073a9f0(local_44);
        local_8 = 1;
        local_70 = local_74;
        uVar4 = FUN_0041f870();
        FUN_007d6a70("BZRNet P2P Failed RELAY Connect For Client %s - P2P Relay Response\n",uVar4);
        local_8 = 0xffffffff;
        ~basic_string<>();
        *local_64 = 0;
        uVar4 = FUN_006cb470();
        FUN_006cb4c0(uVar4);
      }
      else {
        puVar3 = (undefined4 *)FUN_006c9bd0(local_90);
        uVar4 = puVar3[1];
        local_64[8] = *puVar3;
        local_64[9] = uVar4;
        *(undefined2 *)(local_64 + 7) = 0x1e;
        local_80 = FUN_0073a9f0(local_2c);
        local_8 = 0;
        local_7c = local_80;
        uVar4 = FUN_0041f870();
        FUN_007d6a70("BZRNet P2P Starting RELAY Connect For Client %s - P2P Relay Response\n",uVar4)
        ;
        local_8 = 0xffffffff;
        ~basic_string<>();
        *local_64 = 6;
        FUN_006cb4c0(param_3);
      }
      goto LAB_0075f528;
    }
    FUN_0042da80();
  } while( true );
}

