
void __thiscall
FUN_007ced10(int *param_1,undefined4 param_2,int param_3,uint param_4,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_5)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uStack_7c;
  undefined1 auStack_6c [4];
  int local_68;
  undefined1 local_61;
  undefined4 local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int *local_4c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_48 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [24];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00862800;
  local_10 = ExceptionList;
  uStack_7c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_7c;
  ExceptionList = &local_10;
  local_68 = (param_3 - *param_1) / 0x18;
  local_4c = param_1;
  local_18 = uStack_7c;
  puVar1 = &uStack_7c;
  if (param_4 != 0) {
    uVar2 = FUN_0066bde0();
    if (uVar2 < param_4) {
      iVar3 = FUN_0048a830();
      iVar4 = FID_conflict_max_size();
      if ((uint)(iVar4 - iVar3) < param_4) {
        FUN_00423e40();
      }
      iVar3 = FUN_0048a830();
      uVar5 = FID_conflict__Grow_to(iVar3 + param_4);
      local_60 = uVar5;
      Getal(&local_61);
      local_50 = allocate(uVar5);
      local_58 = (param_3 - *local_4c) / 0x18;
      local_54 = 0;
      local_8 = 0;
      uVar5 = FUN_00417780(param_5);
      FUN_007cf160(local_58 * 0x18 + local_50,param_4,uVar5);
      local_54 = local_54 + 1;
      FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                (*local_4c,param_3,local_50);
      local_54 = local_54 + 1;
      FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                (param_3,local_4c[1],(local_58 + param_4) * 0x18 + local_50);
      FUN_007ceeb9();
      return;
    }
    if ((uint)((local_4c[1] - param_3) / 0x18) < param_4) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,param_5)
      ;
      local_8 = 2;
      FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                (param_3,local_4c[1],param_4 * 0x18 + param_3);
      local_8 = CONCAT31(local_8._1_3_,3);
      uVar5 = FUN_00417780(local_30);
      FUN_007cf160(local_4c[1],param_4 - (local_4c[1] - param_3) / 0x18,uVar5);
      FUN_007ceffe();
      return;
    }
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_48,param_5);
    local_8 = 5;
    local_5c = local_4c[1];
    iVar3 = FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                      (local_5c + param_4 * -0x18,local_5c,local_4c[1]);
    local_4c[1] = iVar3;
    FUN_00422c10(param_3,local_4c[1]);
    _Move<>(param_3,local_5c + param_4 * -0x18,local_5c);
    FUN_007cf1f0(param_3,param_4 * 0x18 + param_3,local_48);
    local_8 = 0xffffffff;
    ~basic_string<>();
    puVar1 = (uint *)local_14;
  }
  local_14 = (undefined1 *)puVar1;
  iVar3 = local_68;
  FID_conflict_begin(auStack_6c);
  FID_conflict_operator_(param_2,iVar3);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

