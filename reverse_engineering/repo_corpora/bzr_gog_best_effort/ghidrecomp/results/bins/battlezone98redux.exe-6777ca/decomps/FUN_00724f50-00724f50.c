
int FUN_00724f50(undefined4 param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  undefined4 uVar8;
  uint uVar9;
  int in_stack_ffffffc8;
  uint local_2c;
  uint local_28;
  int local_20;
  uint local_1c;
  
  uVar1 = FUN_00726a40(param_3,param_2);
  uVar2 = _Val_type<>();
  iVar3 = _Val_type<>();
  iVar4 = eof(iVar3);
  uVar5 = FUN_00726a40(iVar4,iVar3);
  if (uVar1 != 0) {
    if (uVar5 == uVar1) {
      uVar6 = FUN_008440c0(uVar2);
      uVar2 = FUN_00726a40(uVar6,uVar2);
      param_2 = FUN_00726a60(uVar2,param_2);
    }
    else if (uVar5 < uVar1) {
      do {
        uVar7 = eof(in_stack_ffffffc8);
        if (uVar1 == uVar7) {
          local_28 = uVar1 / (uVar5 + 1);
          if (uVar1 % (uVar5 + 1) == uVar5) {
            local_28 = local_28 + 1;
          }
        }
        else {
          local_28 = (uVar1 + 1) / (uVar5 + 1);
        }
        local_20 = 0;
        for (local_1c = 1; local_1c <= local_28; local_1c = (uVar5 + 1) * local_1c) {
          uVar6 = uVar2;
          uVar8 = FUN_008440c0(uVar2);
          iVar3 = FUN_00726a40(uVar8,uVar6);
          local_20 = iVar3 * local_1c + local_20;
          if (local_1c * uVar5 - ((uVar1 - local_1c) + 1) == 0) {
            return local_20;
          }
        }
        uVar7 = FUN_00724f50(param_1,0,uVar1 / local_1c,0);
        uVar9 = eof(in_stack_ffffffc8);
      } while (((uVar9 / local_1c < uVar7) ||
               (uVar9 = local_20 + uVar7 * local_1c, uVar9 < uVar7 * local_1c)) || (uVar1 < uVar9));
      param_2 = FUN_00726a60(uVar9,param_2);
    }
    else {
      uVar7 = eof(in_stack_ffffffc8);
      if (uVar5 == uVar7) {
        local_2c = uVar5 / (uVar1 + 1);
        if (uVar5 % (uVar1 + 1) == uVar1) {
          local_2c = local_2c + 1;
        }
      }
      else {
        local_2c = (uVar5 + 1) / (uVar1 + 1);
      }
      do {
        uVar6 = uVar2;
        uVar8 = FUN_008440c0(uVar2);
        uVar5 = FUN_00726a40(uVar8,uVar6);
      } while (uVar1 < uVar5 / local_2c);
      param_2 = FUN_00726a60(uVar5 / local_2c,param_2);
    }
  }
  return param_2;
}

