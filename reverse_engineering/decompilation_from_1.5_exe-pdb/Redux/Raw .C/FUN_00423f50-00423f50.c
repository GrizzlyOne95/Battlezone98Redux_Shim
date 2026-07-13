
void __thiscall FUN_00423f50(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  uint uStack_34;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008453c0;
  local_10 = ExceptionList;
  uStack_34 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_34;
  ExceptionList = &local_10;
  Getal(&local_15);
  uVar1 = allocate(param_2);
  local_8 = 0;
  FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
            (*param_1,param_1[1],uVar1);
  FUN_00423fe5();
  return;
}

