
undefined4 __thiscall
FUN_006cb330(allocator<char> *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = std::allocator<char>::allocator<char>(param_1);
  uVar2 = param_2;
  FUN_006cf300(param_2,uVar1,param_3,param_4);
  FUN_006cf880(uVar2,uVar1,param_3,param_4);
  return param_2;
}

