
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_005732d0(int param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar7;
  float fVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  code *pcVar12;
  uint local_40;
  int local_38;
  int local_30;
  float local_2c;
  uint local_28;
  uint local_24;
  undefined2 local_1c;
  uint local_1a;
  undefined1 local_16;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  cVar1 = FUN_00571c30();
  if (cVar1 != '\0') {
    uVar3 = FUN_00822e60();
    if ((DAT_009180e0 == 0) && (DAT_00917f80 < uVar3)) {
      DAT_00917f88 = 0;
      DAT_00917f80 = uVar3 + 15000;
      DAT_009180e0 = 1;
      DAT_00917f9c = DAT_00917f80;
    }
    local_28 = 0;
    local_40 = 0;
    if (DAT_009180e0 != 0) {
      for (local_30 = FUN_0056f950(); local_30 != 0; local_30 = FUN_00577b50(local_30)) {
        uVar4 = FUN_00575f80();
        if (local_28 < uVar4) {
          local_28 = uVar4;
        }
        uVar4 = FUN_00575ff0();
        if (local_40 < uVar4) {
          local_40 = uVar4;
        }
      }
    }
    if (DAT_009180e0 == 1) {
      if (DAT_00917f88 < local_28) {
        DAT_00917f88 = local_28;
      }
      if ((DAT_00917f80 < uVar3) || (DAT_008e8cec <= DAT_00917f88)) {
        if (DAT_008e8cec <= DAT_00917f88) {
          DAT_00917f88 = DAT_008e8cec;
        }
        if (DAT_00917f88 == 0) {
          DAT_00917f80 = uVar3 + 15000;
          DAT_009180e0 = 0;
        }
        else {
          DAT_00917f88 = (uint)(((longlong)(int)DAT_00917f88 * 0xc & 0xffffffffU) / 10);
          if (DAT_00917f88 < 0x4b) {
            DAT_00917f88 = 0x4b;
          }
          DAT_00917f80 = 0;
          DAT_009180e0 = 2;
          DAT_00917f9c = uVar3;
        }
      }
    }
    if (1 < DAT_009180e0) {
      local_24 = local_28 / DAT_008e8d00;
      if ((int)DAT_008e8ce8 < (int)local_24) {
        local_24 = DAT_008e8ce8;
      }
      if ((int)local_24 < (int)DAT_008e8c00) {
        local_24 = DAT_008e8c00;
      }
      DAT_008e8c04 = local_24 & 0xfffffffc;
      DAT_00917fa8 = DAT_008e8c04;
      if (local_28 == 0) goto LAB_00573886;
      if (DAT_00917f9c < uVar3) {
        iVar5 = FUN_00822e60();
        local_2c = (float)((double)(iVar5 - _DAT_009180c4) +
                          (double)(&DAT_008a2fd0)[-(iVar5 - _DAT_009180c4 >> 0x1f)]) / 1000.0;
        uVar4 = FUN_00573100();
        if (uVar4 < DAT_00917f98) {
          DAT_00917f98 = uVar4;
        }
        local_38 = uVar4 - DAT_00917f98;
        if (local_2c == 0.0) {
          local_38 = 0;
          local_2c = 0.001;
        }
        DAT_00917f40 = (float)((double)local_38 + (double)(&DAT_008a2fd0)[-(local_38 >> 0x1f)]) /
                       local_2c;
        if ((local_28 < DAT_00917f88) && (local_40 <= DAT_008e8cfc)) {
          if ((float)((double)(int)DAT_008e8d14 +
                     (double)(&DAT_008a2fd0)[-((int)DAT_008e8d14 >> 0x1f)]) * 0.8 < DAT_00917f40) {
            DAT_008e8d14 = DAT_008e8d14 + _DAT_008e8cf0;
          }
        }
        else {
          DAT_008e8d14 = DAT_008e8d14 - _DAT_008e8d10;
        }
        if (1 < DAT_009180d8) {
          pcVar12 = FUN_004bc8c0;
          fVar8 = (float)((double)local_38 + (double)(&DAT_008a2fd0)[-(local_38 >> 0x1f)]) /
                  local_2c;
          uVar9 = DAT_00917f98;
          uVar10 = uVar4;
          uVar11 = DAT_008e8d14;
          FUN_0081e820("Net::AdjustBandwidth Prev Bytes: ",DAT_00917f98,", New Total: ",uVar4,
                       ", Time ",local_2c,"s, BW: ",fVar8,", Target BW: ");
          uVar6 = FUN_0081e660();
          pbVar7 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar6);
          pbVar7 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar7,uVar9)
          ;
          pbVar7 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar7);
          pbVar7 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                             (pbVar7,uVar10);
          pbVar7 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar7);
          pbVar7 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                             (pbVar7,local_2c);
          pbVar7 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar7);
          pbVar7 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar7,fVar8)
          ;
          pbVar7 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar7);
          pbVar7 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                             (pbVar7,uVar11);
          std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar7,pcVar12);
        }
        for (; DAT_00917f9c < iVar5 + 0x7dU; DAT_00917f9c = DAT_00917f9c + 0x7d) {
        }
        if (DAT_008e8d14 < DAT_008e8cf4) {
          DAT_008e8d14 = DAT_008e8cf4;
        }
        if (DAT_008e8d08 < DAT_008e8d14) {
          DAT_008e8d14 = DAT_008e8d08;
        }
        DAT_00917f98 = uVar4;
        _DAT_009180c4 = iVar5;
        if (DAT_009180d8 != 0) {
          uVar6 = FUN_008445c0();
          FUN_0056fcb0("Bandwidth = %lu, used rate = %lu",DAT_008e8d14,uVar6);
        }
      }
      if (DAT_008e8d14 < DAT_008e8cf4) {
        DAT_008e8d14 = DAT_008e8cf4;
      }
      if (DAT_008e8d08 < DAT_008e8d14) {
        DAT_008e8d14 = DAT_008e8d08;
      }
    }
    if (*(uint *)(param_1 + 0x420) < uVar3) {
      local_1c = 0x4250;
      local_1a = DAT_008e8d14;
      local_16 = (undefined1)((int)(DAT_008e8c04 + ((int)DAT_008e8c04 >> 0x1f & 3U)) >> 2);
      sVar2 = FUN_00572d90();
      if (sVar2 != 0) {
        FUN_00575890(&local_1c,10,0,0);
        *(uint *)(param_1 + 0x420) = uVar3 + 2000;
      }
      if ((DAT_009180c0 != DAT_008e8d14) || (DAT_00917f74 != DAT_008e8c04)) {
        DAT_009180c0 = DAT_008e8d14;
        DAT_00917f74 = DAT_008e8c04;
        uVar6 = FUN_0081e820("Net: Bandwidth usage now set to %d, Interval %d, Actual Used %d\n",
                             DAT_008e8d14,DAT_008e8c04,(int)DAT_00917f40);
        FUN_0081e710(uVar6);
      }
    }
  }
LAB_00573886:
  FUN_0083e885();
  return;
}

