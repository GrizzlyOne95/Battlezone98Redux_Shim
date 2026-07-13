
void FUN_0068f8f0(void)

{
  FUN_006a5fd0("AI::AI_Close Begins");
  if (DAT_00930f08 == 0) {
    FUN_006a5fd0("AI::AI_Close CALLED WITHOUT MATCHING OPEN !!!");
  }
  else {
    DAT_00930f08 = 0;
    if (DAT_00920f04 != 0) {
      FUN_006a8e80(DAT_00920f04);
      DAT_00920f04 = 0;
      FUN_00692fd0();
      std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>();
    }
  }
  FUN_006990e0();
  FUN_006a5fd0("AI::AI_Close Ends");
  return;
}

