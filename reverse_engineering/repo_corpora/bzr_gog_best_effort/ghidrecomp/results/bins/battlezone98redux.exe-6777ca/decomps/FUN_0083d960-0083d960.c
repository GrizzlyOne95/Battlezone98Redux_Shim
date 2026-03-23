
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * FUN_0083d960(int *param_1,int param_2)

{
  uint uVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0086540c;
  local_c = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffff0;
  ExceptionList = &local_c;
  if (param_2 < 0x10c) {
    if (param_2 == 0x10b) {
      if ((DAT_00914d24 & 1) == 0) {
        DAT_00914d24 = DAT_00914d24 | 1;
        local_4 = 0;
        _DAT_00914d20 = boost::system::_anon_56EC52FE::generic_error_category::vftable;
        FUN_0083e979(&LAB_008681d0);
      }
      *param_1 = 0x16;
      param_1[1] = (int)&DAT_00914d20;
      ExceptionList = local_c;
      return param_1;
    }
    switch(param_2) {
    case 0:
      FUN_0083e3a0(param_1,0,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 1:
      FUN_0083e3a0(param_1,0x28,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 2:
    case 3:
      FUN_0083e3a0(param_1,2,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 4:
switchD_0083d9aa_caseD_4:
      FUN_0083e3a0(param_1,0x18,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 5:
    case 0xc:
    case 0x10:
    case 0x13:
    case 0x20:
    case 0x52:
switchD_0083d9aa_caseD_5:
      FUN_0083e3a0(param_1,0xd,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 6:
    case 0x7b:
    case 0x83:
switchD_0083d9aa_caseD_6:
      FUN_0083e3a0(param_1,0x16,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 8:
    case 0xe:
      FUN_0083e3a0(param_1,0xc,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0xf:
    case 0x14:
    case 0x37:
      FUN_0083e3a0(param_1,0x13,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x11:
      FUN_0083e3a0(param_1,0x12,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x15:
switchD_0083d9aa_caseD_15:
      FUN_0083e3a0(param_1,0xb,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x19:
    case 0x1d:
    case 0x1e:
    case 0x6e:
      goto switchD_0083d9aa_caseD_19;
    case 0x21:
    case 0xd4:
      FUN_0083e3a0(param_1,0x27,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x27:
    case 0x70:
      FUN_0083e3a0(param_1,0x1c,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x50:
    case 0xb7:
      FUN_0083e3a0(param_1,0x11,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x6f:
switchD_0083d9aa_caseD_6f:
      FUN_0083e3a0(param_1,0x26,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x8e:
    case 0xaa:
switchD_0083d9aa_caseD_8e:
      FUN_0083e3a0(param_1,0x10,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x91:
      FUN_0083e3a0(param_1,0x29,uVar1);
      ExceptionList = local_c;
      return param_1;
    }
  }
  else if (param_2 < 0x2715) {
    if (param_2 == 0x2714) {
      FUN_0083e3a0(param_1,4,uVar1);
      ExceptionList = local_c;
      return param_1;
    }
    if (param_2 < 0x3f6) {
      if (param_2 != 0x3f5) {
        switch(param_2) {
        case 0x3e3:
          FUN_0083e3a0(param_1,0x69,uVar1);
          ExceptionList = local_c;
          return param_1;
        default:
          goto switchD_0083d9aa_caseD_7;
        case 0x3e6:
          goto switchD_0083d9aa_caseD_5;
        case 0x3f3:
        case 0x3f4:
          break;
        }
      }
switchD_0083d9aa_caseD_19:
      FUN_0083e3a0(param_1,5,uVar1);
      ExceptionList = local_c;
      return param_1;
    }
    if (param_2 == 0x4d5) goto switchD_0083d9aa_caseD_15;
    if ((param_2 == 0x961) || (param_2 == 0x964)) goto switchD_0083d9aa_caseD_8e;
  }
  else {
    switch(param_2) {
    case 0x2719:
      FUN_0083e3a0(param_1,9,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x271d:
      goto switchD_0083d9aa_caseD_5;
    case 0x271e:
      FUN_0083e3a0(param_1,0xe,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2726:
      goto switchD_0083d9aa_caseD_6;
    case 0x2728:
      goto switchD_0083d9aa_caseD_4;
    case 0x2733:
      FUN_0083e3a0(param_1,0x8c,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2734:
      FUN_0083e3a0(param_1,0x70,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2735:
      FUN_0083e3a0(param_1,0x67,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2736:
      FUN_0083e3a0(param_1,0x80,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2737:
      FUN_0083e3a0(param_1,0x6d,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2738:
      FUN_0083e3a0(param_1,0x73,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2739:
      FUN_0083e3a0(param_1,0x88,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x273a:
      FUN_0083e3a0(param_1,0x7b,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x273b:
      FUN_0083e3a0(param_1,0x87,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x273d:
      FUN_0083e3a0(param_1,0x82,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x273f:
      FUN_0083e3a0(param_1,0x66,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2740:
      FUN_0083e3a0(param_1,100,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2741:
      FUN_0083e3a0(param_1,0x65,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2742:
      FUN_0083e3a0(param_1,0x74,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2743:
      FUN_0083e3a0(param_1,0x76,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2744:
      FUN_0083e3a0(param_1,0x75,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2745:
      FUN_0083e3a0(param_1,0x6a,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2746:
      FUN_0083e3a0(param_1,0x6c,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2747:
      FUN_0083e3a0(param_1,0x77,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2748:
      FUN_0083e3a0(param_1,0x71,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x2749:
      FUN_0083e3a0(param_1,0x7e,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x274c:
      FUN_0083e3a0(param_1,0x8a,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x274d:
      FUN_0083e3a0(param_1,0x6b,uVar1);
      ExceptionList = local_c;
      return param_1;
    case 0x274f:
      goto switchD_0083d9aa_caseD_6f;
    case 0x2751:
      FUN_0083e3a0(param_1,0x6e,uVar1);
      ExceptionList = local_c;
      return param_1;
    }
  }
switchD_0083d9aa_caseD_7:
  if ((DAT_00914d1c & 1) == 0) {
    DAT_00914d1c = DAT_00914d1c | 1;
    local_4 = 1;
    _DAT_00914d18 = boost::system::_anon_56EC52FE::system_error_category::vftable;
    FUN_0083e979(&LAB_008681e0);
  }
  *param_1 = param_2;
  param_1[1] = (int)&DAT_00914d18;
  ExceptionList = local_c;
  return param_1;
}

