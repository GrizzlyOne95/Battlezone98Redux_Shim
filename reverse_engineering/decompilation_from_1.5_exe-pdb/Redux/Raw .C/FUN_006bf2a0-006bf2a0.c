
void FUN_006bf2a0(void)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  type_info *ptVar5;
  undefined4 *puVar6;
  char *pcVar7;
  undefined4 uVar8;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar9;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar10;
  int *piVar11;
  undefined1 *puVar12;
  TypeDescriptor *pTVar13;
  code *pcVar14;
  _Smanip<__int64> local_cf8 [16];
  _Smanip<__int64> local_ce8 [64];
  _Smanip<__int64> local_ca8 [16];
  _Smanip<__int64> local_c98 [32];
  _Smanip<__int64> local_c78 [48];
  _Smanip<__int64> local_c48 [16];
  _Smanip<__int64> local_c38 [32];
  _Smanip<__int64> local_c18 [16];
  _Smanip<__int64> local_c08 [168];
  undefined4 local_b60;
  undefined1 *local_b58;
  undefined4 local_b50;
  undefined4 local_ae0;
  undefined4 local_a34;
  undefined4 local_a30;
  undefined4 local_a2c;
  undefined4 local_a28;
  undefined1 local_a24;
  undefined4 local_a1c;
  undefined4 local_a18;
  undefined4 local_a14;
  undefined4 local_a10;
  undefined1 local_a04;
  undefined1 local_a03;
  undefined4 local_a00;
  undefined4 local_9f4;
  _Smanip<__int64> local_9ec [16];
  undefined1 local_9dc [12];
  undefined4 local_9d0;
  undefined4 local_9c8;
  undefined4 local_9c4;
  undefined4 local_9c0;
  int local_9bc;
  undefined4 local_9b8;
  undefined4 local_9b4;
  undefined4 local_9b0;
  undefined4 local_9ac;
  char *local_9a8;
  undefined4 local_99c;
  undefined4 local_994;
  int local_988;
  undefined4 local_984;
  undefined4 local_980;
  undefined4 local_97c;
  undefined4 local_978;
  undefined4 local_974;
  char *local_970;
  undefined4 local_96c;
  undefined4 local_968;
  int local_95c;
  undefined4 local_958;
  undefined4 local_954;
  undefined4 local_950;
  undefined4 local_94c;
  undefined4 local_948;
  undefined4 local_944;
  char *local_940;
  undefined4 local_93c;
  undefined4 local_934;
  undefined4 local_930;
  undefined4 local_92c;
  undefined4 local_928;
  undefined4 local_924;
  undefined4 local_920;
  undefined4 local_91c;
  int local_918;
  int local_914;
  undefined4 local_910;
  int local_908;
  undefined4 local_900;
  undefined4 local_8f8;
  undefined4 local_8ec;
  undefined4 local_8e4;
  undefined4 local_8e0;
  undefined4 local_8dc;
  undefined4 local_8cc;
  undefined4 local_8c8;
  undefined4 local_8c4;
  undefined4 local_8c0;
  char local_8bb;
  undefined1 local_8ba;
  char local_8b9;
  undefined4 local_8b8;
  undefined4 local_8b4;
  uint local_8b0;
  undefined1 local_8ab;
  undefined1 local_8aa;
  char local_8a9;
  undefined4 local_8a8;
  undefined1 local_8a1;
  undefined4 local_8a0;
  int local_89c;
  char local_895;
  undefined4 local_894;
  undefined1 local_890 [72];
  undefined1 local_848 [1132];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_3dc [48];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_3ac [600];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_154 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_13c [88];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_e4 [48];
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined1 local_7c;
  undefined1 local_7b;
  undefined1 local_50;
  SchedulingNode local_4c [56];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00851beb;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8b0 = 0;
  local_8 = 1;
  local_14 = uVar3;
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    local_8 = local_8 & 0xffffff00;
    FUN_006c9420();
    local_8 = 0xffffffff;
    FUN_006ca8c0();
    goto LAB_006c2db0;
  }
  FUN_00421ec0();
  iVar4 = FUN_006cc050();
  if (iVar4 == 1) {
    FUN_006cc3b0();
    local_8._0_1_ = 2;
    FUN_006bdff0();
    local_8._0_1_ = 3;
    FUN_00421ec0();
    local_8cc = FUN_006cc070();
    cVar1 = FUN_007fb090();
    if (cVar1 == '\0') {
      if (*(int *)(local_89c + 4) < 3) {
        FUN_0081e0c0();
        basic_string<>();
        local_8._0_1_ = 4;
        FUN_00421ec0();
        FUN_006dae30();
        local_8._0_1_ = 3;
        ~basic_string<>();
        std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
                  ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(local_89c + 0x2e0))
        ;
      }
    }
    else {
      pTVar13 = &boost::container::
                 map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                 ::RTTI_Type_Descriptor;
      ptVar5 = (type_info *)FUN_006cc480();
      bVar2 = type_info::operator!=(ptVar5,(type_info *)pTVar13);
      if (bVar2) {
        if (*(int *)(local_89c + 4) < 3) {
          FUN_0081e0c0();
          basic_string<>();
          local_8._0_1_ = 5;
          FUN_00421ec0();
          FUN_006dae30();
          local_8._0_1_ = 3;
          ~basic_string<>();
          std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
                    ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)
                     (local_89c + 0x2e0));
        }
      }
      else {
        local_8a0 = FUN_006db8f0();
        basic_string<>();
        local_8._0_1_ = 6;
        basic_string<>();
        local_8._0_1_ = 7;
        FUN_006cc1b0();
        local_8._0_1_ = 6;
        ~basic_string<>();
        local_895 = '\0';
        FUN_006cc180();
        cVar1 = operator!=<>();
        if (cVar1 == '\0') {
LAB_006bf560:
          if (*(int *)(local_89c + 4) < 3) {
            FUN_0081e0c0();
            basic_string<>();
            local_8._0_1_ = 8;
            FUN_00421ec0();
            FUN_006dae30();
            local_8._0_1_ = 6;
            ~basic_string<>();
            std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
                      ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)
                       (local_89c + 0x2e0));
          }
          local_895 = '\x01';
        }
        else {
          pTVar13 = &std::
                     basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                     RTTI_Type_Descriptor;
          FUN_006cc330();
          ptVar5 = (type_info *)FUN_006cc480();
          bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
          if (!bVar2) goto LAB_006bf560;
          FUN_006cc330();
          FUN_006db910();
          FID_conflict_operator_();
        }
        if (local_895 != '\0') goto LAB_006c2d07;
        cVar1 = FUN_00427270();
        if (cVar1 == '\0') {
          if (*(int *)(local_89c + 4) < 3) {
            FUN_0041f870();
            FUN_007d6a70();
            FUN_0081e0c0();
            basic_string<>();
            local_8._0_1_ = 0xf;
            FUN_00421ec0();
            FUN_006dae30();
            local_8._0_1_ = 6;
            ~basic_string<>();
            std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
                      ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)
                       (local_89c + 0x2e0));
            local_8._0_1_ = 3;
            ~basic_string<>();
            local_8._0_1_ = 2;
            FUN_00430320();
            local_8._0_1_ = 1;
            Concurrency::details::SchedulingNode::~SchedulingNode(local_4c);
            local_8 = (uint)local_8._1_3_ << 8;
            FUN_006c9420();
            local_8 = 0xffffffff;
            FUN_006ca8c0();
            goto LAB_006c2db0;
          }
          pcVar14 = FUN_004bc8c0;
          FUN_0041f870();
          pbVar10 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
          std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar10,pcVar14);
          if (2 < DAT_008eda28) {
            pcVar14 = FUN_004bc8c0;
            FUN_0041f870();
            FUN_0081e820();
            uVar8 = FUN_0081e660();
            FUN_004bc590(uVar8);
            pbVar10 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
            std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar10,pcVar14);
          }
          cVar1 = FUN_00427270();
          if (cVar1 == '\0') {
            cVar1 = FUN_00427270();
            if (cVar1 == '\0') {
              cVar1 = FUN_00427270();
              if (cVar1 == '\0') {
                cVar1 = FUN_00427270();
                if (cVar1 == '\0') {
                  cVar1 = FUN_00427270();
                  if (cVar1 == '\0') {
                    cVar1 = FUN_00427270();
                    if (cVar1 == '\0') {
                      cVar1 = FUN_00427270();
                      if (cVar1 == '\0') {
                        cVar1 = FUN_00427270();
                        if ((cVar1 == '\0') && (cVar1 = FUN_00427270(), cVar1 == '\0')) {
                          cVar1 = FUN_00427270();
                          if ((cVar1 == '\0') &&
                             ((cVar1 = FUN_00427270(), cVar1 == '\0' &&
                              (cVar1 = FUN_00427270(), cVar1 == '\0')))) {
                            cVar1 = FUN_00427270();
                            if (cVar1 != '\0') {
                              basic_string<>();
                              local_8._0_1_ = 0x45;
                              puVar6 = (undefined4 *)FUN_006cc1b0();
                              local_894 = *puVar6;
                              local_8._0_1_ = 6;
                              ~basic_string<>();
                              FUN_006cc330();
                              local_9d0 = FUN_006db8f0();
                              basic_string<>();
                              local_8._0_1_ = 0x46;
                              FUN_006cc1b0();
                              FUN_006cc330();
                              local_910 = FUN_006db8f0();
                              local_8._0_1_ = 6;
                              ~basic_string<>();
                              basic_string<>();
                              local_8._0_1_ = 0x47;
                              FUN_006cc1b0();
                              FUN_006cc330();
                              puVar6 = (undefined4 *)FUN_006db950();
                              local_974 = *puVar6;
                              local_8._0_1_ = 6;
                              ~basic_string<>();
                              basic_string<>();
                              local_8._0_1_ = 0x48;
                              FUN_006cc1b0();
                              FUN_006cc330();
                              puVar6 = (undefined4 *)FUN_006db950();
                              local_9c4 = *puVar6;
                              local_8._0_1_ = 6;
                              ~basic_string<>();
                              FUN_007d6a70();
                              basic_string<>();
                              local_8._0_1_ = 0x49;
                              FUN_006cc1b0();
                              FUN_006cc330();
                              local_92c = FUN_006db970();
                              local_8._0_1_ = 6;
                              ~basic_string<>();
                              FUN_006cc6f0();
                              FUN_006cc720();
                              vector<>();
                              local_8._0_1_ = 0x4a;
                              while (cVar1 = FUN_006cc7a0(), cVar1 != '\0') {
                                local_b50 = get();
                                get();
                                FUN_006db910();
                                FUN_006cae50();
                                FUN_006cc780();
                              }
                              local_b58 = &stack0xfffff2f8;
                              local_b60 = FUN_00489f50(local_9dc);
                              local_8._0_1_ = 0x4b;
                              local_968 = local_b60;
                              FUN_00764790();
                              local_8._0_1_ = 0x4a;
                              FUN_0076dd40();
                              local_8._0_1_ = 6;
                              FUN_0048a040();
                              goto LAB_006c2d07;
                            }
                            cVar1 = FUN_00427270();
                            if (cVar1 == '\0') {
                              cVar1 = FUN_00427270();
                              if (cVar1 != '\0') {
                                FUN_0041f870();
                                FUN_007d6b70();
                                goto LAB_006c2d07;
                              }
                              cVar1 = FUN_00427270();
                              if (cVar1 == '\0') {
                                cVar1 = FUN_00427270();
                                if (cVar1 == '\0') {
                                  cVar1 = FUN_00427270();
                                  if (cVar1 == '\0') {
                                    cVar1 = FUN_00427270();
                                    if (cVar1 == '\0') {
                                      FUN_0041f870();
                                      FUN_0041f870();
                                      FUN_007d6b70();
                                    }
                                    else {
                                      local_988 = FUN_00822e60();
                                      *(undefined1 *)(local_89c + 0x2d8) = 1;
                                      iVar4 = rand();
                                      *(int *)(local_89c + 0x2dc) = local_988 + 0x1e + iVar4 % 0x1e;
                                    }
                                  }
                                  else {
                                    basic_string<>();
                                    local_8._0_1_ = 0x57;
                                    puVar6 = (undefined4 *)FUN_006cc1b0();
                                    local_894 = *puVar6;
                                    local_8._0_1_ = 6;
                                    ~basic_string<>();
                                    FUN_006cc180();
                                    cVar1 = operator!=<>();
                                    if (cVar1 != '\0') {
                                      local_9bc = FUN_006cc330();
                                      local_9bc = local_9bc + 0x18;
                                      local_9ac = FUN_007d7550(local_890);
                                      local_8._0_1_ = 0x58;
                                      local_984 = local_9ac;
                                      FUN_0041f870();
                                      FUN_007d6a70();
                                      local_8._0_1_ = 6;
                                      ~basic_string<>();
                                      pTVar13 = &boost::container::
                                                 map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                                                 ::RTTI_Type_Descriptor;
                                      FUN_006cc330();
                                      ptVar5 = (type_info *)FUN_006cc480();
                                      bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                                      if (bVar2) {
                                        FUN_006cc330();
                                        local_91c = FUN_006db8f0();
                                        FUN_006cc150();
                                        FUN_006cc180();
                                        while (cVar1 = operator!=<>(), cVar1 != '\0') {
                                          FUN_006cc270();
                                        }
                                      }
                                      else {
                                        pTVar13 = &boost::container::
                                                                                                      
                                                  vector<class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::detail::vari...etail::variant::void_,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_>_>_>
                                                  ::RTTI_Type_Descriptor;
                                        FUN_006cc330();
                                        ptVar5 = (type_info *)FUN_006cc480();
                                        bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                                        if (bVar2) {
                                          FUN_006cc330();
                                          local_958 = FUN_006db970();
                                          FUN_006cc6f0();
                                          FUN_006cc720();
                                          local_914 = 0;
                                          while (cVar1 = FUN_006cc7a0(), cVar1 != '\0') {
                                            local_994 = get();
                                            local_9b4 = FUN_007d7550(local_848);
                                            local_8._0_1_ = 0x59;
                                            local_99c = local_9b4;
                                            FUN_0041f870();
                                            FUN_007d6a70();
                                            local_8._0_1_ = 6;
                                            ~basic_string<>();
                                            local_914 = local_914 + 1;
                                            FUN_006cc780();
                                          }
                                        }
                                        else {
                                          pTVar13 = &std::
                                                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                                  ::RTTI_Type_Descriptor;
                                          FUN_006cc330();
                                          ptVar5 = (type_info *)FUN_006cc480();
                                          bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13)
                                          ;
                                          if (bVar2) {
                                            FUN_006cc330();
                                            local_96c = FUN_006db910();
                                            FUN_0041f870();
                                            FUN_007d6a70();
                                          }
                                          else {
                                            pTVar13 = &._N::RTTI_Type_Descriptor;
                                            FUN_006cc330();
                                            ptVar5 = (type_info *)FUN_006cc480();
                                            bVar2 = type_info::operator==
                                                              (ptVar5,(type_info *)pTVar13);
                                            if (bVar2) {
                                              FUN_006cc330();
                                              local_970 = (char *)FUN_006db930();
                                              if (*local_970 == '\0') {
                                                local_940 = "false";
                                              }
                                              else {
                                                local_940 = "true";
                                              }
                                              FUN_007d6a70();
                                            }
                                            else {
                                              pTVar13 = &.N::RTTI_Type_Descriptor;
                                              FUN_006cc330();
                                              ptVar5 = (type_info *)FUN_006cc480();
                                              bVar2 = type_info::operator==
                                                                (ptVar5,(type_info *)pTVar13);
                                              if (bVar2) {
                                                FUN_006cc330();
                                                local_978 = FUN_006db990();
                                                FUN_007d6a70();
                                              }
                                              else {
                                                pTVar13 = &.J::RTTI_Type_Descriptor;
                                                FUN_006cc330();
                                                ptVar5 = (type_info *)FUN_006cc480();
                                                bVar2 = type_info::operator==
                                                                  (ptVar5,(type_info *)pTVar13);
                                                if (bVar2) {
                                                  FUN_006cc330();
                                                  local_980 = FUN_006db950();
                                                  FUN_007d6a70();
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                                else {
                                  basic_string<>();
                                  local_8._0_1_ = 0x53;
                                  puVar6 = (undefined4 *)FUN_006cc1b0();
                                  local_894 = *puVar6;
                                  local_8._0_1_ = 6;
                                  ~basic_string<>();
                                  FUN_006cc180();
                                  cVar1 = operator!=<>();
                                  if (cVar1 != '\0') {
                                    pTVar13 = &boost::container::
                                               map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                                               ::RTTI_Type_Descriptor;
                                    FUN_006cc330();
                                    ptVar5 = (type_info *)FUN_006cc480();
                                    bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                                    if (bVar2) {
                                      FUN_006cc330();
                                      local_8c4 = FUN_006db8f0();
                                      local_8a1 = 0;
                                      basic_string<>();
                                      local_8._0_1_ = 0x54;
                                      puVar6 = (undefined4 *)FUN_006cc1b0();
                                      local_894 = *puVar6;
                                      local_8 = CONCAT31(local_8._1_3_,6);
                                      ~basic_string<>();
                                      FUN_006cc180();
                                      cVar1 = operator!=<>();
                                      if (cVar1 == '\0') {
                                        local_895 = '\x01';
                                      }
                                      else {
                                        pTVar13 = &._N::RTTI_Type_Descriptor;
                                        FUN_006cc330();
                                        ptVar5 = (type_info *)FUN_006cc480();
                                        bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                                        if (bVar2) {
                                          FUN_006cc330();
                                          puVar12 = (undefined1 *)FUN_006db930();
                                          local_8a1 = *puVar12;
                                        }
                                        else {
                                          local_895 = '\x01';
                                        }
                                      }
                                      local_930 = 0;
                                      basic_string<>();
                                      local_8._0_1_ = 0x55;
                                      puVar6 = (undefined4 *)FUN_006cc1b0();
                                      local_894 = *puVar6;
                                      local_8 = CONCAT31(local_8._1_3_,6);
                                      ~basic_string<>();
                                      FUN_006cc180();
                                      cVar1 = operator==<>();
                                      if (cVar1 == '\0') {
                                        pTVar13 = &.J::RTTI_Type_Descriptor;
                                        FUN_006cc330();
                                        ptVar5 = (type_info *)FUN_006cc480();
                                        bVar2 = type_info::operator!=(ptVar5,(type_info *)pTVar13);
                                        if (bVar2) goto LAB_006c26c8;
                                        FUN_006cc330();
                                        puVar6 = (undefined4 *)FUN_006db950();
                                        local_930 = *puVar6;
                                      }
                                      else {
LAB_006c26c8:
                                        local_895 = '\x01';
                                      }
                                      basic_string<>();
                                      local_8._0_1_ = 0x56;
                                      puVar6 = (undefined4 *)FUN_006cc1b0();
                                      local_894 = *puVar6;
                                      local_8._0_1_ = 6;
                                      ~basic_string<>();
                                      FUN_006cc180();
                                      cVar1 = operator==<>();
                                      if (cVar1 == '\0') {
                                        pTVar13 = &std::
                                                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                                  ::RTTI_Type_Descriptor;
                                        FUN_006cc330();
                                        ptVar5 = (type_info *)FUN_006cc480();
                                        bVar2 = type_info::operator!=(ptVar5,(type_info *)pTVar13);
                                        if (bVar2) goto LAB_006c2786;
                                      }
                                      else {
LAB_006c2786:
                                        local_895 = '\x01';
                                      }
                                      if (local_895 == '\0') {
                                        FUN_006cb4c0();
                                        FUN_006cb4e0();
                                        FUN_006cc330();
                                        FUN_006db910();
                                        FUN_0073a7a0();
                                        if (*(int *)(local_89c + 0xc3c) != 0) {
                                          FUN_0075f370();
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                              else {
                                basic_string<>();
                                local_8._0_1_ = 0x50;
                                puVar6 = (undefined4 *)FUN_006cc1b0();
                                local_894 = *puVar6;
                                local_8._0_1_ = 6;
                                ~basic_string<>();
                                FUN_006cc180();
                                cVar1 = operator!=<>();
                                if (cVar1 != '\0') {
                                  pTVar13 = &boost::container::
                                             map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                                             ::RTTI_Type_Descriptor;
                                  FUN_006cc330();
                                  ptVar5 = (type_info *)FUN_006cc480();
                                  bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                                  if (bVar2) {
                                    FUN_006cc330();
                                    local_8e4 = FUN_006db8f0();
                                    local_8aa = 0;
                                    basic_string<>();
                                    local_8._0_1_ = 0x51;
                                    puVar6 = (undefined4 *)FUN_006cc1b0();
                                    local_894 = *puVar6;
                                    local_8 = CONCAT31(local_8._1_3_,6);
                                    ~basic_string<>();
                                    FUN_006cc180();
                                    cVar1 = operator==<>();
                                    if (cVar1 != '\0') {
                                      pTVar13 = &._N::RTTI_Type_Descriptor;
                                      FUN_006cc330();
                                      ptVar5 = (type_info *)FUN_006cc480();
                                      bVar2 = type_info::operator!=(ptVar5,(type_info *)pTVar13);
                                      if (bVar2) {
                                        FUN_006cc330();
                                        puVar12 = (undefined1 *)FUN_006db930();
                                        local_8aa = *puVar12;
                                      }
                                      else {
                                        local_895 = '\x01';
                                      }
                                    }
                                    basic_string<>();
                                    local_8._0_1_ = 0x52;
                                    puVar6 = (undefined4 *)FUN_006cc1b0();
                                    local_894 = *puVar6;
                                    local_8._0_1_ = 6;
                                    ~basic_string<>();
                                    FUN_006cc180();
                                    cVar1 = operator==<>();
                                    if (cVar1 == '\0') {
                                      pTVar13 = &std::
                                                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                                 ::RTTI_Type_Descriptor;
                                      FUN_006cc330();
                                      ptVar5 = (type_info *)FUN_006cc480();
                                      bVar2 = type_info::operator!=(ptVar5,(type_info *)pTVar13);
                                      if (bVar2) goto LAB_006c241a;
                                    }
                                    else {
LAB_006c241a:
                                      local_895 = '\x01';
                                    }
                                    if (local_895 == '\0') {
                                      FUN_006cc330();
                                      FUN_006db910();
                                      FUN_0073a7a0();
                                      if (*(int *)(local_89c + 0xc3c) != 0) {
                                        FUN_0075eea0();
                                      }
                                    }
                                  }
                                }
                              }
                            }
                            else {
                              basic_string<>();
                              local_8._0_1_ = 0x4c;
                              puVar6 = (undefined4 *)FUN_006cc1b0();
                              local_894 = *puVar6;
                              local_8._0_1_ = 6;
                              ~basic_string<>();
                              FUN_006cc180();
                              cVar1 = operator!=<>();
                              if (cVar1 != '\0') {
                                pTVar13 = &boost::container::
                                           map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                                           ::RTTI_Type_Descriptor;
                                FUN_006cc330();
                                ptVar5 = (type_info *)FUN_006cc480();
                                bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                                if (bVar2) {
                                  FUN_006cc330();
                                  local_8dc = FUN_006db8f0();
                                  basic_string<>();
                                  local_8._0_1_ = 0x4d;
                                  puVar6 = (undefined4 *)FUN_006cc1b0();
                                  local_894 = *puVar6;
                                  local_8._0_1_ = 6;
                                  ~basic_string<>();
                                  FUN_006cc180();
                                  cVar1 = operator==<>();
                                  if (cVar1 == '\0') {
                                    pTVar13 = &.J::RTTI_Type_Descriptor;
                                    FUN_006cc330();
                                    ptVar5 = (type_info *)FUN_006cc480();
                                    bVar2 = type_info::operator!=(ptVar5,(type_info *)pTVar13);
                                    if (bVar2) goto LAB_006c207f;
                                  }
                                  else {
LAB_006c207f:
                                    local_895 = '\x01';
                                  }
                                  if (local_895 == '\0') {
                                    FUN_006cc330();
                                    piVar11 = (int *)FUN_006db950();
                                    std::_Smanip<__int64>::_Smanip<__int64>
                                              (local_c98,(_func_void_ios_base_ptr___int64 *)0x3,
                                               CONCAT44(uVar3,*piVar11 >> 0x1f));
                                    basic_string<>();
                                    local_8._0_1_ = 0x4e;
                                    FUN_006cc1b0();
                                    FUN_006cc330();
                                    puVar12 = (undefined1 *)FUN_006db930();
                                    local_8ab = *puVar12;
                                    local_8._0_1_ = 6;
                                    ~basic_string<>();
                                    basic_string<>();
                                    local_8._0_1_ = 0x4f;
                                    FUN_006cc1b0();
                                    FUN_006cc330();
                                    piVar11 = (int *)FUN_006db950();
                                    local_918 = *piVar11;
                                    local_8._0_1_ = 6;
                                    ~basic_string<>();
                                    if (local_918 == 5) {
                                      local_918 = 0;
                                      local_8ab = 1;
                                    }
                                    FUN_0074c7d0();
                                  }
                                }
                              }
                            }
                          }
                          else {
                            basic_string<>();
                            local_8._0_1_ = 0x43;
                            puVar6 = (undefined4 *)FUN_006cc1b0();
                            local_894 = *puVar6;
                            local_8._0_1_ = 6;
                            ~basic_string<>();
                            FUN_006cc180();
                            cVar1 = operator!=<>();
                            if (cVar1 != '\0') {
                              pTVar13 = &boost::container::
                                         map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                                         ::RTTI_Type_Descriptor;
                              FUN_006cc330();
                              ptVar5 = (type_info *)FUN_006cc480();
                              bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                              if (bVar2) {
                                FUN_006cc330();
                                local_950 = FUN_006db8f0();
                                basic_string<>();
                                local_8._0_1_ = 0x44;
                                puVar6 = (undefined4 *)FUN_006cc1b0();
                                local_894 = *puVar6;
                                local_8._0_1_ = 6;
                                ~basic_string<>();
                                FUN_006cc180();
                                cVar1 = operator==<>();
                                if (cVar1 == '\0') {
                                  pTVar13 = &.J::RTTI_Type_Descriptor;
                                  FUN_006cc330();
                                  ptVar5 = (type_info *)FUN_006cc480();
                                  bVar2 = type_info::operator!=(ptVar5,(type_info *)pTVar13);
                                  if (bVar2) goto LAB_006c1b55;
                                }
                                else {
LAB_006c1b55:
                                  local_895 = '\x01';
                                }
                                if (local_895 == '\0') {
                                  FUN_006cc330();
                                  piVar11 = (int *)FUN_006db950();
                                  std::_Smanip<__int64>::_Smanip<__int64>
                                            (local_9ec,(_func_void_ios_base_ptr___int64 *)0x3,
                                             CONCAT44(uVar3,*piVar11 >> 0x1f));
                                  cVar1 = FUN_00427270();
                                  if (cVar1 == '\0') {
                                    cVar1 = FUN_00427270();
                                    if (cVar1 == '\0') {
                                      cVar1 = FUN_00427270();
                                      if (cVar1 != '\0') {
                                        FUN_0074c9b0();
                                      }
                                    }
                                    else {
                                      FUN_0074c6c0();
                                    }
                                  }
                                  else {
                                    FUN_00578950();
                                    FUN_006be370();
                                    FUN_0074d060();
                                  }
                                }
                              }
                            }
                          }
                        }
                        else {
                          cVar1 = FUN_00427270();
                          if (cVar1 != '\0') {
                            *(undefined1 *)(local_89c + 9) = 1;
                            FUN_00429ce0();
                          }
                          basic_string<>();
                          local_8._0_1_ = 0x25;
                          puVar6 = (undefined4 *)FUN_006cc1b0();
                          local_894 = *puVar6;
                          local_8._0_1_ = 6;
                          ~basic_string<>();
                          FUN_006cc180();
                          cVar1 = operator!=<>();
                          if (cVar1 != '\0') {
                            pTVar13 = &boost::container::
                                       map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                                       ::RTTI_Type_Descriptor;
                            FUN_006cc330();
                            ptVar5 = (type_info *)FUN_006cc480();
                            bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                            if (bVar2) {
                              FUN_006cc330();
                              local_928 = FUN_006db8f0();
                              basic_string<>();
                              local_8._0_1_ = 0x26;
                              puVar6 = (undefined4 *)FUN_006cc1b0();
                              local_894 = *puVar6;
                              local_8._0_1_ = 6;
                              ~basic_string<>();
                              FUN_006cc180();
                              cVar1 = operator!=<>();
                              if (cVar1 != '\0') {
                                pTVar13 = &boost::container::
                                           map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                                           ::RTTI_Type_Descriptor;
                                FUN_006cc330();
                                ptVar5 = (type_info *)FUN_006cc480();
                                bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                                if (bVar2) {
                                  FUN_006cc590();
                                  local_8 = CONCAT31(local_8._1_3_,0x27);
                                  FUN_006cc330();
                                  local_93c = FUN_006db8f0();
                                  FUN_006cc150();
                                  FUN_006cc180();
                                  while (cVar1 = operator!=<>(), cVar1 != '\0') {
                                    pTVar13 = &boost::container::
                                               map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                                               ::RTTI_Type_Descriptor;
                                    FUN_006cc330();
                                    ptVar5 = (type_info *)FUN_006cc480();
                                    bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                                    if (bVar2) {
                                      FUN_006cc330();
                                      local_8a8 = FUN_006db8f0();
                                      FUN_006c2df0();
                                      local_8._0_1_ = 0x28;
                                      basic_string<>();
                                      local_8._0_1_ = 0x29;
                                      FUN_006cc1b0();
                                      FUN_006cc330();
                                      piVar11 = (int *)FUN_006db950();
                                      puVar6 = (undefined4 *)
                                               std::_Smanip<__int64>::_Smanip<__int64>
                                                         (local_cf8,
                                                          (_func_void_ios_base_ptr___int64 *)0x3,
                                                          CONCAT44(uVar3,*piVar11 >> 0x1f));
                                      local_a34 = *puVar6;
                                      local_a30 = puVar6[1];
                                      local_a2c = puVar6[2];
                                      local_a28 = puVar6[3];
                                      local_8._0_1_ = 0x28;
                                      ~basic_string<>();
                                      basic_string<>();
                                      local_8._0_1_ = 0x2a;
                                      FUN_006cc1b0();
                                      FUN_006cc330();
                                      puVar6 = (undefined4 *)FUN_006db950();
                                      local_9f4 = *puVar6;
                                      local_8._0_1_ = 0x28;
                                      ~basic_string<>();
                                      basic_string<>();
                                      local_8._0_1_ = 0x2b;
                                      FUN_006cc1b0();
                                      FUN_006cc330();
                                      puVar6 = (undefined4 *)FUN_006db950();
                                      local_a00 = *puVar6;
                                      local_8._0_1_ = 0x28;
                                      ~basic_string<>();
                                      basic_string<>();
                                      local_8._0_1_ = 0x2c;
                                      FUN_006cc1b0();
                                      FUN_006cc330();
                                      puVar12 = (undefined1 *)FUN_006db930();
                                      local_a04 = *puVar12;
                                      local_8._0_1_ = 0x28;
                                      ~basic_string<>();
                                      basic_string<>();
                                      local_8._0_1_ = 0x2d;
                                      FUN_006cc1b0();
                                      FUN_006cc330();
                                      puVar12 = (undefined1 *)FUN_006db930();
                                      local_a03 = *puVar12;
                                      local_8._0_1_ = 0x28;
                                      ~basic_string<>();
                                      basic_string<>();
                                      local_8._0_1_ = 0x2e;
                                      FUN_006cc1b0();
                                      FUN_006cc330();
                                      local_944 = FUN_006db8f0();
                                      local_8 = CONCAT31(local_8._1_3_,0x28);
                                      ~basic_string<>();
                                      FUN_006cc150();
                                      FUN_006cc180();
                                      while (cVar1 = operator!=<>(), cVar1 != '\0') {
                                        pbVar9 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                                  *)FUN_006cc330();
                                        std::
                                        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                        ::
                                        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                                  (local_154,pbVar9);
                                        local_8._0_1_ = 0x2f;
                                        FUN_006cc330();
                                        pbVar9 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                                  *)FUN_006db910();
                                        std::
                                        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                        ::
                                        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                                  (local_13c,pbVar9);
                                        local_8._0_1_ = 0x30;
                                        FUN_006ca810();
                                        FID_conflict_operator_();
                                        FUN_006cc270();
                                        local_8._0_1_ = 0x2f;
                                        ~basic_string<>();
                                        local_8 = CONCAT31(local_8._1_3_,0x28);
                                        ~basic_string<>();
                                      }
                                      basic_string<>();
                                      local_8._0_1_ = 0x31;
                                      FUN_006cc1b0();
                                      FUN_006cc330();
                                      FUN_006db910();
                                      puVar6 = (undefined4 *)FUN_0073a7a0();
                                      local_a1c = *puVar6;
                                      local_a18 = puVar6[1];
                                      local_a14 = puVar6[2];
                                      local_a10 = puVar6[3];
                                      local_8._0_1_ = 0x28;
                                      ~basic_string<>();
                                      basic_string<>();
                                      local_8._0_1_ = 0x32;
                                      FUN_006cc1b0();
                                      FUN_006cc330();
                                      puVar12 = (undefined1 *)FUN_006db930();
                                      local_a24 = *puVar12;
                                      local_8._0_1_ = 0x28;
                                      ~basic_string<>();
                                      basic_string<>();
                                      local_8._0_1_ = 0x33;
                                      puVar6 = (undefined4 *)FUN_006cc1b0();
                                      local_894 = *puVar6;
                                      local_8 = CONCAT31(local_8._1_3_,0x28);
                                      ~basic_string<>();
                                      FUN_006cc330();
                                      local_94c = FUN_006db8f0();
                                      puVar6 = (undefined4 *)FUN_006cc150();
                                      local_8b8 = *puVar6;
                                      puVar6 = (undefined4 *)FUN_006cc180();
                                      local_900 = *puVar6;
                                      local_908 = 0;
                                      while (cVar1 = operator!=<>(), cVar1 != '\0') {
                                        pTVar13 = &boost::container::
                                                                                                      
                                                  map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                                                  ::RTTI_Type_Descriptor;
                                        FUN_006cc330();
                                        ptVar5 = (type_info *)FUN_006cc480();
                                        bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                                        if (bVar2) {
                                          FUN_006cc330();
                                          local_8b4 = FUN_006db8f0();
                                          FUN_006c2e90();
                                          local_8._0_1_ = 0x34;
                                          basic_string<>();
                                          local_8._0_1_ = 0x35;
                                          FUN_006cc1b0();
                                          FUN_006cc330();
                                          FUN_006db910();
                                          puVar6 = (undefined4 *)FUN_0073a7a0();
                                          local_b4 = *puVar6;
                                          local_b0 = puVar6[1];
                                          local_ac = puVar6[2];
                                          local_a8 = puVar6[3];
                                          local_8._0_1_ = 0x34;
                                          ~basic_string<>();
                                          basic_string<>();
                                          local_8._0_1_ = 0x36;
                                          FUN_006cc1b0();
                                          FUN_006cc330();
                                          FUN_006db910();
                                          FID_conflict_operator_();
                                          local_8._0_1_ = 0x34;
                                          ~basic_string<>();
                                          basic_string<>();
                                          local_8._0_1_ = 0x37;
                                          FUN_006cc1b0();
                                          FUN_006cc330();
                                          piVar11 = (int *)FUN_006db950();
                                          puVar6 = (undefined4 *)
                                                   std::_Smanip<__int64>::_Smanip<__int64>
                                                             (local_ce8,
                                                              (_func_void_ios_base_ptr___int64 *)0x3
                                                              ,CONCAT44(uVar3,*piVar11 >> 0x1f));
                                          local_a4 = *puVar6;
                                          local_a0 = puVar6[1];
                                          local_9c = puVar6[2];
                                          local_98 = puVar6[3];
                                          local_8._0_1_ = 0x34;
                                          ~basic_string<>();
                                          basic_string<>();
                                          local_8._0_1_ = 0x38;
                                          FUN_006cc1b0();
                                          FUN_006cc330();
                                          puVar12 = (undefined1 *)FUN_006db930();
                                          local_7c = *puVar12;
                                          local_8._0_1_ = 0x34;
                                          ~basic_string<>();
                                          basic_string<>();
                                          local_8._0_1_ = 0x39;
                                          FUN_006cc1b0();
                                          FUN_006cc330();
                                          puVar12 = (undefined1 *)FUN_006db930();
                                          local_7b = *puVar12;
                                          local_8._0_1_ = 0x34;
                                          ~basic_string<>();
                                          basic_string<>();
                                          local_8._0_1_ = 0x3a;
                                          FUN_006cc1b0();
                                          FUN_006cc330();
                                          FUN_006db910();
                                          FID_conflict_operator_();
                                          local_8._0_1_ = 0x34;
                                          ~basic_string<>();
                                          basic_string<>();
                                          local_8._0_1_ = 0x3b;
                                          FUN_006cc1b0();
                                          FUN_006cc330();
                                          puVar12 = (undefined1 *)FUN_006db930();
                                          local_50 = *puVar12;
                                          local_8._0_1_ = 0x34;
                                          ~basic_string<>();
                                          local_908 = local_908 + 1;
                                          basic_string<>();
                                          local_8._0_1_ = 0x3c;
                                          FUN_006cc1b0();
                                          FUN_006cc330();
                                          local_954 = FUN_006db970();
                                          local_8 = CONCAT31(local_8._1_3_,0x34);
                                          ~basic_string<>();
                                          FUN_006cc6f0();
                                          FUN_006cc720();
                                          local_95c = 0;
                                          while (cVar1 = FUN_006cc7a0(), cVar1 != '\0') {
                                            local_ae0 = get();
                                            get();
                                            FUN_006db910();
                                            FUN_004222f0();
                                            local_95c = local_95c + 1;
                                            FUN_006cc780();
                                          }
                                          basic_string<>();
                                          local_8._0_1_ = 0x3d;
                                          FUN_006cc1b0();
                                          FUN_006cc330();
                                          local_948 = FUN_006db8f0();
                                          local_8 = CONCAT31(local_8._1_3_,0x34);
                                          ~basic_string<>();
                                          FUN_006cc150();
                                          FUN_006cc180();
                                          while (cVar1 = operator!=<>(), cVar1 != '\0') {
                                            pbVar9 = (
                                                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                                  *)FUN_006cc330();
                                            std::
                                            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                            ::
                                            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                                      (local_3dc,pbVar9);
                                            local_8._0_1_ = 0x3e;
                                            FUN_006cc330();
                                            pbVar9 = (
                                                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                                  *)FUN_006db910();
                                            std::
                                            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                            ::
                                            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                                      (local_3ac,pbVar9);
                                            local_8._0_1_ = 0x3f;
                                            FUN_006ca810();
                                            FID_conflict_operator_();
                                            FUN_006cc270();
                                            local_8._0_1_ = 0x3e;
                                            ~basic_string<>();
                                            local_8 = CONCAT31(local_8._1_3_,0x34);
                                            ~basic_string<>();
                                          }
                                          FUN_006cafd0();
                                          FUN_006c2f60();
                                          local_8 = CONCAT31(local_8._1_3_,0x28);
                                          CCommandManager::ClearAllCmdImages
                                                    ((CCommandManager *)&local_b4);
                                        }
                                        FUN_006cc290();
                                      }
                                      basic_string<>();
                                      local_8._0_1_ = 0x40;
                                      puVar6 = (undefined4 *)FUN_006cc1b0();
                                      local_894 = *puVar6;
                                      local_8._0_1_ = 0x28;
                                      ~basic_string<>();
                                      FUN_006cc180();
                                      cVar1 = operator!=<>();
                                      if (cVar1 != '\0') {
                                        pTVar13 = &std::
                                                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                                  ::RTTI_Type_Descriptor;
                                        FUN_006cc330();
                                        ptVar5 = (type_info *)FUN_006cc480();
                                        bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                                        if (bVar2) {
                                          FUN_006cc330();
                                          local_924 = FUN_006db910();
                                          local_9a8 = "2.2.301";
                                          local_8a9 = '\x01';
                                          local_9b8 = basic_string<>();
                                          local_8 = CONCAT31(local_8._1_3_,0x41);
                                          local_8b0 = local_8b0 | 1;
                                          local_9b0 = local_9b8;
                                          cVar1 = FUN_00427310();
                                          if (cVar1 == '\0') {
                                            local_9c8 = basic_string<>();
                                            local_8 = 0x42;
                                            local_8b0 = local_8b0 | 2;
                                            local_9c0 = local_9c8;
                                            cVar1 = FUN_00427310();
                                            if ((cVar1 != '\0') && (local_8a9 == '\x01'))
                                            goto LAB_006c1894;
                                            local_920 = 0;
                                          }
                                          else {
LAB_006c1894:
                                            local_920 = 1;
                                          }
                                          local_8b9 = (char)local_920;
                                          local_8 = 0x41;
                                          if ((local_8b0 & 2) != 0) {
                                            local_8b0 = local_8b0 & 0xfffffffd;
                                            ~basic_string<>();
                                          }
                                          local_8._0_1_ = 0x28;
                                          local_8._1_3_ = 0;
                                          if ((local_8b0 & 1) != 0) {
                                            local_8b0 = local_8b0 & 0xfffffffe;
                                            ~basic_string<>();
                                          }
                                          if (local_8b9 != '\0') {
                                            piVar11 = (int *)FUN_006cc4a0();
                                            *piVar11 = local_908;
                                          }
                                        }
                                      }
                                      FUN_006cc5c0();
                                      FUN_006c3020();
                                      local_8 = CONCAT31(local_8._1_3_,0x27);
                                      FUN_006c2e60();
                                    }
                                    FUN_006cc270();
                                  }
                                  FUN_006be370();
                                  cVar1 = FUN_00427270();
                                  if (cVar1 == '\0') {
                                    FUN_0074cb90();
                                  }
                                  else {
                                    FUN_0074ca30();
                                  }
                                  local_8._0_1_ = 6;
                                  FUN_006c2dd0();
                                }
                              }
                            }
                          }
                        }
                      }
                      else {
                        basic_string<>();
                        local_8._0_1_ = 0x22;
                        puVar6 = (undefined4 *)FUN_006cc1b0();
                        local_894 = *puVar6;
                        local_8._0_1_ = 6;
                        ~basic_string<>();
                        FUN_006cc180();
                        cVar1 = operator!=<>();
                        if (cVar1 != '\0') {
                          pTVar13 = &boost::container::
                                     map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                                     ::RTTI_Type_Descriptor;
                          FUN_006cc330();
                          ptVar5 = (type_info *)FUN_006cc480();
                          bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                          if (bVar2) {
                            FUN_006cc330();
                            local_934 = FUN_006db8f0();
                            basic_string<>();
                            local_8._0_1_ = 0x23;
                            FUN_006cc1b0();
                            FUN_006cc330();
                            FUN_006db910();
                            FUN_0073a7a0();
                            local_8._0_1_ = 6;
                            ~basic_string<>();
                            basic_string<>();
                            local_8._0_1_ = 0x24;
                            FUN_006cc1b0();
                            FUN_006cc330();
                            piVar11 = (int *)FUN_006db950();
                            std::_Smanip<__int64>::_Smanip<__int64>
                                      (local_c78,(_func_void_ios_base_ptr___int64 *)0x3,
                                       CONCAT44(uVar3,*piVar11 >> 0x1f));
                            local_8._0_1_ = 6;
                            ~basic_string<>();
                            FUN_0074c6a0();
                          }
                        }
                      }
                    }
                    else {
                      basic_string<>();
                      local_8._0_1_ = 0x20;
                      puVar6 = (undefined4 *)FUN_006cc1b0();
                      local_894 = *puVar6;
                      local_8._0_1_ = 6;
                      ~basic_string<>();
                      FUN_006cc180();
                      cVar1 = operator!=<>();
                      if (cVar1 != '\0') {
                        pTVar13 = &boost::container::
                                   map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                                   ::RTTI_Type_Descriptor;
                        FUN_006cc330();
                        ptVar5 = (type_info *)FUN_006cc480();
                        bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                        if (bVar2) {
                          FUN_006cc330();
                          local_97c = FUN_006db8f0();
                          basic_string<>();
                          local_8._0_1_ = 0x21;
                          FUN_006cc1b0();
                          FUN_006cc330();
                          piVar11 = (int *)FUN_006db950();
                          std::_Smanip<__int64>::_Smanip<__int64>
                                    (local_c38,(_func_void_ios_base_ptr___int64 *)0x3,
                                     CONCAT44(uVar3,*piVar11 >> 0x1f));
                          local_8._0_1_ = 6;
                          ~basic_string<>();
                          FUN_0074c680();
                        }
                      }
                    }
                  }
                  else {
                    basic_string<>();
                    local_8._0_1_ = 0x1c;
                    puVar6 = (undefined4 *)FUN_006cc1b0();
                    local_894 = *puVar6;
                    local_8._0_1_ = 6;
                    ~basic_string<>();
                    FUN_006cc180();
                    cVar1 = operator!=<>();
                    if (cVar1 != '\0') {
                      pTVar13 = &boost::container::
                                 map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                                 ::RTTI_Type_Descriptor;
                      FUN_006cc330();
                      ptVar5 = (type_info *)FUN_006cc480();
                      bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                      if (bVar2) {
                        FUN_006cc330();
                        local_8f8 = FUN_006db8f0();
                        basic_string<>();
                        local_8._0_1_ = 0x1d;
                        FUN_006cc1b0();
                        FUN_006cc330();
                        piVar11 = (int *)FUN_006db950();
                        std::_Smanip<__int64>::_Smanip<__int64>
                                  (local_c18,(_func_void_ios_base_ptr___int64 *)0x3,
                                   CONCAT44(uVar3,*piVar11 >> 0x1f));
                        local_8._0_1_ = 6;
                        ~basic_string<>();
                        basic_string<>();
                        local_8._0_1_ = 0x1e;
                        FUN_006cc1b0();
                        FUN_006cc330();
                        FUN_006db910();
                        FUN_0073a7a0();
                        local_8._0_1_ = 6;
                        ~basic_string<>();
                        basic_string<>();
                        local_8._0_1_ = 0x1f;
                        FUN_006cc1b0();
                        FUN_006cc330();
                        puVar12 = (undefined1 *)FUN_006db930();
                        local_8ba = *puVar12;
                        local_8._0_1_ = 6;
                        ~basic_string<>();
                        FUN_0074cf50();
                      }
                    }
                  }
                }
                else {
                  basic_string<>();
                  local_8._0_1_ = 0x19;
                  puVar6 = (undefined4 *)FUN_006cc1b0();
                  local_894 = *puVar6;
                  local_8._0_1_ = 6;
                  ~basic_string<>();
                  FUN_006cc180();
                  cVar1 = operator!=<>();
                  if (cVar1 != '\0') {
                    pTVar13 = &boost::container::
                               map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                               ::RTTI_Type_Descriptor;
                    FUN_006cc330();
                    ptVar5 = (type_info *)FUN_006cc480();
                    bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                    if (bVar2) {
                      FUN_006cc330();
                      local_8ec = FUN_006db8f0();
                      basic_string<>();
                      local_8._0_1_ = 0x1a;
                      FUN_006cc1b0();
                      local_8._0_1_ = 6;
                      ~basic_string<>();
                      basic_string<>();
                      local_8._0_1_ = 0x1b;
                      FUN_006cc1b0();
                      local_8._0_1_ = 6;
                      ~basic_string<>();
                      FUN_006cc180();
                      cVar1 = operator!=<>();
                      if (cVar1 != '\0') {
                        pTVar13 = &std::
                                   basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                   ::RTTI_Type_Descriptor;
                        FUN_006cc330();
                        ptVar5 = (type_info *)FUN_006cc480();
                        bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                        if (bVar2) {
                          FUN_006cc180();
                          cVar1 = operator!=<>();
                          if (cVar1 != '\0') {
                            pTVar13 = &.J::RTTI_Type_Descriptor;
                            FUN_006cc330();
                            ptVar5 = (type_info *)FUN_006cc480();
                            bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                            if (bVar2) {
                              FUN_006cc330();
                              FUN_006db910();
                              FUN_0073a7a0();
                              FUN_006cc330();
                              piVar11 = (int *)FUN_006db950();
                              std::_Smanip<__int64>::_Smanip<__int64>
                                        (local_c08,(_func_void_ios_base_ptr___int64 *)0x3,
                                         CONCAT44(uVar3,*piVar11 >> 0x1f));
                              FUN_0074c720();
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
              else {
                basic_string<>();
                local_8._0_1_ = 0x16;
                puVar6 = (undefined4 *)FUN_006cc1b0();
                local_894 = *puVar6;
                local_8._0_1_ = 6;
                ~basic_string<>();
                FUN_006cc180();
                cVar1 = operator!=<>();
                if (cVar1 != '\0') {
                  pTVar13 = &boost::container::
                             map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                             ::RTTI_Type_Descriptor;
                  FUN_006cc330();
                  ptVar5 = (type_info *)FUN_006cc480();
                  bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                  if (bVar2) {
                    FUN_006cc330();
                    local_8e0 = FUN_006db8f0();
                    basic_string<>();
                    local_8._0_1_ = 0x17;
                    FUN_006cc1b0();
                    local_8._0_1_ = 6;
                    ~basic_string<>();
                    basic_string<>();
                    local_8._0_1_ = 0x18;
                    FUN_006cc1b0();
                    local_8._0_1_ = 6;
                    ~basic_string<>();
                    FUN_006cc180();
                    cVar1 = operator!=<>();
                    if (cVar1 != '\0') {
                      pTVar13 = &std::
                                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                 ::RTTI_Type_Descriptor;
                      FUN_006cc330();
                      ptVar5 = (type_info *)FUN_006cc480();
                      bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                      if (bVar2) {
                        FUN_006cc180();
                        cVar1 = operator!=<>();
                        if (cVar1 != '\0') {
                          pTVar13 = &.J::RTTI_Type_Descriptor;
                          FUN_006cc330();
                          ptVar5 = (type_info *)FUN_006cc480();
                          bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                          if (bVar2) {
                            FUN_006cc330();
                            FUN_006db910();
                            FUN_0073a7a0();
                            FUN_006cc330();
                            piVar11 = (int *)FUN_006db950();
                            std::_Smanip<__int64>::_Smanip<__int64>
                                      (local_c48,(_func_void_ios_base_ptr___int64 *)0x3,
                                       CONCAT44(uVar3,*piVar11 >> 0x1f));
                            FUN_0074c720();
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
            else {
              *(undefined1 *)(local_89c + 0x31c) = 0;
              uVar8 = FUN_00822e60();
              *(undefined4 *)(local_89c + 800) = uVar8;
            }
          }
          else {
            basic_string<>();
            local_8._0_1_ = 0x10;
            puVar6 = (undefined4 *)FUN_006cc1b0();
            local_894 = *puVar6;
            local_8._0_1_ = 6;
            ~basic_string<>();
            FUN_006cc180();
            cVar1 = operator!=<>();
            if (cVar1 != '\0') {
              pTVar13 = &boost::container::
                         map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                         ::RTTI_Type_Descriptor;
              FUN_006cc330();
              ptVar5 = (type_info *)FUN_006cc480();
              bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
              if (bVar2) {
                FUN_006cc330();
                local_8c8 = FUN_006db8f0();
                basic_string<>();
                local_8._0_1_ = 0x11;
                basic_string<>();
                local_8._0_1_ = 0x12;
                basic_string<>();
                local_8._0_1_ = 0x13;
                puVar6 = (undefined4 *)FUN_006cc1b0();
                local_894 = *puVar6;
                local_8 = CONCAT31(local_8._1_3_,0x12);
                ~basic_string<>();
                FUN_006cc180();
                cVar1 = operator==<>();
                if (cVar1 == '\0') {
                  pTVar13 = &std::
                             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             ::RTTI_Type_Descriptor;
                  FUN_006cc330();
                  ptVar5 = (type_info *)FUN_006cc480();
                  bVar2 = type_info::operator!=(ptVar5,(type_info *)pTVar13);
                  if (bVar2) goto LAB_006bfe06;
                }
                else {
LAB_006bfe06:
                  local_895 = '\x01';
                }
                if (local_895 == '\0') {
                  FUN_006cc330();
                  FUN_006db910();
                  FID_conflict_operator_();
                  basic_string<>();
                  local_8._0_1_ = 0x14;
                  puVar6 = (undefined4 *)FUN_006cc1b0();
                  local_894 = *puVar6;
                  local_8 = CONCAT31(local_8._1_3_,0x12);
                  ~basic_string<>();
                  FUN_006cc180();
                  cVar1 = operator==<>();
                  if (cVar1 == '\0') {
                    pTVar13 = &std::
                               basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                               ::RTTI_Type_Descriptor;
                    FUN_006cc330();
                    ptVar5 = (type_info *)FUN_006cc480();
                    bVar2 = type_info::operator!=(ptVar5,(type_info *)pTVar13);
                    if (bVar2) goto LAB_006bfed5;
                  }
                  else {
LAB_006bfed5:
                    local_895 = '\x01';
                  }
                  if (local_895 == '\0') {
                    FUN_006cc330();
                    FUN_006db910();
                    FUN_0073a7a0();
                    basic_string<>();
                    local_8._0_1_ = 0x15;
                    puVar6 = (undefined4 *)FUN_006cc1b0();
                    local_894 = *puVar6;
                    local_8 = CONCAT31(local_8._1_3_,0x12);
                    ~basic_string<>();
                    FUN_006cc180();
                    cVar1 = operator==<>();
                    if (cVar1 == '\0') {
                      pTVar13 = &.J::RTTI_Type_Descriptor;
                      FUN_006cc330();
                      ptVar5 = (type_info *)FUN_006cc480();
                      bVar2 = type_info::operator!=(ptVar5,(type_info *)pTVar13);
                      if (bVar2) goto LAB_006bffa4;
                    }
                    else {
LAB_006bffa4:
                      local_895 = '\x01';
                    }
                    if (local_895 == '\0') {
                      FUN_006cc330();
                      piVar11 = (int *)FUN_006db950();
                      std::_Smanip<__int64>::_Smanip<__int64>
                                (local_ca8,(_func_void_ios_base_ptr___int64 *)0x3,
                                 CONCAT44(uVar3,*piVar11 >> 0x1f));
                      FUN_0074ca00();
                    }
                  }
                }
                local_8._0_1_ = 0x11;
                ~basic_string<>();
                local_8._0_1_ = 6;
                ~basic_string<>();
              }
            }
          }
        }
        else {
          basic_string<>();
          local_8._0_1_ = 9;
          puVar6 = (undefined4 *)FUN_006cc1b0();
          local_894 = *puVar6;
          local_8._0_1_ = 6;
          ~basic_string<>();
          FUN_006cc180();
          cVar1 = operator!=<>();
          if (cVar1 == '\0') {
LAB_006bfa6e:
            local_895 = '\x01';
          }
          else {
            pTVar13 = &boost::container::
                       map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_boost::recursive_variant_,class_boost::container::new_allocator<struct_boost::recursive_variant_>_>,struct_boost::detail::variant::void_,struct_boost::detail::variant::void_,struct_boost::d...l::variant::void_,struct_boost::detail::variant::void_>_>_>,struct_boost::container::tree_opt<0,1>_>
                       ::RTTI_Type_Descriptor;
            FUN_006cc330();
            ptVar5 = (type_info *)FUN_006cc480();
            bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
            if (!bVar2) goto LAB_006bfa6e;
            FUN_006cc330();
            local_8c0 = FUN_006db8f0();
            basic_string<>();
            local_8._0_1_ = 10;
            puVar6 = (undefined4 *)FUN_006cc1b0();
            local_894 = *puVar6;
            local_8 = CONCAT31(local_8._1_3_,6);
            ~basic_string<>();
            FUN_006cc180();
            cVar1 = operator==<>();
            if (cVar1 == '\0') {
              pTVar13 = &std::
                         basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         ::RTTI_Type_Descriptor;
              FUN_006cc330();
              ptVar5 = (type_info *)FUN_006cc480();
              bVar2 = type_info::operator!=(ptVar5,(type_info *)pTVar13);
              if (bVar2) goto LAB_006bf754;
            }
            else {
LAB_006bf754:
              local_895 = '\x01';
            }
            basic_string<>();
            local_8._0_1_ = 0xb;
            puVar6 = (undefined4 *)FUN_006cc1b0();
            local_894 = *puVar6;
            local_8._0_1_ = 6;
            ~basic_string<>();
            FUN_006cc180();
            cVar1 = operator==<>();
            if (cVar1 == '\0') {
              pTVar13 = &._N::RTTI_Type_Descriptor;
              FUN_006cc330();
              ptVar5 = (type_info *)FUN_006cc480();
              bVar2 = type_info::operator!=(ptVar5,(type_info *)pTVar13);
              if (bVar2) goto LAB_006bf7f1;
            }
            else {
LAB_006bf7f1:
              local_895 = '\x01';
            }
            if (local_895 == '\0') {
              FUN_006cc330();
              pcVar7 = (char *)FUN_006db930();
              local_8bb = *pcVar7;
              if (local_8bb == '\0') {
                FUN_0041f830();
                FUN_0041f830();
                FUN_0041f830();
                FUN_0041f830();
                FUN_0041f830();
                FUN_0041f830();
                FUN_0041f830();
                FUN_0041f830();
                FUN_0041f830();
                FUN_00764920();
              }
              else {
                *(undefined1 *)(local_89c + 8) = 1;
                *(undefined4 *)(local_89c + 4) = 3;
                uVar8 = FUN_00822e60();
                *(undefined4 *)(local_89c + 800) = uVar8;
                *(undefined1 *)(local_89c + 0x31c) = 0;
                basic_string<>();
                local_8._0_1_ = 0xc;
                puVar6 = (undefined4 *)FUN_006cc1b0();
                local_894 = *puVar6;
                local_8._0_1_ = 6;
                ~basic_string<>();
                FUN_006cc180();
                cVar1 = operator!=<>();
                if (cVar1 != '\0') {
                  pTVar13 = &std::
                             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             ::RTTI_Type_Descriptor;
                  FUN_006cc330();
                  ptVar5 = (type_info *)FUN_006cc480();
                  bVar2 = type_info::operator==(ptVar5,(type_info *)pTVar13);
                  if (bVar2) {
                    FUN_006cc330();
                    pbVar9 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              *)FUN_006db910();
                    std::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              (local_e4,pbVar9);
                    local_8 = CONCAT31(local_8._1_3_,0xd);
                    FUN_0073a7a0();
                    if (*(int *)(local_89c + 0xc38) != 0) {
                      FUN_0074d0d0();
                    }
                    if (*(int *)(local_89c + 0xc3c) != 0) {
                      FUN_006bdeb0();
                    }
                    FUN_0041f870();
                    FUN_0041f870();
                    FUN_007d6a70();
                    local_8._0_1_ = 6;
                    ~basic_string<>();
                  }
                }
              }
            }
          }
          if (local_895 != '\0') {
            FUN_0081e0c0();
            basic_string<>();
            local_8._0_1_ = 0xe;
            FUN_00421ec0();
            FUN_006dae30();
            local_8._0_1_ = 6;
            ~basic_string<>();
            std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
                      ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)
                       (local_89c + 0x2e0));
            local_8._0_1_ = 3;
            ~basic_string<>();
            local_8._0_1_ = 2;
            FUN_00430320();
            local_8._0_1_ = 1;
            Concurrency::details::SchedulingNode::~SchedulingNode(local_4c);
            local_8 = (uint)local_8._1_3_ << 8;
            FUN_006c9420();
            local_8 = 0xffffffff;
            FUN_006ca8c0();
            goto LAB_006c2db0;
          }
        }
LAB_006c2d07:
        local_8._0_1_ = 3;
        ~basic_string<>();
      }
    }
    local_8._0_1_ = 2;
    FUN_00430320();
    local_8 = CONCAT31(local_8._1_3_,1);
    Concurrency::details::SchedulingNode::~SchedulingNode(local_4c);
  }
  else {
    FUN_0081e0c0();
    basic_string<>();
    local_8._0_1_ = 0x5a;
    FUN_00421ec0();
    FUN_006dae30();
    local_8 = CONCAT31(local_8._1_3_,1);
    ~basic_string<>();
    std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
              ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(local_89c + 0x2e0));
  }
  local_8 = local_8 & 0xffffff00;
  FUN_006c9420();
  local_8 = 0xffffffff;
  FUN_006ca8c0();
LAB_006c2db0:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

