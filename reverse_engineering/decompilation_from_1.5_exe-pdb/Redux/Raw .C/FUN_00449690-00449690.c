
void __thiscall FUN_00449690(int param_1,undefined4 param_2)

{
  ColourValue *this;
  float10 fVar1;
  ColourValue local_28 [16];
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  int local_8;
  
  local_8 = param_1;
  fVar1 = (float10)FUN_00448e60(*(undefined4 *)(param_1 + 0x14c),*(undefined4 *)(param_1 + 0x15c),
                                param_2);
  local_18 = (float)fVar1;
  fVar1 = (float10)FUN_00448e60(*(undefined4 *)(local_8 + 0x150),*(undefined4 *)(local_8 + 0x160),
                                param_2);
  local_14 = (float)fVar1;
  fVar1 = (float10)FUN_00448e60(*(undefined4 *)(local_8 + 0x154),*(undefined4 *)(local_8 + 0x164),
                                param_2);
  local_10 = (float)fVar1;
  fVar1 = (float10)FUN_00448e60(*(undefined4 *)(local_8 + 0x158),*(undefined4 *)(local_8 + 0x168),
                                param_2);
  local_c = (float)fVar1;
  this = (ColourValue *)Ogre::ColourValue::ColourValue(local_28,local_18,local_14,local_10,local_c);
  Ogre::ColourValue::getAsARGB(this);
  return;
}

