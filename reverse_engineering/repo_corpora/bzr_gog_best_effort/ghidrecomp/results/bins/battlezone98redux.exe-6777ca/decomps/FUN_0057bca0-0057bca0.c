
void FUN_0057bca0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uStack_44;
  uint local_20;
  undefined4 *local_1c;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ba40;
  local_10 = ExceptionList;
  uStack_44 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_44;
  ExceptionList = &local_10;
  local_20 = 0;
  _Distance<>(param_2,param_3,&local_20);
  if (local_20 != 0) {
    uVar1 = FUN_0057f2c0();
    if (uVar1 < local_20) {
      iVar2 = FUN_004bb390();
      iVar3 = FID_conflict_max_size();
      if ((uint)(iVar3 - iVar2) < local_20) {
        FUN_00423e40();
      }
      iVar2 = FUN_004bb390();
      uVar4 = FID_conflict__Grow_to(iVar2 + local_20);
      Getal(&local_15);
      uVar4 = allocate(uVar4);
      local_8 = 0;
      uVar4 = FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                        (*local_1c,param_1,uVar4);
      uVar4 = FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                        (param_2,param_3,uVar4);
      FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                (param_1,local_1c[1],uVar4);
      FUN_0057bdf4();
      return;
    }
    FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
              (param_2,param_3,local_1c[1]);
    rotate<>(param_1,local_1c[1],local_1c[1] + local_20);
    local_1c[1] = local_1c[1] + local_20;
    FUN_00422c10(param_1,local_1c[1]);
  }
  ExceptionList = local_10;
  return;
}

