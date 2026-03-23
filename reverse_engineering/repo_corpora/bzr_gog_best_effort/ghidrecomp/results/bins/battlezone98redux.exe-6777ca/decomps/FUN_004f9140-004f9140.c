
undefined4 * __fastcall FUN_004f9140(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a897;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004d4980(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  Ogre::RenderQueueListener::RenderQueueListener((RenderQueueListener *)(param_1 + 10));
  local_8 = 0;
  FUN_004f9230();
  *param_1 = LensFlare::vftable;
  param_1[10] = LensFlare::vftable;
  param_1[0xb] = LensFlare::vftable;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0xc));
  local_8 = CONCAT31(local_8._1_3_,1);
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0xe));
  *(byte *)((int)param_1 + 0x25) = *(byte *)((int)param_1 + 0x25) & 0xfd;
  *(undefined1 *)(param_1 + 9) = 0x32;
  ExceptionList = local_10;
  return param_1;
}

