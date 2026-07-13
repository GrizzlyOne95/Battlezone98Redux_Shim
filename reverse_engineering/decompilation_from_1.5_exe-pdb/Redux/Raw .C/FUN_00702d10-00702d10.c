
uint FUN_00702d10(int param_1,uint param_2,undefined4 *param_3)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  undefined4 uVar6;
  int local_b8;
  undefined1 *local_b4;
  undefined1 local_84 [8];
  undefined1 local_7c [8];
  undefined1 local_74 [24];
  undefined1 local_5c [8];
  undefined1 local_54 [8];
  undefined4 local_4c;
  undefined4 local_48;
  undefined1 *local_44;
  undefined1 *local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_18;
  undefined4 local_14;
  undefined1 local_d;
  uint local_c;
  int local_8;
  
  local_c = 0;
  puVar2 = (undefined4 *)FUN_006ab750();
  uVar4 = puVar2[1];
  *param_3 = *puVar2;
  param_3[1] = uVar4;
  while( true ) {
    if (*(int *)(local_8 + 0x5c) == 4) {
      return local_c;
    }
    if (*(int *)(local_8 + 0x5c) == 5) break;
    if ((param_2 <= local_c) && (*(int *)(local_8 + 0x18) != 0)) {
      return local_c;
    }
    if (*(int *)(local_8 + 0x5c) == 0) {
      local_b4 = (undefined1 *)(param_1 + local_c);
      local_b8 = 0x702d8a;
      iVar3 = FUN_00705980();
      local_c = iVar3 + local_c;
      if (*(int *)(local_8 + 0x18) == 0) {
        cVar1 = FUN_006ab7d0();
        local_d = cVar1 == '\0';
        local_b4 = (undefined1 *)(uint)*(byte *)(local_8 + 5);
        local_b8 = local_8 + 0xc;
        puVar2 = (undefined4 *)FUN_00705c60(local_7c);
        uVar4 = puVar2[1];
        *param_3 = *puVar2;
        param_3[1] = uVar4;
        cVar1 = FUN_006ab7d0();
        if (cVar1 != '\0') {
          return local_c;
        }
        *(undefined4 *)(local_8 + 0x5c) = 1;
        *(undefined4 *)(local_8 + 0x1c) = 0;
        local_b4 = (undefined1 *)0x702e18;
        iVar3 = FUN_006ba480();
        *(int *)(local_8 + 0x18) = iVar3 + -2;
      }
    }
    else if (*(int *)(local_8 + 0x5c) == 1) {
      local_b4 = (undefined1 *)(param_1 + local_c);
      local_b8 = 0x702e4c;
      iVar3 = FUN_00705a80();
      local_c = iVar3 + local_c;
      if (*(int *)(local_8 + 0x18) == 0) {
        local_b8 = *(int *)(local_8 + 0x4c);
        local_b4 = *(undefined1 **)(local_8 + 0x50);
        puVar2 = (undefined4 *)FUN_00705ea0(local_54,*(undefined2 *)(local_8 + 0xc));
        uVar4 = puVar2[1];
        *param_3 = *puVar2;
        param_3[1] = uVar4;
        cVar1 = FUN_006ab7d0();
        if (cVar1 != '\0') {
          return local_c;
        }
        *(undefined4 *)(local_8 + 0x5c) = 3;
        local_b4 = (undefined1 *)(local_8 + 0xc);
        local_b8 = 0x702ecd;
        uVar4 = FUN_006ba6b0();
        *(undefined4 *)(local_8 + 0x18) = uVar4;
        local_b4 = (undefined1 *)0x702ee2;
        local_14 = FUN_006ba430();
        local_b4 = (undefined1 *)0x702ef1;
        cVar1 = FUN_006ba0d0();
        if (cVar1 == '\0') {
          cVar1 = FUN_006ab7d0();
          if (cVar1 == '\0') {
            if (*(uint *)(local_8 + 8) < *(uint *)(local_8 + 0x18)) {
              local_b4 = local_84;
              local_b8 = 0x702fb3;
              puVar2 = (undefined4 *)make_error_code();
              uVar4 = puVar2[1];
              *param_3 = *puVar2;
              param_3[1] = uVar4;
              return local_c;
            }
            local_b4 = (undefined1 *)(local_8 + 0xc);
            local_b8 = 0x702fdb;
            local_30 = FUN_006ba5d0();
            local_40 = (undefined1 *)&local_b8;
            piVar5 = &local_b8;
            uVar4 = *(undefined4 *)(local_8 + 0x18);
            uVar6 = local_14;
            FUN_00421ec0(&local_b8,local_14,uVar4);
            local_4c = FUN_006e1b80(piVar5,uVar6,uVar4);
            local_2c = FUN_00706280();
            local_b4 = (undefined1 *)0x703031;
            local_24 = local_2c;
            FUN_00704960();
            FUN_006cd590();
            cVar1 = FUN_0044bb90();
            if (cVar1 != '\0') {
              local_b4 = (undefined1 *)0x70305a;
              FUN_006ba3a0();
              local_b4 = (undefined1 *)0x70306c;
              FUN_00421ec0();
              local_b4 = (undefined1 *)0x703073;
              FUN_006e1aa0();
            }
          }
          else {
            FUN_00421ec0();
            local_18 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        *)FUN_006cc070();
            iVar3 = FUN_004170c0();
            if (*(uint *)(local_8 + 8) < (uint)(iVar3 + *(int *)(local_8 + 0x18))) {
              local_b4 = local_5c;
              local_b8 = 0x7030ae;
              puVar2 = (undefined4 *)make_error_code();
              uVar4 = puVar2[1];
              *param_3 = *puVar2;
              param_3[1] = uVar4;
              return local_c;
            }
            local_b4 = (undefined1 *)(local_8 + 0xc);
            local_b8 = 0x7030d6;
            local_34 = FUN_006ba5d0();
            local_b4 = (undefined1 *)0x7030e5;
            uVar4 = FUN_006ba710();
            *(undefined4 *)(local_8 + 0x28) = uVar4;
            iVar3 = FUN_004170c0();
            local_b4 = (undefined1 *)0x703105;
            std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            reserve(local_18,iVar3 + *(int *)(local_8 + 0x18));
          }
          *(int *)(local_8 + 0x48) = local_8 + 0x20;
        }
        else {
          local_b4 = (undefined1 *)(local_8 + 0xc);
          local_b8 = 0x702f12;
          local_3c = FUN_006ba5d0();
          local_44 = (undefined1 *)&local_b8;
          piVar5 = &local_b8;
          uVar4 = *(undefined4 *)(local_8 + 0x18);
          uVar6 = local_14;
          FUN_00421ec0(&local_b8,local_14,uVar4);
          local_48 = FUN_006e1b80(piVar5,uVar6,uVar4);
          local_38 = FUN_00706280();
          local_b4 = (undefined1 *)0x702f68;
          local_28 = local_38;
          FUN_00704960();
          FUN_006cd590();
          *(int *)(local_8 + 0x48) = local_8 + 0x34;
        }
      }
    }
    else if (*(int *)(local_8 + 0x5c) == 2) {
      *(undefined4 *)(local_8 + 0x5c) = 3;
    }
    else {
      if (*(int *)(local_8 + 0x5c) != 3) {
        local_b4 = local_74;
        local_b8 = 0x7031f5;
        puVar2 = (undefined4 *)make_error_code();
        uVar4 = puVar2[1];
        *param_3 = *puVar2;
        param_3[1] = uVar4;
        return 0;
      }
      local_20 = param_2 - local_c;
      local_b4 = (undefined1 *)(local_8 + 0x18);
      local_b8 = 0x703154;
      piVar5 = (int *)_Min_value<>();
      local_b4 = (undefined1 *)*piVar5;
      local_1c = (int)local_b4;
      if (local_b4 != (undefined1 *)0x0) {
        local_b8 = param_1 + local_c;
        iVar3 = FUN_00705af0();
        local_c = iVar3 + local_c;
        cVar1 = FUN_006ab7d0();
        if (cVar1 != '\0') {
          return local_c;
        }
      }
      if (*(int *)(local_8 + 0x18) == 0) {
        local_b4 = (undefined1 *)0x7031aa;
        cVar1 = FUN_006ba370();
        if (cVar1 == '\0') {
          FUN_007058a0();
        }
        else {
          local_b4 = (undefined1 *)0x7031c0;
          puVar2 = (undefined4 *)FUN_007057a0();
          uVar4 = puVar2[1];
          *param_3 = *puVar2;
          param_3[1] = uVar4;
          cVar1 = FUN_006ab7d0();
          if (cVar1 != '\0') {
            return local_c;
          }
        }
      }
    }
  }
  return local_c;
}

