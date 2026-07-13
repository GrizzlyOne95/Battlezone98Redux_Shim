
void FUN_006860d0(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined1 local_2c [16];
  Vector3 local_1c [12];
  int local_10;
  int local_c;
  int local_8;
  
  local_10 = (**(code **)(*DAT_00920edc + 0x164))();
  FUN_00684e50(local_2c,param_3);
  for (local_8 = 0; local_8 < param_2; local_8 = local_8 + 1) {
    uVar1 = Ogre::Vector3::Vector3
                      (local_1c,*(float *)(param_1 + local_8 * 0x18),
                       *(float *)(param_1 + 4 + local_8 * 0x18),
                       -*(float *)(param_1 + 8 + local_8 * 0x18));
    (**(code **)(*DAT_00920edc + 0x120))(uVar1);
    (**(code **)(*DAT_00920edc + 0x148))
              (*(undefined4 *)(param_1 + 0xc + local_8 * 0x18),
               *(undefined4 *)(param_1 + 0x10 + local_8 * 0x18));
    (**(code **)(*DAT_00920edc + 0x154))(local_2c);
  }
  for (local_c = 2; local_c < param_2; local_c = local_c + 1) {
    (**(code **)(*DAT_00920edc + 0x15c))(local_10,local_10 + -1 + local_c,local_10 + local_c);
  }
  return;
}

