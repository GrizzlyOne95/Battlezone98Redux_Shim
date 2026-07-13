
int * FUN_006dba70(int *param_1,undefined4 param_2)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined1 local_7c [8];
  undefined1 local_74 [16];
  undefined4 local_64;
  undefined4 local_60;
  int *local_5c;
  locale local_58 [8];
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 local_2c;
  int local_28;
  undefined4 local_24;
  void *local_20;
  int local_1c;
  int local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853a0c;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (param_1 == (int *)0x0) {
    local_18 = 0;
  }
  else {
    local_18 = (int)param_1 + *(int *)(*param_1 + 4);
  }
  FUN_006be210(local_18);
  local_8 = 0;
  FUN_006e27b0(param_1);
  local_34 = std::ios_base::getloc((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)));
  local_11 = FUN_006eb150(local_34,uVar3);
  FUN_00417b50();
  if (local_11 == '\0') {
    local_20 = operator_new(0x114);
    local_8._0_1_ = 2;
    if (local_20 == (void *)0x0) {
      local_24 = 0;
    }
    else {
      local_24 = FUN_006e1d70(0);
    }
    local_48 = local_24;
    local_8._0_1_ = 0;
    local_2c = local_24;
    local_50 = std::ios_base::getloc((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)));
    local_8._0_1_ = 3;
    local_4c = local_50;
    FUN_006db9f0(local_50,local_2c);
    local_8._0_1_ = 5;
    FUN_00417b50();
    std::basic_ios<char,struct_std::char_traits<char>_>::imbue
              ((basic_ios<char,struct_std::char_traits<char>_> *)
               ((int)param_1 + *(int *)(*param_1 + 4)),local_58);
    FUN_00417b50();
    if (param_1 == (int *)0x0) {
      local_28 = 0;
    }
    else {
      local_28 = (int)param_1 + *(int *)(*param_1 + 4);
    }
    cVar2 = std::basic_ios<char,struct_std::char_traits<char>_>::fill
                      ((basic_ios<char,struct_std::char_traits<char>_> *)
                       ((int)param_1 + *(int *)(*param_1 + 4)));
    FUN_006e1e90(local_7c,local_64,local_60,local_28,cVar2,param_2);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00417b50();
  }
  else {
    if (param_1 == (int *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = (int)param_1 + *(int *)(*param_1 + 4);
    }
    local_40 = std::ios_base::getloc((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)));
    local_8._0_1_ = 1;
    local_3c = local_40;
    bVar1 = std::basic_ios<char,struct_std::char_traits<char>_>::fill
                      ((basic_ios<char,struct_std::char_traits<char>_> *)
                       ((int)param_1 + *(int *)(*param_1 + 4)));
    uVar3 = (uint)bVar1;
    puVar4 = local_74;
    iVar5 = local_1c;
    FUN_006eb1c0(local_40,puVar4,local_64,local_60,local_1c,uVar3,param_2);
    FUN_006e1e90(puVar4,local_64,local_60,iVar5,uVar3,param_2);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00417b50();
  }
  local_5c = param_1;
  local_8 = 0xffffffff;
  FUN_006be240();
  ExceptionList = local_10;
  return local_5c;
}

