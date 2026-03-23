
void FUN_004889c0(int param_1,char *param_2)

{
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  void *pvVar5;
  undefined4 *local_190;
  size_t local_18c;
  size_t local_188;
  uint local_17c;
  undefined1 local_174 [24];
  undefined1 local_15c [24];
  undefined1 local_144 [47];
  undefined4 uStack_115;
  undefined1 local_110 [252];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849051;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  param_2[0] = '\0';
  param_2[1] = '\0';
  param_2[2] = '\0';
  param_2[3] = '\0';
  local_17c = 0;
  do {
    if (0xf5 < local_17c) {
LAB_00488a9e:
      puVar2 = &uStack_115;
      do {
        local_190 = puVar2;
        puVar2 = (undefined4 *)((int)local_190 + 1);
      } while (*(char *)((int)local_190 + 1) != '\0');
      *(undefined4 *)((int)local_190 + 1) = 0x7365642e;
      *(undefined1 *)((int)local_190 + 5) = 0;
      bVar1 = false;
      iVar3 = FUN_004344a0();
      if (iVar3 == 2) {
        basic_string<>((int)&uStack_115 + 1);
        local_8 = 0;
        uVar4 = FUN_00489f20(&DAT_008752b0,0xffffffff);
        FUN_0045e1d0(local_144,0,uVar4);
        local_8._0_1_ = 1;
        FUN_0045e1d0(local_15c,uVar4,0xffffffff);
        local_8 = CONCAT31(local_8._1_3_,2);
        uVar4 = FUN_0048b7d0(local_174,local_144,&DAT_00876e6c);
        FUN_0045e0f0(uVar4);
        ~basic_string<>();
        uVar4 = FUN_0041f870();
        pvVar5 = (void *)FUN_00481af0(uVar4);
        if (pvVar5 != (void *)0x0) {
          uVar4 = FUN_0041f870();
          local_188 = FUN_00481a60(uVar4);
          if (0x1f400 < (int)local_188) {
            local_188 = 0x1f400;
          }
          memcpy(param_2,pvVar5,local_188);
          param_2[local_188] = '\0';
          uVar4 = FUN_0041f870();
          FUN_00481990(uVar4);
          uVar4 = FUN_0041f870();
          FUN_00481ea0(uVar4);
          bVar1 = true;
        }
        local_8._0_1_ = 1;
        ~basic_string<>();
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
      if ((!bVar1) && (pvVar5 = (void *)FUN_00481af0((int)&uStack_115 + 1), pvVar5 != (void *)0x0))
      {
        local_18c = FUN_00481a60((int)&uStack_115 + 1);
        if (0x1f400 < (int)local_18c) {
          local_18c = 0x1f400;
        }
        memcpy(param_2,pvVar5,local_18c);
        param_2[local_18c] = '\0';
        FUN_00481990((int)&uStack_115 + 1);
        FUN_00481ea0((int)&uStack_115 + 1);
        bVar1 = true;
      }
      if (!bVar1) {
        builtin_strncpy(param_2,"NO DESCRIPTION",0xf);
      }
      ExceptionList = local_10;
      FUN_0083e885();
      return;
    }
    *(undefined1 *)((int)&uStack_115 + local_17c + 1) = *(undefined1 *)(param_1 + local_17c);
    if (*(char *)(param_1 + local_17c) == '.') {
      if (0xff < local_17c) {
        ___report_rangecheckfailure(local_14);
      }
      *(undefined1 *)((int)&uStack_115 + local_17c + 1) = 0;
      goto LAB_00488a9e;
    }
    local_17c = local_17c + 1;
  } while( true );
}

