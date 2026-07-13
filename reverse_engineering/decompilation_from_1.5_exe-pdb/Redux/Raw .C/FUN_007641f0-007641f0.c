
void __fastcall FUN_007641f0(int *param_1)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  int iVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_2d0 [12];
  undefined4 uStack_2c4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbStack_2c0;
  basic_ostream<char,struct_std::char_traits<char>_> local_2b4 [152];
  basic_ostream<char,struct_std::char_traits<char>_> local_21c [152];
  basic_ostream<char,struct_std::char_traits<char>_> local_184 [152];
  undefined4 local_ec;
  undefined4 local_e8;
  undefined1 *local_e4;
  undefined1 *local_e0;
  undefined4 local_dc;
  undefined1 *local_d8;
  int local_d4;
  int local_d0;
  int local_cc;
  int local_c8;
  int *local_c4;
  char local_bd;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_74 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_5c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d102;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_c4 = param_1;
  if (((char)param_1[3] == '\0') || (DAT_00918430 != 0)) goto LAB_0076473a;
  local_bd = '\0';
  local_c8 = *(int *)(DAT_0094672c + 0x40);
  pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_00482850();
  pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                0x764264;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar2);
  local_8 = 0;
  pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                0x764274;
  local_d0 = FUN_004888b0();
  pbStack_2c0 = local_2c;
  uStack_2c4 = 0x76428b;
  cVar1 = FUN_00427310();
  if (cVar1 == '\0') {
    pbStack_2c0 = local_2c;
    uStack_2c4 = 0x76437d;
    cVar1 = FUN_00427310();
    if (cVar1 == '\0') {
      pbStack_2c0 = local_2c;
      uStack_2c4 = 0x764395;
      cVar1 = FUN_00427310();
      if (cVar1 == '\0') {
        pbStack_2c0 = local_2c;
        uStack_2c4 = 0x7643ad;
        cVar1 = FUN_00427310();
        if (cVar1 == '\0') {
          pbStack_2c0 = local_2c;
          uStack_2c4 = 0x7643c5;
          cVar1 = FUN_00427310();
          if (cVar1 == '\0') goto LAB_0076470c;
        }
      }
    }
    local_cc = local_d0 + 1;
    basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,4);
    iVar3 = FUN_004344a0();
    if (iVar3 == 2) {
      pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x764405;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_44,"grp.MISSION_COMPLETE_");
    }
    else {
      pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x764414;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_44,"MISSION_COMPLETE_");
    }
    if (local_c8 < 3) {
      iVar3 = FUN_004344a0();
      if ((iVar3 == 2) && (1 < local_c8)) goto LAB_00764438;
    }
    else {
LAB_00764438:
      pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x764444;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (local_5c,local_44);
      local_8._0_1_ = 5;
      pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x764455;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_5c,"HARD_");
      pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x2;
      uStack_2c4 = 0x764464;
      FUN_006ca050();
      local_8._0_1_ = 6;
      pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x76447b;
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_21c,local_cc);
      pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x76448d;
      GetPolicy();
      local_8 = CONCAT31(local_8._1_3_,7);
      pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x7644a0;
      FUN_00449810();
      pbStack_2c0 = local_2c;
      uStack_2c4 = 0x7644ae;
      cVar1 = FUN_00427310();
      if (cVar1 == '\0') {
        pbStack_2c0 = local_2c;
        uStack_2c4 = 0x7644d5;
        cVar1 = FUN_00427310();
        if (cVar1 == '\0') {
          pbStack_2c0 = local_2c;
          uStack_2c4 = 0x7644fc;
          cVar1 = FUN_00427310();
          if (cVar1 == '\0') {
            pbStack_2c0 = local_2c;
            uStack_2c4 = 0x764523;
            cVar1 = FUN_00427310();
            if (cVar1 != '\0') {
              pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)0x76453a;
              std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
              operator=(local_5c,"_DLC_CRA");
            }
          }
          else {
            pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)0x764513;
            std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            operator=(local_5c,"_DLC_BDG");
          }
        }
        else {
          pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)0x7644ec;
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          operator=(local_5c,"_CCA");
        }
      }
      else {
        pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x7644c5;
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_5c,"_NSDF");
      }
      local_e0 = abStack_2d0;
      local_e8 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           (abStack_2d0,local_5c);
      (**(code **)(*local_c4 + 0x14))();
      local_bd = '\x01';
      local_8._0_1_ = 6;
      ~basic_string<>();
      local_8._0_1_ = 5;
      FUN_006b3a50();
      local_8 = CONCAT31(local_8._1_3_,4);
      ~basic_string<>();
    }
    if (local_c8 < 2) {
      iVar3 = FUN_004344a0();
      if ((iVar3 == 2) && (0 < local_c8)) goto LAB_007645bc;
    }
    else {
LAB_007645bc:
      pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x7645c9;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_44,"NORMAL_");
      pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x2;
      uStack_2c4 = 0x7645d8;
      FUN_006ca050();
      local_8._0_1_ = 8;
      pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x7645ef;
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_2b4,local_cc);
      pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x764601;
      GetPolicy();
      local_8 = CONCAT31(local_8._1_3_,9);
      pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x764614;
      FUN_00449810();
      pbStack_2c0 = local_2c;
      uStack_2c4 = 0x764622;
      cVar1 = FUN_00427310();
      if (cVar1 == '\0') {
        pbStack_2c0 = local_2c;
        uStack_2c4 = 0x764649;
        cVar1 = FUN_00427310();
        if (cVar1 == '\0') {
          pbStack_2c0 = local_2c;
          uStack_2c4 = 0x764670;
          cVar1 = FUN_00427310();
          if (cVar1 == '\0') {
            pbStack_2c0 = local_2c;
            uStack_2c4 = 0x764697;
            cVar1 = FUN_00427310();
            if (cVar1 != '\0') {
              pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)0x7646ae;
              std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
              operator=(local_44,"_DLC_CRA");
            }
          }
          else {
            pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)0x764687;
            std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            operator=(local_44,"_DLC_BDG");
          }
        }
        else {
          pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)0x764660;
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          operator=(local_44,"_CCA");
        }
      }
      else {
        pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x764639;
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_44,"_NSDF");
      }
      local_d8 = abStack_2d0;
      local_ec = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           (abStack_2d0,local_44);
      (**(code **)(*local_c4 + 0x14))();
      local_bd = '\x01';
      local_8._0_1_ = 8;
      ~basic_string<>();
      local_8 = CONCAT31(local_8._1_3_,4);
      FUN_006b3a50();
    }
    local_8 = local_8 & 0xffffff00;
    ~basic_string<>();
  }
  else {
    local_d4 = local_d0 + 1;
    basic_string<>();
    local_8._0_1_ = 1;
    pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7642c1;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_74,"MISSION_COMPLETE_TUTORIAL_");
    pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x2;
    uStack_2c4 = 0x7642d0;
    FUN_006ca050();
    local_8._0_1_ = 2;
    pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7642e7;
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_184,local_d4);
    pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7642f9;
    GetPolicy();
    local_8._0_1_ = 3;
    pbStack_2c0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x76430c;
    FUN_00449810();
    local_e4 = abStack_2d0;
    local_dc = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         (abStack_2d0,local_74);
    (**(code **)(*local_c4 + 0x14))();
    local_bd = '\x01';
    local_8._0_1_ = 2;
    ~basic_string<>();
    local_8._0_1_ = 1;
    FUN_006b3a50();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
  }
LAB_0076470c:
  if (local_bd == '\x01') {
    (**(code **)(*local_c4 + 0x18))();
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
LAB_0076473a:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

