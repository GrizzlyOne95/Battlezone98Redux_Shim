
void FUN_0073c450(undefined4 param_1)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  basic_istream<char,struct_std::char_traits<char>_> local_164 [180];
  basic_istream<char,struct_std::char_traits<char>_> *local_b0;
  int *local_ac;
  basic_istream<char,struct_std::char_traits<char>_> *local_a8;
  basic_istream<char,struct_std::char_traits<char>_> *local_a4;
  basic_istream<char,struct_std::char_traits<char>_> *local_a0;
  basic_istream<char,struct_std::char_traits<char>_> *local_9c;
  basic_istream<char,struct_std::char_traits<char>_> *local_98;
  basic_istream<char,struct_std::char_traits<char>_> *local_94;
  basic_istream<char,struct_std::char_traits<char>_> *local_90;
  int *local_8c;
  basic_istream<char,struct_std::char_traits<char>_> *local_88;
  basic_istream<char,struct_std::char_traits<char>_> *local_84;
  basic_istream<char,struct_std::char_traits<char>_> *local_80;
  undefined1 local_7b;
  undefined1 local_7a;
  undefined1 local_79;
  undefined1 local_78;
  undefined1 local_77;
  undefined1 local_76;
  undefined1 local_75;
  undefined1 local_74;
  undefined1 local_73;
  undefined1 local_72;
  undefined1 local_71;
  undefined1 local_70;
  undefined1 local_6f;
  undefined1 local_6e;
  char local_6d;
  uint local_6c;
  undefined1 local_68 [24];
  undefined1 local_50;
  ulong local_4c;
  undefined1 local_48 [24];
  bool local_30;
  bool local_2f;
  bool local_2e [2];
  uint local_2c;
  uint local_28;
  uint local_24;
  bool local_20 [4];
  uint local_1c;
  bool local_18 [4];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085a9b3;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_004203f0(param_1,3,1);
  local_8 = 0;
  FUN_0073bbd0(uVar2);
  local_8._0_1_ = 1;
  local_6d = '\0';
  std::basic_istream<char,struct_std::char_traits<char>_>::operator>>(local_164,&local_6c);
  local_80 = std::basic_istream<char,struct_std::char_traits<char>_>::get(local_164,&local_6d);
  bVar1 = std::ios_base::operator!((ios_base *)(local_80 + *(int *)(*(int *)local_80 + 4)));
  if ((bVar1) || (local_6d != '*')) {
    local_74 = 0;
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_0073cb40();
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  else {
    local_ac = (int *)FUN_004272a0(local_164,local_68,0x2a);
    bVar1 = std::ios_base::operator!((ios_base *)((int)local_ac + *(int *)(*local_ac + 4)));
    if (bVar1) {
      local_7b = 0;
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_0073cb40();
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
    else {
      iVar3 = std::basic_istream<char,struct_std::char_traits<char>_>::peek(local_164);
      local_6d = (char)iVar3;
      if ((local_6d == 'h') || (local_6d == 's')) {
        std::basic_istream<char,struct_std::char_traits<char>_>::get(local_164,&local_6d);
        local_50 = 0;
        local_4c = 0;
      }
      else {
        local_50 = 1;
        std::basic_istream<char,struct_std::char_traits<char>_>::operator>>(local_164,&local_4c);
      }
      local_6d = '\0';
      local_b0 = std::basic_istream<char,struct_std::char_traits<char>_>::get(local_164,&local_6d);
      bVar1 = std::ios_base::operator!((ios_base *)(local_b0 + *(int *)(*(int *)local_b0 + 4)));
      if ((bVar1) || (local_6d != '*')) {
        local_70 = 0;
        local_8 = (uint)local_8._1_3_ << 8;
        FUN_0073cb40();
        local_8 = 0xffffffff;
        FUN_00417f10();
      }
      else {
        local_8c = (int *)FUN_004272a0(local_164,local_48,0x2a);
        bVar1 = std::ios_base::operator!((ios_base *)((int)local_8c + *(int *)(*local_8c + 4)));
        if (bVar1) {
          local_76 = 0;
          local_8 = (uint)local_8._1_3_ << 8;
          FUN_0073cb40();
          local_8 = 0xffffffff;
          FUN_00417f10();
        }
        else {
          std::basic_istream<char,struct_std::char_traits<char>_>::operator>>(local_164,&local_30);
          local_6d = '\0';
          local_a4 = std::basic_istream<char,struct_std::char_traits<char>_>::get
                               (local_164,&local_6d);
          bVar1 = std::ios_base::operator!((ios_base *)(local_a4 + *(int *)(*(int *)local_a4 + 4)));
          if ((bVar1) || (local_6d != '*')) {
            local_72 = 0;
            local_8 = (uint)local_8._1_3_ << 8;
            FUN_0073cb40();
            local_8 = 0xffffffff;
            FUN_00417f10();
          }
          else {
            std::basic_istream<char,struct_std::char_traits<char>_>::operator>>(local_164,&local_2f)
            ;
            local_6d = '\0';
            local_94 = std::basic_istream<char,struct_std::char_traits<char>_>::get
                                 (local_164,&local_6d);
            bVar1 = std::ios_base::operator!
                              ((ios_base *)(local_94 + *(int *)(*(int *)local_94 + 4)));
            if ((bVar1) || (local_6d != '*')) {
              local_7a = 0;
              local_8 = (uint)local_8._1_3_ << 8;
              FUN_0073cb40();
              local_8 = 0xffffffff;
              FUN_00417f10();
            }
            else {
              std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                        (local_164,local_2e);
              local_6d = '\0';
              local_a8 = std::basic_istream<char,struct_std::char_traits<char>_>::get
                                   (local_164,&local_6d);
              bVar1 = std::ios_base::operator!
                                ((ios_base *)(local_a8 + *(int *)(*(int *)local_a8 + 4)));
              if ((bVar1) || (local_6d != '*')) {
                local_6e = 0;
                local_8 = (uint)local_8._1_3_ << 8;
                FUN_0073cb40();
                local_8 = 0xffffffff;
                FUN_00417f10();
              }
              else {
                std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                          (local_164,&local_2c);
                local_6d = '\0';
                local_9c = std::basic_istream<char,struct_std::char_traits<char>_>::get
                                     (local_164,&local_6d);
                bVar1 = std::ios_base::operator!
                                  ((ios_base *)(local_9c + *(int *)(*(int *)local_9c + 4)));
                if ((bVar1) || (local_6d != '*')) {
                  local_78 = 0;
                  local_8 = (uint)local_8._1_3_ << 8;
                  FUN_0073cb40();
                  local_8 = 0xffffffff;
                  FUN_00417f10();
                }
                else {
                  std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                            (local_164,&local_28);
                  local_6d = '\0';
                  local_84 = std::basic_istream<char,struct_std::char_traits<char>_>::get
                                       (local_164,&local_6d);
                  bVar1 = std::ios_base::operator!
                                    ((ios_base *)(local_84 + *(int *)(*(int *)local_84 + 4)));
                  if ((bVar1) || (local_6d != '*')) {
                    local_6f = 0;
                    local_8 = (uint)local_8._1_3_ << 8;
                    FUN_0073cb40();
                    local_8 = 0xffffffff;
                    FUN_00417f10();
                  }
                  else {
                    std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                              (local_164,&local_24);
                    local_6d = '\0';
                    local_88 = std::basic_istream<char,struct_std::char_traits<char>_>::get
                                         (local_164,&local_6d);
                    bVar1 = std::ios_base::operator!
                                      ((ios_base *)(local_88 + *(int *)(*(int *)local_88 + 4)));
                    if ((bVar1) || (local_6d != '*')) {
                      local_71 = 0;
                      local_8 = (uint)local_8._1_3_ << 8;
                      FUN_0073cb40();
                      local_8 = 0xffffffff;
                      FUN_00417f10();
                    }
                    else {
                      std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                                (local_164,local_20);
                      local_6d = '\0';
                      local_90 = std::basic_istream<char,struct_std::char_traits<char>_>::get
                                           (local_164,&local_6d);
                      bVar1 = std::ios_base::operator!
                                        ((ios_base *)(local_90 + *(int *)(*(int *)local_90 + 4)));
                      if ((bVar1) || (local_6d != '*')) {
                        local_73 = 0;
                        local_8 = (uint)local_8._1_3_ << 8;
                        FUN_0073cb40();
                        local_8 = 0xffffffff;
                        FUN_00417f10();
                      }
                      else {
                        std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                                  (local_164,&local_1c);
                        local_6d = '\0';
                        local_98 = std::basic_istream<char,struct_std::char_traits<char>_>::get
                                             (local_164,&local_6d);
                        bVar1 = std::ios_base::operator!
                                          ((ios_base *)(local_98 + *(int *)(*(int *)local_98 + 4)));
                        if ((bVar1) || (local_6d != '*')) {
                          local_75 = 0;
                          local_8 = (uint)local_8._1_3_ << 8;
                          FUN_0073cb40();
                          local_8 = 0xffffffff;
                          FUN_00417f10();
                        }
                        else {
                          std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                                    (local_164,local_18);
                          local_6d = '\0';
                          local_a0 = std::basic_istream<char,struct_std::char_traits<char>_>::get
                                               (local_164,&local_6d);
                          bVar1 = std::ios_base::operator!
                                            ((ios_base *)(local_a0 + *(int *)(*(int *)local_a0 + 4))
                                            );
                          if ((bVar1) || (local_6d != '*')) {
                            local_77 = 0;
                            local_8 = (uint)local_8._1_3_ << 8;
                            FUN_0073cb40();
                            local_8 = 0xffffffff;
                            FUN_00417f10();
                          }
                          else {
                            FUN_0073cb70(&local_6c);
                            local_79 = 1;
                            local_8 = (uint)local_8._1_3_ << 8;
                            FUN_0073cb40();
                            local_8 = 0xffffffff;
                            FUN_00417f10();
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

