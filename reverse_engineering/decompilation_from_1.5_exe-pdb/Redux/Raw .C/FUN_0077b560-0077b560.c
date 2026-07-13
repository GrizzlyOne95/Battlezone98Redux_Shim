
uint FUN_0077b560(int param_1)

{
  uint *puVar1;
  ColourValue *pCVar2;
  int iVar3;
  ushort in_FPUControlWord;
  float10 fVar4;
  undefined1 local_d0 [16];
  double local_c0;
  double local_b8;
  double local_b0;
  double local_a8;
  double local_a0;
  int local_98;
  undefined4 local_94;
  uint local_90;
  int local_8c;
  int local_88;
  uint local_84;
  uint local_80;
  uint local_7c;
  undefined4 local_78;
  undefined4 local_74;
  int local_70;
  uint local_6c;
  int local_68;
  uint local_64;
  uint local_60;
  int local_5c;
  uint local_58;
  int local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  undefined4 local_30;
  PixelBox *local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  ushort *local_c;
  ushort *local_8;
  
  local_2c = (PixelBox *)FUN_0077b370();
  if (local_2c == (PixelBox *)0x0) {
    local_64 = 0;
  }
  else {
    local_50 = FUN_0050cd60();
    local_54 = FUN_0050cd80();
    local_94 = FUN_0046b240();
    puVar1 = (uint *)_Min_value<>(&stack0x00000008,&local_94);
    local_64 = *puVar1;
    for (local_20 = 0; local_20 < local_64; local_20 = local_20 + 1) {
      local_30 = FUN_0050ce10(local_20);
      local_60 = local_50;
      local_a0 = (double)(int)local_50 + (double)(&DAT_008a2fd0)[-((int)local_50 >> 0x1f)];
      local_4c = FUN_008445c0();
      local_68 = local_54;
      local_b8 = (double)local_54 + (double)(&DAT_008a2fd0)[-(local_54 >> 0x1f)];
      local_48 = FUN_008445c0();
      local_6c = local_50;
      local_b0 = (double)(int)local_50 + (double)(&DAT_008a2fd0)[-((int)local_50 >> 0x1f)];
      local_44 = FUN_008445c0();
      local_70 = local_54;
      local_c0 = (double)local_54 + (double)(&DAT_008a2fd0)[-(local_54 >> 0x1f)];
      local_40 = FUN_008445c0();
      Ogre::ColourValue::ColourValue((ColourValue *)&local_1c,0.0,0.0,0.0,0.0);
      if ((local_4c < local_44) && (local_48 < local_40)) {
        for (local_28 = local_48; local_28 < local_40; local_28 = local_28 + 1) {
          for (local_24 = local_4c; local_24 < local_44; local_24 = local_24 + 1) {
            if (*(int *)(local_2c + 0x1c) == 0x11) {
              iVar3 = (local_28 >> 2) * (local_50 >> 2) + (local_24 >> 2);
              local_78 = *(undefined4 *)(*(int *)(local_2c + 0x18) + iVar3 * 8);
              local_74 = *(undefined4 *)(*(int *)(local_2c + 0x18) + 4 + iVar3 * 8);
              local_8 = (ushort *)&local_78;
              local_c = (ushort *)((int)&local_78 + 2);
              local_90 = __aullshr();
              local_90 = local_90 & 3;
              local_58 = local_90;
              switch(local_90) {
              case 0:
                local_1c = (float)(*local_8 >> 0xb) / 31.0 + local_1c;
                local_18 = (float)(*local_8 >> 5 & 0x3f) / 63.0 + local_18;
                local_14 = (float)(*local_8 & 0x1f) / 31.0 + local_14;
                local_10 = local_10 + 1.0;
                break;
              case 1:
                local_1c = (float)(ushort)((*local_c >> 0xb) + (*local_8 >> 0xb) * 2) / 93.0 +
                           local_1c;
                local_18 = (float)(ushort)((*local_c >> 5 & 0x3f) + (*local_8 >> 5 & 0x3f) * 2) /
                           189.0 + local_18;
                local_14 = (float)(ushort)((*local_c & 0x1f) + (*local_8 & 0x1f) * 2) / 93.0 +
                           local_14;
                local_10 = local_10 + 1.0;
                break;
              case 2:
                local_1c = (float)(ushort)((*local_8 >> 0xb) + (*local_c >> 0xb) * 2) / 93.0 +
                           local_1c;
                local_18 = (float)(ushort)((*local_8 >> 5 & 0x3f) + (*local_c >> 5 & 0x3f) * 2) /
                           189.0 + local_18;
                local_14 = (float)(ushort)((*local_8 & 0x1f) + (*local_c & 0x1f) * 2) / 93.0 +
                           local_14;
                local_10 = local_10 + 1.0;
                break;
              case 3:
                local_1c = (float)(*local_c >> 0xb) / 31.0 + local_1c;
                local_18 = (float)(*local_c >> 5 & 0x3f) / 63.0 + local_18;
                local_14 = (float)(*local_c & 0x1f) / 31.0 + local_14;
                local_10 = local_10 + 1.0;
              }
            }
            else {
              pCVar2 = (ColourValue *)
                       Ogre::PixelBox::getColourAt(local_2c,(uint)local_d0,local_24,local_28);
              Ogre::ColourValue::operator+=((ColourValue *)&local_1c,pCVar2);
            }
          }
        }
        local_5c = (local_44 - local_4c) * (local_40 - local_48);
        local_a8 = (double)local_5c + (double)(&DAT_008a2fd0)[-(local_5c >> 0x1f)];
        Ogre::ColourValue::operator/=((ColourValue *)&local_1c,(float)local_a8);
      }
      fVar4 = (float10)FUN_00461fd0(local_1c * 255.0 + 0.5);
      local_84 = in_FPUControlWord | 0xc00;
      local_98 = (int)ROUND(fVar4);
      *(undefined1 *)(param_1 + local_20 * 3) = (undefined1)local_98;
      fVar4 = (float10)FUN_00461fd0(local_18 * 255.0 + 0.5);
      local_7c = in_FPUControlWord | 0xc00;
      local_8c = (int)ROUND(fVar4);
      *(undefined1 *)(param_1 + 1 + local_20 * 3) = (undefined1)local_8c;
      fVar4 = (float10)FUN_00461fd0(local_14 * 255.0 + 0.5);
      local_80 = in_FPUControlWord | 0xc00;
      local_88 = (int)ROUND(fVar4);
      *(undefined1 *)(param_1 + 2 + local_20 * 3) = (undefined1)local_88;
    }
    FUN_0077b470();
  }
  return local_64;
}

