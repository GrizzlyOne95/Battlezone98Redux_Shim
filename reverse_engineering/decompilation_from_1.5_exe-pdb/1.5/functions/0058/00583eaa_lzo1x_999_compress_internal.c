/*
 * Entry: 00583eaa
 * Name: lzo1x_999_compress_internal
 * Namespace: Global
 * Signature: int lzo1x_999_compress_internal(uchar * param_1, ulong param_2, uchar * param_3, ulong * param_4, void * param_5, uchar * param_6, ulong param_7, lzo_callback_t * param_8, int param_9, ulong param_10, ulong param_11, ulong param_12, ulong param_13, ulong param_14)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
lzo1x_999_compress_internal
          (uchar *param_1,ulong param_2,uchar *param_3,ulong *param_4,void *param_5,uchar *param_6,
          ulong param_7,lzo_callback_t *param_8,int param_9,ulong param_10,ulong param_11,
          ulong param_12,ulong param_13,ulong param_14)

{
  int iVar1;
  ulong uVar2;
  ulong uVar3;
  uint uVar4;
  lzo1x_999_t *plVar5;
  ulong *unaff_EBX;
  ulong *unaff_ESI;
  lzo1x_999_swd_t *unaff_EDI;
  uchar *puVar6;
  lzo1x_999_t *plVar7;
  undefined4 local_8c;
  uint local_88;
  uint local_84;
  uchar *local_80;
  undefined4 local_7c;
  undefined4 local_78;
  lzo1x_999_t *local_74;
  uchar *local_70;
  uchar *local_6c;
  uchar *local_68;
  uchar *local_64;
  lzo_callback_t *local_60;
  ulong local_5c;
  uchar *local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  int local_44;
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
  uint local_18;
  ulong local_14;
  lzo1x_999_t *local_10;
  lzo1x_999_t *local_c;
  lzo1x_999_t *local_8;
  
  local_10 = (lzo1x_999_t *)param_9;
  if (param_9 < 0) {
    local_10 = (lzo1x_999_t *)0x1;
  }
  if (param_10 == 0) {
    param_10 = 0x20;
  }
  if (param_11 == 0) {
    param_11 = 0x20;
  }
  if (param_12 == 0) {
    param_12 = 0;
  }
  if (param_13 == 0) {
    param_13 = 0x800;
  }
  local_68 = param_1 + param_2;
  local_6c = param_1;
  local_70 = param_1;
  local_c = (lzo1x_999_t *)param_1;
  *(undefined4 **)((int)param_5 + 0xb4) = &local_8c;
  local_64 = param_3;
  local_60 = param_8;
  local_28 = 0;
  local_2c = 0;
  local_30 = 0;
  local_34 = 0;
  local_38 = 0;
  local_1c = 0;
  local_20 = 0;
  local_24 = 0;
  param_1 = param_3;
  param_9 = 0;
  local_3c = 0;
  local_40 = 0;
  local_8c = 1;
  local_78 = 0;
  local_7c = 0;
  local_54 = 0;
  local_58 = (uchar *)0x0;
  local_5c = 0;
  local_48 = 0;
  local_4c = 0;
  local_50 = 0;
  local_44 = 0;
  iVar1 = swd_init((lzo1x_999_swd_t *)param_7,(uchar *)unaff_EDI,(ulong)unaff_ESI);
  if (iVar1 == 0) {
    *(ulong *)((int)param_5 + 0x14) = param_14 & 1;
    if (param_13 != 0) {
      *(ulong *)((int)param_5 + 0xc) = param_13;
    }
    if (param_12 != 0) {
      *(ulong *)((int)param_5 + 0x10) = param_12;
    }
    iVar1 = find_match((lzo1x_999_t *)0x0,(lzo1x_999_swd_t *)0x0,(ulong)unaff_EDI,(ulong)unaff_ESI);
    if (iVar1 == 0) {
      if (local_88 != 0) {
        do {
          puVar6 = local_80;
          local_58 = (uchar *)((int)param_1 - (int)param_3);
          param_2 = local_84;
          if (param_9 == 0) {
            local_c = local_74;
          }
          if ((local_84 < 2) ||
             (((local_84 == 2 &&
               (((((uchar *)0x400 < local_80 || (param_9 == 0)) || (3 < (uint)param_9)) ||
                (param_1 == param_3)))) || ((param_1 == param_3 && (param_9 == 0)))))) {
            param_2 = 0;
LAB_00584023:
            if (param_2 == 0) goto LAB_00584028;
            if (*(int *)((int)param_5 + 0x14) != 0) {
              better_match(unaff_EDI,unaff_ESI,unaff_EBX);
            }
            param_12 = 0;
            if ((local_10 == (lzo1x_999_t *)0x0) || (param_11 <= param_2)) {
              local_14 = 0;
              local_8 = (lzo1x_999_t *)0x0;
            }
            else {
              local_14 = len_of_coded_match((ulong)unaff_EDI,(ulong)unaff_ESI,(ulong)unaff_EBX);
              local_8 = (lzo1x_999_t *)(local_14 - 1);
              if (local_10 <= local_8) {
                local_8 = local_10;
              }
            }
            if (local_8 != (lzo1x_999_t *)0x0) {
              do {
                if (local_88 <= param_2) break;
                uVar2 = param_13;
                if (param_10 <= param_2) {
                  uVar2 = param_13 >> 2;
                }
                *(ulong *)((int)param_5 + 0xc) = uVar2;
                find_match((lzo1x_999_t *)0x1,(lzo1x_999_swd_t *)0x0,(ulong)unaff_EDI,
                           (ulong)unaff_ESI);
                param_12 = param_12 + 1;
                if ((param_2 <= local_84) && ((local_84 != param_2 || (local_80 < puVar6)))) {
                  if (*(int *)((int)param_5 + 0x14) != 0) {
                    better_match(unaff_EDI,unaff_ESI,unaff_EBX);
                  }
                  local_18 = (int)&((lzo1x_999_t *)param_12)->init + param_9;
                  uVar2 = len_of_coded_match((ulong)unaff_EDI,(ulong)unaff_ESI,(ulong)unaff_EBX);
                  if (uVar2 != 0) {
                    if (param_1 == param_3) {
                      uVar3 = 0;
                    }
                    else {
                      uVar3 = len_of_coded_match((ulong)unaff_EDI,(ulong)unaff_ESI,(ulong)unaff_EBX)
                      ;
                    }
                    if ((uint)param_9 < 4) {
                      uVar4 = -(uint)(3 < local_18) & 2;
LAB_0058414f:
                      plVar5 = (lzo1x_999_t *)((int)&((lzo1x_999_t *)param_12)->init + uVar4);
                    }
                    else {
                      plVar5 = (lzo1x_999_t *)param_12;
                      if ((uint)param_9 < 0x13) {
                        uVar4 = (uint)(0x12 < local_18);
                        goto LAB_0058414f;
                      }
                    }
                    iVar1 = (int)plVar5 + (uVar2 - local_14) * 2;
                    if (uVar3 != 0) {
                      iVar1 = iVar1 + (uVar3 - param_12) * 2;
                    }
                    if (iVar1 < 0) {
                      iVar1 = 0;
                    }
                    if (iVar1 + param_2 <= local_84) {
                      local_44 = local_44 + 1;
                      if (uVar3 == 0) {
                        param_9 = (int)&((lzo1x_999_t *)param_12)->init + param_9;
                      }
                      else {
                        plVar5 = local_c;
                        plVar7 = (lzo1x_999_t *)param_12;
                        code_run(local_c,(uchar *)param_12,(uchar *)unaff_EDI,(ulong)unaff_ESI,
                                 (ulong)unaff_EBX);
                        param_9 = 0;
                        param_1 = code_match((lzo1x_999_t *)param_12,puVar6,(ulong)plVar5,
                                             (ulong)plVar7);
                      }
                      goto LAB_005841cb;
                    }
                  }
                }
              } while (param_12 < local_8);
            }
            plVar5 = local_c;
            uVar3 = param_2;
            code_run(local_c,(uchar *)param_2,(uchar *)unaff_EDI,(ulong)unaff_ESI,(ulong)unaff_EBX);
            param_9 = 0;
            uVar2 = param_2;
            param_1 = code_match((lzo1x_999_t *)param_2,puVar6,(ulong)plVar5,uVar3);
            *(ulong *)((int)param_5 + 0xc) = param_13;
            find_match((lzo1x_999_t *)param_2,(lzo1x_999_swd_t *)(param_12 + 1),uVar2,(ulong)puVar6)
            ;
          }
          else {
            if (((local_84 != 3) || (local_80 < (uchar *)0xc01)) || ((uint)param_9 < 4))
            goto LAB_00584023;
LAB_00584028:
            param_9 = param_9 + 1;
            *(ulong *)((int)param_5 + 0xc) = param_13;
            find_match((lzo1x_999_t *)0x1,(lzo1x_999_swd_t *)0x0,(ulong)unaff_EDI,(ulong)unaff_ESI);
          }
LAB_005841cb:
        } while (local_88 != 0);
        if (param_9 != 0) {
          param_1 = STORE_RUN(local_c,(uchar *)param_9,(uchar *)unaff_EDI,(ulong)unaff_ESI);
        }
      }
      *param_1 = '\x11';
      param_1[1] = '\0';
      param_1[2] = '\0';
      local_58 = param_1 + (3 - (int)param_3);
      *param_4 = (ulong)local_58;
      if ((local_60 != (lzo_callback_t *)0x0) &&
         (local_60->nprogress != (_func___cdecl_void_lzo_callback_t_ptr_ulong_ulong_int *)0x0)) {
        (*local_60->nprogress)(local_60,local_5c,(ulong)local_58,0);
      }
      iVar1 = 0;
    }
  }
  return iVar1;
}
