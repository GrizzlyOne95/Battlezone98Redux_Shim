
void FUN_0065f180(void)

{
  float *pfVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  float10 fVar6;
  char *_Buf2;
  size_t _Size;
  undefined1 local_88 [4];
  undefined1 local_84 [4];
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  int local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  undefined4 local_48;
  int local_44;
  undefined4 local_40;
  undefined1 local_3c [4];
  int local_38;
  FILE *local_34;
  int local_30;
  char local_29;
  uint local_28;
  int local_24;
  undefined4 local_20;
  int iStack_1c;
  int iStack_18;
  undefined4 uStack_14;
  int iStack_10;
  int iStack_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_28 = 0;
  uVar3 = FUN_005c7fb0();
  *(undefined4 *)(local_24 + 0xa4) = uVar3;
  if ((*(char *)(local_24 + 0x54) == '\0') && (cVar2 = FUN_005c84d0(local_24 + 0xa4), cVar2 == '\0')
     ) {
    if (*(float *)(local_24 + 0x9c) == 0.0) {
      fVar6 = (float10)FUN_004b1670();
      local_5c = (float)fVar6;
      *(float *)(local_24 + 0x9c) = local_5c + 2.0;
    }
    else {
      fVar6 = (float10)FUN_004b1670();
      local_78 = (float)fVar6;
      if (*(float *)(local_24 + 0x9c) <= local_78 && local_78 != *(float *)(local_24 + 0x9c)) {
        local_30 = FUN_004f6b10();
        local_58 = *(int *)(local_24 + 0x570) / 0x3c;
        local_4c = *(int *)(local_24 + 0x570) % 0x3c;
        local_50 = local_30 / 0x3c;
        local_54 = local_30 % 0x3c;
        iVar4 = FUN_00820da0(*(undefined4 *)(DAT_0094672c + 0x30));
        if ((iVar4 == 0) &&
           ((*(int *)(local_24 + 0x56c) < *(int *)(local_24 + 0x558) ||
            ((*(int *)(local_24 + 0x56c) == *(int *)(local_24 + 0x558) &&
             (local_30 < *(int *)(local_24 + 0x570))))))) {
          local_34 = fopen("emission.bst","wb");
          if (local_34 != (FILE *)0x0) {
            fwrite((void *)(local_24 + 0x558),4,1,local_34);
            fwrite(&local_30,4,1,local_34);
            fclose(local_34);
          }
          local_20 = *(undefined4 *)(local_24 + 0x558);
          iStack_1c = local_50;
          iStack_18 = local_54;
          uStack_14 = *(undefined4 *)(local_24 + 0x56c);
          iStack_10 = local_58;
          iStack_c = local_4c;
          fVar6 = (float10)FUN_004b1670("sammywin.des",&local_20);
          local_7c = (float)fVar6;
          FUN_0045c130(local_7c + 2.0);
        }
        else {
          local_20 = *(undefined4 *)(local_24 + 0x558);
          iStack_1c = local_50;
          iStack_18 = local_54;
          uStack_14 = *(undefined4 *)(local_24 + 0x56c);
          iStack_10 = local_58;
          iStack_c = local_4c;
          fVar6 = (float10)FUN_004b1670("sammylse.des",&local_20);
          local_64 = (float)fVar6;
          FUN_0045c130(local_64 + 2.0);
        }
        *(undefined1 *)(local_24 + 0x54) = 1;
        goto LAB_0065fc6b;
      }
    }
  }
  else {
    if (*(char *)(local_24 + 0x54) != '\0') goto LAB_0065fc6b;
    *(undefined4 *)(local_24 + 0x9c) = 0;
  }
  if (*(int *)(local_24 + 800) == 0) {
    if (*(float *)(local_24 + 0x58) == 0.0) {
      local_44 = 1;
      if (((*(int *)(local_24 + 0x554) != 0) &&
          (*(int *)(local_24 + 0xa4) != *(int *)(local_24 + 0xa8))) &&
         (*(int *)(local_24 + 0xa4) != 0)) {
        for (local_28 = 0; (int)local_28 < *(int *)(local_24 + 0x554); local_28 = local_28 + 1) {
          FUN_005cb820(*(undefined4 *)(local_24 + 0xac + local_28 * 4),
                       *(undefined4 *)(local_24 + 0xa4),1);
        }
      }
      if ((*(int *)(local_24 + 0xa4) != *(int *)(local_24 + 0xa8)) &&
         (*(int *)(local_24 + 0xa4) != 0)) {
        for (local_28 = 0; local_28 < 0x10; local_28 = local_28 + 1) {
          if (((*(int *)(&DAT_008ece88 + local_28 * 0x14) != 0) &&
              (*(int *)(local_24 + 0x2dc + local_28 * 4) != 0)) &&
             (cVar2 = FUN_005c84d0(local_24 + 0x2dc + local_28 * 4), cVar2 != '\0')) {
            FUN_005cb820(*(undefined4 *)(local_24 + 0x2dc + local_28 * 4),
                         *(undefined4 *)(local_24 + 0xa4),1);
          }
        }
      }
      for (local_28 = 0; (int)local_28 < *(int *)(local_24 + 0x554); local_28 = local_28 + 1) {
        if (*(int *)(local_24 + 0x324 + local_28 * 4) == 0) {
          cVar2 = FUN_005c84d0(local_24 + 0xac + local_28 * 4);
          if (cVar2 == '\0') {
            FUN_005c83e0(*(undefined4 *)(local_24 + 0xac + local_28 * 4));
            *(undefined4 *)(local_24 + 0x324 + local_28 * 4) = 1;
            *(int *)(local_24 + 0x558) = *(int *)(local_24 + 0x558) + 1;
            if (*(int *)(local_24 + 0x568) < *(int *)(local_24 + 0x558)) {
              *(undefined4 *)(local_24 + 0x568) = *(undefined4 *)(local_24 + 0x558);
              FUN_005cae60(1,*(undefined4 *)(local_24 + 0x568));
            }
            FUN_005cadd0(1,*(undefined4 *)(local_24 + 0x558));
          }
          else {
            local_44 = 0;
          }
        }
      }
      for (local_28 = 0; local_28 < 0x10; local_28 = local_28 + 1) {
        if (((*(int *)(&DAT_008ece88 + local_28 * 0x14) != 0) &&
            (*(int *)(local_24 + 0x2dc + local_28 * 4) != 0)) &&
           (cVar2 = FUN_005c84d0(local_24 + 0x2dc + local_28 * 4), cVar2 == '\0')) {
          FUN_005c83e0(*(undefined4 *)(local_24 + 0x2dc + local_28 * 4));
          *(undefined4 *)(local_24 + 0x2dc + local_28 * 4) = 0;
          *(int *)(local_24 + 0x558) = *(int *)(local_24 + 0x558) + 1;
          if (*(int *)(local_24 + 0x568) < *(int *)(local_24 + 0x558)) {
            *(undefined4 *)(local_24 + 0x568) = *(undefined4 *)(local_24 + 0x558);
            FUN_005cae60(1,*(undefined4 *)(local_24 + 0x568));
          }
          FUN_005cadd0(1,*(undefined4 *)(local_24 + 0x558));
        }
      }
      if (local_44 != 0) {
        *(int *)(local_24 + 0x55c) = *(int *)(local_24 + 0x55c) + 1;
        if ((8 < *(uint *)(local_24 + 0x55c)) &&
           (*(undefined4 *)(local_24 + 0x55c) = 3, *(int *)(local_24 + 0x560) < 0x14)) {
          *(int *)(local_24 + 0x560) = *(int *)(local_24 + 0x560) + 1;
        }
        if (*(int *)(&DAT_008ecfc4 + *(int *)(local_24 + 0x55c) * 0x1c) == 0) {
          if (*(float *)(&DAT_008ecfc0 + *(int *)(local_24 + 0x55c) * 0x1c) == 0.0) {
            FUN_0065fc80();
          }
          else {
            fVar6 = (float10)FUN_004b1670();
            local_74 = (float)fVar6;
            *(float *)(local_24 + 0x58) =
                 local_74 + *(float *)(&DAT_008ecfc0 + *(int *)(local_24 + 0x55c) * 0x1c);
          }
        }
        else {
          *(undefined4 *)(local_24 + 0x58) = 0x3f800000;
        }
      }
    }
    else if ((*(float *)(local_24 + 0x58) == 1.0) &&
            (*(int *)(&DAT_008ecfc4 + *(int *)(local_24 + 0x55c) * 0x1c) != 0)) {
      if (*(int *)(local_24 + 0x564) != 0) {
        fVar6 = (float10)FUN_004b1670();
        local_6c = (float)fVar6;
        *(float *)(local_24 + 0x58) =
             local_6c + *(float *)(&DAT_008ecfc0 + *(int *)(local_24 + 0x55c) * 0x1c);
      }
    }
    else {
      fVar6 = (float10)FUN_004b1670();
      local_80 = (float)fVar6;
      if (*(float *)(local_24 + 0x58) <= local_80 && local_80 != *(float *)(local_24 + 0x58)) {
        FUN_0065fc80();
        *(undefined4 *)(local_24 + 0x58) = 0;
      }
    }
  }
  else {
    FUN_005cadd0(1,0);
    FUN_005cacb0(1,10);
    FUN_005cae60(1,*(undefined4 *)(local_24 + 0x568));
    FUN_004ff120(0,0x7fffffff,0x7fffffff);
    *(undefined4 *)(local_24 + 0xa8) = *(undefined4 *)(local_24 + 0xa4);
    *(undefined4 *)(local_24 + 0x558) = 0;
    *(undefined4 *)(local_24 + 800) = 0;
    *(undefined4 *)(local_24 + 0x564) = 0;
    *(undefined4 *)(local_24 + 0x55c) = 0;
    *(undefined4 *)(local_24 + 0x58) = 0;
    *(undefined4 *)(local_24 + 0x560) = 1;
    for (local_28 = 0; local_28 < 0x10; local_28 = local_28 + 1) {
      *(undefined4 *)(local_24 + 0x2dc + local_28 * 4) = 0;
      if (*(int *)(local_24 + 0x55c) < *(int *)(&DAT_008ece84 + local_28 * 0x14)) {
        *(undefined4 *)(local_24 + 0x5c + local_28 * 4) = 0;
      }
      else {
        *(undefined4 *)(local_24 + 0x5c + local_28 * 4) = 0x3f800000;
      }
    }
    FUN_0065fc80();
  }
  for (local_28 = 0; local_28 < 0x10; local_28 = local_28 + 1) {
    if (*(float *)(local_24 + 0x5c + local_28 * 4) == 0.0) {
      if (((*(int *)(local_24 + 0x2dc + local_28 * 4) == 0) ||
          (cVar2 = FUN_005c84d0(local_24 + 0x2dc + local_28 * 4), cVar2 == '\0')) &&
         (*(int *)(&DAT_008ece84 + local_28 * 0x14) <= *(int *)(local_24 + 0x55c))) {
        *(undefined4 *)(&DAT_008ece84 + local_28 * 0x14) = 0;
        fVar6 = (float10)FUN_004b1670();
        local_60 = (float)fVar6;
        *(float *)(local_24 + 0x5c + local_28 * 4) =
             local_60 + *(float *)(&DAT_008ece80 + local_28 * 0x14);
      }
    }
    else {
      fVar6 = (float10)FUN_004b1670();
      local_68 = (float)fVar6;
      pfVar1 = (float *)(local_24 + 0x5c + local_28 * 4);
      if (*pfVar1 <= local_68 && local_68 != *pfVar1) {
        *(undefined4 *)(local_24 + 0x5c + local_28 * 4) = 0;
        if (*(int *)(&DAT_008ece88 + local_28 * 0x14) == 0) {
          local_48 = 1;
        }
        else {
          local_48 = 2;
        }
        uVar3 = FUN_005c8250((&PTR_s_aprepaa_008ece90)[local_28 * 5],local_48,
                             (&PTR_s_repair_008ece8c)[local_28 * 5],0,0);
        *(undefined4 *)(local_24 + 0x2dc + local_28 * 4) = uVar3;
        if (*(int *)(&DAT_008ece88 + local_28 * 0x14) != 0) {
          FUN_005cb820(*(undefined4 *)(local_24 + 0x2dc + local_28 * 4),
                       *(undefined4 *)(local_24 + 0xa4),1);
        }
      }
    }
  }
  local_29 = '\0';
LAB_0065fb86:
  if (local_29 == '\0') {
    local_40 = DAT_00917a74;
    local_29 = '\x01';
    FID_conflict_begin(local_3c);
    while( true ) {
      uVar3 = FID_conflict_end(local_88);
      cVar2 = FID_conflict_operator__(uVar3);
      if (cVar2 == '\0') break;
      piVar5 = (int *)FUN_00421ec0();
      local_38 = *piVar5;
      _Size = 5;
      _Buf2 = "npscr";
      iVar4 = (*(code *)**(undefined4 **)(local_38 + 0x18))();
      local_70 = memcmp((void *)(iVar4 + 0x30),_Buf2,_Size);
      if (local_70 == 0) {
        uVar3 = FUN_00477590(local_38);
        FUN_005c83e0(uVar3);
        local_29 = '\0';
        break;
      }
      FUN_0046b260(local_84,0);
    }
    goto LAB_0065fb86;
  }
  if (*(int *)(local_24 + 0xa4) != *(int *)(local_24 + 0xa8)) {
    *(undefined4 *)(local_24 + 0xa8) = *(undefined4 *)(local_24 + 0xa4);
    *(undefined4 *)(local_24 + 0x564) = 1;
  }
LAB_0065fc6b:
  FUN_0083e885();
  return;
}

