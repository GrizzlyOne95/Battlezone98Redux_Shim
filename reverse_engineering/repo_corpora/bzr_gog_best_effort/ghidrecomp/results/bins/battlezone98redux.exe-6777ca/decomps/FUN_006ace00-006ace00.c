
allocator<char> * __fastcall FUN_006ace00(allocator<char> *param_1)

{
  std::allocator<char>::allocator<char>(param_1);
  LOCK();
  UNLOCK();
  return param_1;
}

