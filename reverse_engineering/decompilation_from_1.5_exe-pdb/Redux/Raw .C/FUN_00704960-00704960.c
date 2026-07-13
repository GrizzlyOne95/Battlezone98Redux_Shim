
shared_ptr<class___ExceptionPtr> * __thiscall
FUN_00704960(shared_ptr<class___ExceptionPtr> *param_1,shared_ptr<class___ExceptionPtr> *param_2)

{
  undefined4 uVar1;
  
  std::shared_ptr<class___ExceptionPtr>::operator=(param_1,param_2);
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_2 + 8);
  uVar1 = *(undefined4 *)(param_2 + 0x10);
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_2 + 0xc);
  *(undefined4 *)(param_1 + 0x10) = uVar1;
  return param_1;
}

