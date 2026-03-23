
undefined4 * FUN_007fbd90(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  uint uStack_38;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 *local_1c;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864420;
  local_10 = ExceptionList;
  uStack_38 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_38;
  ExceptionList = &local_10;
  puVar5 = &local_15;
  Getal(&local_16);
  uVar2 = select_on_container_copy_construction(puVar5);
  _Vector_alloc<>(uVar2);
  uVar2 = size();
  cVar1 = FUN_0048aa40(uVar2);
  if (cVar1 != '\0') {
    local_8 = 0;
    uVar2 = *local_1c;
    puVar3 = (undefined4 *)FUN_0041fc60(local_24);
    uVar4 = *puVar3;
    puVar3 = (undefined4 *)FUN_0041fc00(local_28);
    local_20 = FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                         (*puVar3,uVar4,uVar2);
    local_1c[1] = local_20;
    puVar3 = (undefined4 *)FUN_007fbe4f();
    return puVar3;
  }
  ExceptionList = local_10;
  return local_1c;
}

