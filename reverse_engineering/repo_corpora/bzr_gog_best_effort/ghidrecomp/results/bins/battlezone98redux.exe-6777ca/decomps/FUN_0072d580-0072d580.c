
/* WARNING: Removing unreachable block (ram,0x0072d5c3) */

undefined4 FUN_0072d580(void)

{
  undefined4 uVar1;
  Count *this;
  undefined4 local_10;
  int local_c;
  allocator<char> *local_8;
  
  local_10 = FUN_006d4b30();
  local_c = FUN_0072d670(&local_10);
  if (local_c == 0) {
    uVar1 = 0;
  }
  else {
    this = (Count *)std::allocator<char>::allocator<char>(local_8);
    Concurrency::details::CollectionTypes::Count::Decrement(this);
    std::allocator<char>::allocator<char>(local_8 + 4);
    uVar1 = FUN_006d7740(&local_c);
  }
  return uVar1;
}

