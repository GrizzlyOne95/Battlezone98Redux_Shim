
/* WARNING: Removing unreachable block (ram,0x0081198e) */

undefined4 FUN_008118f0(undefined4 *param_1,undefined4 param_2,__ExceptionPtr *param_3)

{
  char cVar1;
  char *pcVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  undefined4 local_c;
  undefined1 local_5;
  
  local_c = *param_1;
  local_10 = 0;
  while ((cVar1 = FID_conflict_operator__(param_2), cVar1 != '\0' &&
         (pcVar2 = (char *)get(), *pcVar2 == '0'))) {
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &local_c);
    local_10 = local_10 + 1;
  }
  cVar1 = FID_conflict_operator__(param_2);
  if (cVar1 == '\0') {
    local_18 = 0;
    local_14 = 0;
    puVar4 = (undefined1 *)get();
    local_5 = *puVar4;
    cVar1 = FUN_00812500(local_5);
    if ((cVar1 == '\0') || (cVar1 = FUN_00812940(local_5,0,&local_14), cVar1 == '\0')) {
      if (local_10 == 0) {
        uVar3 = 0;
      }
      else {
        std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
                  ((shared_ptr<class___ExceptionPtr> *)&local_14,param_3);
        *param_1 = local_c;
        uVar3 = 1;
      }
    }
    else {
      std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
      operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                  *)&local_c);
      while (cVar1 = FID_conflict_operator__(param_2), cVar1 == '\0') {
        puVar4 = (undefined1 *)get();
        local_5 = *puVar4;
        cVar1 = FUN_00812500(local_5);
        if (cVar1 == '\0') break;
        cVar1 = FUN_00812940(local_5,local_10,&local_14);
        if (cVar1 == '\0') {
          std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
                    ((shared_ptr<class___ExceptionPtr> *)&local_14,param_3);
          return 0;
        }
        std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
        operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                    *)&local_c);
        local_10 = local_10 + 1;
        cVar1 = FID_conflict_operator__(param_2);
        if (cVar1 != '\0') break;
        puVar4 = (undefined1 *)get();
        local_5 = *puVar4;
        cVar1 = FUN_00812500(local_5);
        if (cVar1 == '\0') break;
        cVar1 = FUN_00812940(local_5,local_10,&local_14);
        if (cVar1 == '\0') {
          std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
                    ((shared_ptr<class___ExceptionPtr> *)&local_14,param_3);
          return 0;
        }
        std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
        operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                    *)&local_c);
        local_10 = local_10 + 1;
        cVar1 = FID_conflict_operator__(param_2);
        if (cVar1 != '\0') break;
        puVar4 = (undefined1 *)get();
        local_5 = *puVar4;
        cVar1 = FUN_00812500(local_5);
        if (cVar1 == '\0') break;
        cVar1 = FUN_00812940(local_5,local_10,&local_14);
        if (cVar1 == '\0') {
          std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
                    ((shared_ptr<class___ExceptionPtr> *)&local_14,param_3);
          return 0;
        }
        std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
        operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                    *)&local_c);
        local_10 = local_10 + 1;
      }
      std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
                ((shared_ptr<class___ExceptionPtr> *)&local_14,param_3);
      *param_1 = local_c;
      uVar3 = 1;
    }
  }
  else if (local_10 == 0) {
    uVar3 = 0;
  }
  else {
    local_1c = 0;
    std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
              ((shared_ptr<class___ExceptionPtr> *)&local_1c,param_3);
    *param_1 = local_c;
    uVar3 = 1;
  }
  return uVar3;
}

