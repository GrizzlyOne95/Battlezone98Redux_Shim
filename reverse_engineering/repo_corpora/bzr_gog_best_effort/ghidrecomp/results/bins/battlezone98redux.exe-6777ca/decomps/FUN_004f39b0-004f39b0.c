
void __thiscall
FUN_004f39b0(int param_1,char *param_2,undefined4 param_3,float param_4,char *param_5)

{
  char *_Dest;
  char cVar1;
  uint uVar2;
  void *pvVar3;
  undefined4 uVar4;
  void *pvVar5;
  size_t sVar6;
  bool bVar7;
  float10 fVar8;
  float fVar9;
  char *local_88;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a678;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  _Dest = (char *)(param_1 + 0xc + *(int *)(param_1 + 8) * 0x18);
  local_14 = uVar2;
  strncpy(_Dest,param_2,0x10);
  _Dest[0xf] = '\0';
  if (param_5 == (char *)0x0) {
    bVar7 = false;
    if (DAT_00915567 != '\0') {
      basic_string<>(param_2);
      local_8 = 0;
      uVar4 = FUN_00489f20(&DAT_008752b0,0xffffffff);
      FUN_0045e1d0(local_44,0,uVar4);
      local_8._0_1_ = 1;
      FUN_0045e1d0(local_74,uVar4,0xffffffff);
      local_8 = CONCAT31(local_8._1_3_,2);
      uVar4 = FUN_0048b7d0(local_5c,local_44,&DAT_00876e6c);
      FUN_0045e0f0(uVar4);
      ~basic_string<>();
      uVar4 = FUN_0041f870();
      pvVar3 = (void *)FUN_00481af0(uVar4);
      bVar7 = pvVar3 != (void *)0x0;
      if (bVar7) {
        uVar4 = FUN_0041f870();
        sVar6 = FUN_00481a60(uVar4);
        pvVar5 = malloc(sVar6 + 1);
        *(void **)(_Dest + 0x10) = pvVar5;
        memcpy(*(void **)(_Dest + 0x10),pvVar3,sVar6);
        *(undefined1 *)(*(int *)(_Dest + 0x10) + sVar6) = 0;
        uVar4 = FUN_0041f870();
        FUN_00481990(uVar4);
      }
      local_8._0_1_ = 1;
      ~basic_string<>();
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    if (!bVar7) {
      pvVar3 = (void *)FUN_00481af0(param_2,uVar2);
      if (pvVar3 != (void *)0x0) {
        sVar6 = FUN_00481a60(param_2);
        pvVar5 = malloc(sVar6 + 1);
        *(void **)(_Dest + 0x10) = pvVar5;
        memcpy(*(void **)(_Dest + 0x10),pvVar3,sVar6);
        *(undefined1 *)(*(int *)(_Dest + 0x10) + sVar6) = 0;
        FUN_00481990(param_2);
        bVar7 = true;
      }
    }
    if (!bVar7) {
      _Dest[0x10] = '\0';
      _Dest[0x11] = '\0';
      _Dest[0x12] = '\0';
      _Dest[0x13] = '\0';
    }
  }
  else {
    local_88 = param_5;
    do {
      cVar1 = *local_88;
      local_88 = local_88 + 1;
    } while (cVar1 != '\0');
    sVar6 = (int)local_88 - (int)(param_5 + 1);
    pvVar3 = malloc(sVar6 + 1);
    *(void **)(_Dest + 0x10) = pvVar3;
    memcpy(*(void **)(_Dest + 0x10),param_5,sVar6);
    *(undefined1 *)(*(int *)(_Dest + 0x10) + sVar6) = 0;
  }
  *(undefined4 *)(_Dest + 0x14) = param_3;
  fVar8 = (float10)FUN_00822da0();
  fVar9 = (float)fVar8 + param_4;
  if ((0.0 < param_4) &&
     (*(float *)(param_1 + 0xfc) <= fVar9 && fVar9 != *(float *)(param_1 + 0xfc))) {
    *(float *)(param_1 + 0xfc) = fVar9;
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

