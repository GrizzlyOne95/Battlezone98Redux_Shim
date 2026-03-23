
bool __thiscall
FUN_00816c50(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4,
            undefined1 *param_5,__ExceptionPtr *param_6)

{
  shared_ptr<class___ExceptionPtr> *psVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
            (param_2,param_3,*param_5,param_1);
  uVar2 = 0;
  uVar3 = *param_3;
  get(param_2,uVar3,0);
  psVar1 = (shared_ptr<class___ExceptionPtr> *)FUN_00816d90(param_2,uVar3,uVar2);
  if (psVar1 != (shared_ptr<class___ExceptionPtr> *)0x0) {
    std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>(psVar1,param_6);
  }
  return psVar1 != (shared_ptr<class___ExceptionPtr> *)0x0;
}

