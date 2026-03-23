
/* WARNING: Removing unreachable block (ram,0x00811609) */
/* WARNING: Removing unreachable block (ram,0x0081161c) */
/* WARNING: Removing unreachable block (ram,0x0081162c) */
/* WARNING: Removing unreachable block (ram,0x00811635) */
/* WARNING: Removing unreachable block (ram,0x00811661) */

bool FUN_008115f0(undefined4 *param_1,undefined4 param_2,__ExceptionPtr *param_3)

{
  char cVar1;
  undefined1 *puVar2;
  bool bVar3;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  undefined1 local_5;
  
  local_c = *param_1;
  local_14 = 0;
  local_1c = *(undefined4 *)param_3;
  local_18 = *(undefined4 *)(param_3 + 4);
  local_10 = 0;
  while ((cVar1 = operator==<>(local_10 + local_14), cVar1 != '\0' &&
         (cVar1 = FID_conflict_operator__(param_2), cVar1 == '\0'))) {
    puVar2 = (undefined1 *)get();
    local_5 = *puVar2;
    cVar1 = FUN_00812500(local_5);
    if (cVar1 == '\0') break;
    cVar1 = FUN_008125f0(local_5,local_10,&local_1c);
    if (cVar1 == '\0') {
      *param_1 = local_c;
      std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
                ((shared_ptr<class___ExceptionPtr> *)&local_1c,param_3);
      return true;
    }
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &local_c);
    local_10 = local_10 + 1;
    cVar1 = operator==<>(local_10 + local_14);
    if ((cVar1 == '\0') || (cVar1 = FID_conflict_operator__(param_2), cVar1 != '\0')) break;
    puVar2 = (undefined1 *)get();
    local_5 = *puVar2;
    cVar1 = FUN_00812500(local_5);
    if (cVar1 == '\0') break;
    cVar1 = FUN_008125f0(local_5,local_10,&local_1c);
    if (cVar1 == '\0') {
      *param_1 = local_c;
      std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
                ((shared_ptr<class___ExceptionPtr> *)&local_1c,param_3);
      return true;
    }
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &local_c);
    local_10 = local_10 + 1;
    cVar1 = operator==<>(local_10 + local_14);
    if ((cVar1 == '\0') || (cVar1 = FID_conflict_operator__(param_2), cVar1 != '\0')) break;
    puVar2 = (undefined1 *)get();
    local_5 = *puVar2;
    cVar1 = FUN_00812500(local_5);
    if (cVar1 == '\0') break;
    cVar1 = FUN_008125f0(local_5,local_10,&local_1c);
    if (cVar1 == '\0') {
      *param_1 = local_c;
      std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
                ((shared_ptr<class___ExceptionPtr> *)&local_1c,param_3);
      return true;
    }
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &local_c);
    local_10 = local_10 + 1;
  }
  bVar3 = local_10 + local_14 != 0;
  if (bVar3) {
    std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
              ((shared_ptr<class___ExceptionPtr> *)&local_1c,param_3);
    *param_1 = local_c;
  }
  return bVar3;
}

