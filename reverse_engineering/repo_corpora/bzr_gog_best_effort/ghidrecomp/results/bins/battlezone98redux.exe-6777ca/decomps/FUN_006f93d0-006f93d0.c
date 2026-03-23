
undefined4 * __thiscall FUN_006f93d0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  shared_ptr<struct__EXCEPTION_RECORD_const_> *psVar3;
  
  puVar2 = (undefined4 *)FUN_00417780(param_2);
  uVar1 = puVar2[1];
  *param_1 = *puVar2;
  param_1[1] = uVar1;
  psVar3 = (shared_ptr<struct__EXCEPTION_RECORD_const_> *)FUN_00417780(param_3);
  std::shared_ptr<struct__EXCEPTION_RECORD_const_>::shared_ptr<struct__EXCEPTION_RECORD_const_>
            ((shared_ptr<struct__EXCEPTION_RECORD_const_> *)(param_1 + 2),psVar3);
  return param_1;
}

