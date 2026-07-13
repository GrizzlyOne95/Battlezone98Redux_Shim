
undefined4 FUN_007c7070(int *param_1,char param_2)

{
  char cVar1;
  int iVar2;
  wchar_t *pwVar3;
  undefined4 uVar4;
  uint uStack_50;
  int local_40;
  int local_3c;
  Root *local_34;
  int local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 *local_20;
  int local_1c;
  undefined4 *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008620e0;
  local_10 = ExceptionList;
  uStack_50 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_50;
  ExceptionList = &local_10;
  cVar1 = (**(code **)(**(int **)(DAT_00920ea0 + 0xc) + 0x88))();
  if ((cVar1 == '\0') || (iVar2 = FUN_004346a0(), iVar2 != 0)) {
    local_1c = 0;
    if ((param_1 != (int *)0x0) && (cVar1 = FUN_0041fc90(), cVar1 == '\0')) {
      pwVar3 = std::
               basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
               ::back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                       *)(param_1 + 0xb));
      local_1c = *(int *)pwVar3;
    }
    if (local_1c == 0x17) {
      if (param_1 != (int *)0x0) {
        *(undefined1 *)(param_1 + 9) = 1;
        *(undefined1 *)(param_1 + 10) = 0;
      }
      DAT_00918328 = 0;
    }
    else if (param_2 == '\0') {
      FUN_00822ed0(1);
    }
    else {
      FUN_00822ed0(0x32);
    }
    if ((param_1 == (int *)0x0) || (cVar1 = FUN_007c7020(), cVar1 != '\0')) {
      uVar4 = 0;
    }
    else {
      uVar4 = 1;
    }
  }
  else {
    iVar2 = FUN_00684ce0(1);
    if (iVar2 == 0) {
      if (((param_1 != (int *)0x0) && (*(char *)((int)param_1 + 0x27) != '\0')) &&
         (cVar1 = FUN_0041fc90(), cVar1 == '\0')) {
        pwVar3 = std::
                 basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                 ::back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                         *)(param_1 + 0xb));
        local_2c = *(int *)pwVar3;
        if (local_2c == 0x17) {
          *(undefined1 *)(param_1 + 9) = 1;
          *(undefined1 *)(param_1 + 10) = 0;
          DAT_00918328 = 0;
        }
      }
    }
    else {
      if (((param_1 != (int *)0x0) && (*(char *)((int)param_1 + 0x27) != '\0')) &&
         (cVar1 = FUN_0041fc90(), cVar1 == '\0')) {
        if (param_1[5] != 0) {
          local_20 = (undefined4 *)param_1[5];
          local_18 = local_20;
          if (local_20 == (undefined4 *)0x0) {
            local_24 = 0;
          }
          else {
            local_24 = (**(code **)*local_20)(1);
          }
        }
        param_1[5] = 0;
        FUN_00682450();
        FUN_00687c90();
        iVar2 = FUN_00685520();
        if (iVar2 == 0) {
          FUN_006854b0();
          FUN_006854d0();
        }
        FUN_007c6760();
        pwVar3 = std::
                 basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                 ::back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                         *)(param_1 + 0xb));
        local_28 = *(undefined4 *)pwVar3;
        *(undefined1 *)((int)param_1 + 0x27) = 0;
        iVar2 = FUN_007c7ad0(local_28);
        param_1[5] = iVar2;
        local_40 = param_1[7];
        local_3c = param_1[8];
        (**(code **)(*param_1 + 0x20))(&local_40);
      }
      if ((param_1 != (int *)0x0) && (param_1[5] != 0)) {
        (**(code **)(*(int *)param_1[5] + 0x34))();
      }
      FUN_00687d80();
      FUN_0067dc80(DAT_00917580);
      iVar2 = FUN_00685520();
      if (iVar2 == 0) {
        FUN_006854d0();
      }
      FUN_00687ac0();
      iVar2 = FUN_00685520();
      if (iVar2 != 0) {
        FUN_006854f0();
      }
    }
    if ((param_1 != (int *)0x0) && (param_1[5] != 0)) {
      local_8 = 0;
      local_30 = FUN_0044d2a0();
      local_34 = *(Root **)(local_30 + 4);
      Ogre::Root::renderOneFrame(local_34);
      DAT_00920c6e = 1;
      uVar4 = FUN_007c73bf();
      return uVar4;
    }
    iVar2 = FUN_00684ce0(0);
    if (iVar2 == 0) {
      if (param_2 == '\0') {
        FUN_00822ed0(1);
      }
    }
    else {
      FUN_006854b0();
      iVar2 = FUN_00685520();
      if (iVar2 == 0) {
        FUN_006854d0();
      }
    }
    if (param_2 != '\0') {
      FUN_00822ed0(0x32);
    }
    if ((param_1 == (int *)0x0) || (cVar1 = FUN_007c7020(), cVar1 != '\0')) {
      uVar4 = 0;
    }
    else {
      uVar4 = 1;
    }
  }
  ExceptionList = local_10;
  return uVar4;
}

