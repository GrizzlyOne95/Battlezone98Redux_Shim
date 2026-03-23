
undefined4 __thiscall FUN_006ad980(int param_1,char param_2,undefined4 *param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  ULONG_PTR UVar5;
  DWORD DVar6;
  BOOL BVar7;
  int *piVar8;
  undefined1 local_48 [8];
  undefined4 local_40;
  undefined4 local_3c;
  int local_38;
  undefined4 local_34;
  int local_30;
  DWORD local_2c;
  ulong local_28;
  LPOVERLAPPED local_24;
  DWORD local_20;
  DWORD local_1c;
  LPOVERLAPPED local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850228;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = param_1;
  do {
    while( true ) {
      while( true ) {
        LOCK();
        iVar2 = *(int *)(local_14 + 0x34);
        if (iVar2 == 1) {
          *(int *)(local_14 + 0x34) = 0;
          iVar2 = 1;
        }
        UNLOCK();
        if (iVar2 == 1) {
          FUN_006c8ce0(local_14 + 0x38);
          local_8 = 0;
          FUN_006c8f00(uVar1);
          local_8._0_1_ = 1;
          FUN_006d8a70(local_14 + 0x54);
          FUN_006acbe0(local_48);
          FUN_006ad700(local_48);
          FUN_006adef0();
          local_8 = (uint)local_8._1_3_ << 8;
          FUN_006c8f30();
          local_8 = 0xffffffff;
          FUN_006c8d50();
        }
        local_20 = 0;
        local_28 = 0;
        local_24 = (LPOVERLAPPED)0x0;
        SetLastError(0);
        if (param_2 == '\0') {
          local_2c = 0;
        }
        else {
          local_2c = *(DWORD *)(local_14 + 0x28);
        }
        local_38 = GetQueuedCompletionStatus
                             (*(HANDLE *)(local_14 + 0x14),&local_20,&local_28,&local_24,local_2c);
        local_1c = GetLastError();
        if (local_24 == (LPOVERLAPPED)0x0) break;
        local_18 = local_24;
        uVar3 = FUN_006abbb0();
        FUN_00416430(local_1c,uVar3);
        if (local_28 == 2) {
          puVar4 = (undefined4 *)FUN_00416430((local_18->u).s.Offset,local_18->Internal);
          local_40 = *puVar4;
          local_3c = puVar4[1];
          local_20 = (local_18->u).s.OffsetHigh;
        }
        else {
          UVar5 = FUN_00416410();
          local_18->Internal = UVar5;
          DVar6 = get();
          (local_18->u).s.Offset = DVar6;
          (local_18->u).s.OffsetHigh = local_20;
        }
        LOCK();
        DVar6 = local_18[1].u.s.Offset;
        if (DVar6 == 0) {
          local_18[1].u.s.Offset = 1;
          DVar6 = 0;
        }
        UNLOCK();
        if (DVar6 == 1) {
          local_30 = local_14;
          local_8 = 2;
          FUN_006ac940(local_14,&local_40,local_20);
          puVar4 = (undefined4 *)FUN_004fbb60();
          uVar3 = puVar4[1];
          *param_3 = *puVar4;
          param_3[1] = uVar3;
          local_34 = 1;
          local_8 = 0xffffffff;
          FUN_006ace40();
          ExceptionList = local_10;
          return local_34;
        }
      }
      if (local_38 == 0) break;
      if (local_28 != 1) {
        LOCK();
        *(undefined4 *)(local_14 + 0x20) = 0;
        UNLOCK();
        piVar8 = (int *)(local_14 + 0x1c);
        LOCK();
        iVar2 = *piVar8;
        *piVar8 = *piVar8;
        UNLOCK();
        if (iVar2 != 0) {
          LOCK();
          iVar2 = *(int *)(local_14 + 0x20);
          *(int *)(local_14 + 0x20) = 1;
          UNLOCK();
          if ((iVar2 == 0) &&
             (BVar7 = PostQueuedCompletionStatus(*(HANDLE *)(local_14 + 0x14),0,0,(LPOVERLAPPED)0x0)
             , BVar7 == 0)) {
            local_1c = GetLastError();
            uVar3 = FUN_006abbb0();
            puVar4 = (undefined4 *)FUN_00416430(local_1c,uVar3);
            uVar3 = puVar4[1];
            *param_3 = *puVar4;
            param_3[1] = uVar3;
            ExceptionList = local_10;
            return 0;
          }
          puVar4 = (undefined4 *)FUN_004fbb60();
          uVar3 = puVar4[1];
          *param_3 = *puVar4;
          param_3[1] = uVar3;
          ExceptionList = local_10;
          return 0;
        }
      }
    }
    if (local_1c != 0x102) {
      uVar3 = FUN_006abbb0();
      puVar4 = (undefined4 *)FUN_00416430(local_1c,uVar3);
      uVar3 = puVar4[1];
      *param_3 = *puVar4;
      param_3[1] = uVar3;
      ExceptionList = local_10;
      return 0;
    }
  } while (param_2 != '\0');
  puVar4 = (undefined4 *)FUN_004fbb60();
  uVar3 = puVar4[1];
  *param_3 = *puVar4;
  param_3[1] = uVar3;
  ExceptionList = local_10;
  return 0;
}

