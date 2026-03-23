
undefined4 __thiscall
FUN_007007c0(allocator<char> *param_1,undefined4 param_2,undefined4 param_3,char *param_4)

{
  Count *this;
  undefined4 local_1c;
  undefined4 local_18 [2];
  undefined4 local_10;
  undefined4 local_c;
  allocator<char> *local_8;
  
  local_8 = param_1;
  std::allocator<char>::allocator<char>(param_1 + 4);
  local_c = FUN_00705450(param_3);
  local_10 = FUN_006d4b50();
  FUN_006d4b70(param_4 + 4,&local_10);
  if (*param_4 == '\0') {
    FUN_006d0bb0();
  }
  local_18[0] = FUN_006d4b30();
  FUN_00705400(local_18,&local_c,param_4);
  this = (Count *)std::allocator<char>::allocator<char>(local_8);
  Concurrency::details::CollectionTypes::Count::Increment(this);
  local_1c = FUN_006d4b50();
  FUN_006d4b70(&local_c,&local_1c);
  return param_2;
}

