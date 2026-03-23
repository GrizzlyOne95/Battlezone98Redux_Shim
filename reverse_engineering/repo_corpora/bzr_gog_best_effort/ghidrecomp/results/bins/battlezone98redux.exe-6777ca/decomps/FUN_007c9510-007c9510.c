
undefined4 __thiscall
FUN_007c9510(int *param_1,undefined4 param_2,int param_3,uint param_4,undefined4 *param_5)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uStack_50;
  undefined1 auStack_40 [4];
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int *local_1c;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008623f0;
  local_10 = ExceptionList;
  uStack_50 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_50;
  ExceptionList = &local_10;
  local_3c = param_3 - *param_1 >> 2;
  local_1c = param_1;
  puVar1 = &uStack_50;
  if (param_4 != 0) {
    uVar2 = FUN_00423eb0();
    if (uVar2 < param_4) {
      iVar3 = size();
      iVar4 = FID_conflict_max_size();
      if ((uint)(iVar4 - iVar3) < param_4) {
        FUN_00423e40();
      }
      iVar3 = size();
      uVar5 = FID_conflict__Grow_to(iVar3 + param_4);
      local_30 = uVar5;
      Getal(&local_15);
      local_20 = allocate(uVar5);
      local_28 = param_3 - *local_1c >> 2;
      local_24 = 0;
      local_8 = 0;
      uVar5 = FUN_00417780(param_5);
      FUN_007c98f0(local_20 + local_28 * 4,param_4,uVar5);
      local_24 = local_24 + 1;
      FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                (*local_1c,param_3,local_20);
      local_24 = local_24 + 1;
      FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                (param_3,local_1c[1],local_20 + (local_28 + param_4) * 4);
      uVar5 = FUN_007c96b2();
      return uVar5;
    }
    if ((uint)(local_1c[1] - param_3 >> 2) < param_4) {
      local_34 = *param_5;
      FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                (param_3,local_1c[1],param_3 + param_4 * 4);
      local_8 = 2;
      uVar5 = FUN_00417780(&local_34);
      FUN_007c98f0(local_1c[1],param_4 - (local_1c[1] - param_3 >> 2),uVar5);
      uVar5 = FUN_007c97e8();
      return uVar5;
    }
    local_38 = *param_5;
    local_2c = local_1c[1];
    iVar3 = FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                      (local_2c + param_4 * -4,local_2c,local_1c[1]);
    local_1c[1] = iVar3;
    FUN_00422c10(param_3,local_1c[1]);
    _Move<>(param_3,local_2c + param_4 * -4,local_2c);
    FUN_007c9930(param_3,param_3 + param_4 * 4,&local_38);
    puVar1 = (uint *)local_14;
  }
  local_14 = (undefined1 *)puVar1;
  uVar5 = param_2;
  iVar3 = local_3c;
  FID_conflict_begin(auStack_40);
  FID_conflict_operator_(uVar5,iVar3);
  ExceptionList = local_10;
  return param_2;
}

