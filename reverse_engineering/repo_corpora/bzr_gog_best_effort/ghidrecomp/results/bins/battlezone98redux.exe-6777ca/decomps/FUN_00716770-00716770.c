
shared_ptr<struct__EXCEPTION_RECORD_const_> * __thiscall
FUN_00716770(shared_ptr<struct__EXCEPTION_RECORD_const_> *param_1,undefined4 param_2,
            undefined4 param_3)

{
  shared_ptr<struct__EXCEPTION_RECORD_const_> *psVar1;
  undefined4 uVar2;
  
  psVar1 = (shared_ptr<struct__EXCEPTION_RECORD_const_> *)FUN_00417780(param_3);
  std::shared_ptr<struct__EXCEPTION_RECORD_const_>::shared_ptr<struct__EXCEPTION_RECORD_const_>
            (param_1,psVar1);
  uVar2 = FUN_00417780(param_2);
  FUN_007212a0(uVar2);
  return param_1;
}

