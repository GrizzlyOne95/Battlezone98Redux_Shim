
void __thiscall FUN_006f7fc0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855790;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar2 = distance<>(param_2,param_3);
  cVar1 = FUN_0048aa40(uVar2);
  if (cVar1 != '\0') {
    local_8 = 0;
    uVar2 = FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                      (param_2,param_3,*param_1);
    param_1[1] = uVar2;
    FUN_006f8051();
    return;
  }
  ExceptionList = local_10;
  return;
}

