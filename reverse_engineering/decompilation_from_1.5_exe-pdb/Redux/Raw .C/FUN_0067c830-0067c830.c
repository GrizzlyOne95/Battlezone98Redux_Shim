
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0067c830(undefined4 param_1)

{
  char cVar1;
  void *pvVar2;
  float10 fVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  DAT_00920e94 = 0;
  _DAT_00920c9c = 0;
  pvVar2 = operator_new(0x58);
  if (pvVar2 != (void *)0x0) {
    FUN_00663990();
  }
  DAT_00920ea0 = FUN_0044d2a0();
  basic_string<>(param_1);
  cVar1 = FUN_00663ed0();
  basic_string<>("Onyx2015 Renderer initialized!");
  Ogre::Log::logMessage(*(Log **)(DAT_00920ea0 + 0x28),local_20,2,false);
  ~basic_string<>();
  DAT_00920e9c = 0.0;
  if (cVar1 != '\0') {
    fVar3 = (float10)FUN_0067cf50();
    DAT_00920e9c = (float)fVar3;
  }
  _DAT_008ed0e0 = DAT_00920e9c - 0.5;
  FUN_0083e885();
  return;
}

