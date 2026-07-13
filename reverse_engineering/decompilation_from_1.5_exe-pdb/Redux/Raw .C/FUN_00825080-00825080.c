
/* WARNING: Removing unreachable block (ram,0x0082520b) */
/* WARNING: Removing unreachable block (ram,0x0082524a) */

void FUN_00825080(int *param_1,int param_2,uint param_3,uint param_4,uint param_5,code *param_6)

{
  char *_Source;
  int iVar1;
  undefined4 uVar2;
  uint local_17c;
  uint local_178;
  uint local_174;
  int local_16c;
  int aiStack_168 [80];
  char local_28 [8];
  undefined1 uStack_20;
  char local_18 [8];
  undefined1 uStack_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_5 != 0) {
    aiStack_168[0] = 0;
    for (local_178 = 0; local_178 < param_3; local_178 = local_178 + 1) {
      for (local_17c = 0; local_17c < param_4; local_17c = local_17c + 1) {
        for (local_174 = 0; local_174 < param_5; local_174 = local_174 + 1) {
          _Source = (char *)(local_174 * 0x78 + *param_1);
          if (local_178 == 0 && local_17c == 0) {
            local_16c = 0;
            iVar1 = _strnicmp(_Source + 0x38,"world",5);
            if (((iVar1 != 0) && (iVar1 = _strnicmp(_Source + 0x38,"null",4), iVar1 != 0)) &&
               (local_16c = FUN_00826b80(param_2,*(undefined4 *)(_Source + 0x38),
                                         *(undefined4 *)(_Source + 0x3c)), local_16c == 0)) {
              strncpy(local_18,_Source + 0x38,8);
              uStack_10 = 0;
              strncpy(local_28,_Source,8);
              uStack_20 = 0;
              FUN_007d6830("Can\'t find parent %s for object %s",local_18,local_28);
            }
            if (local_16c == 0) {
              local_16c = param_2;
            }
            local_16c = FUN_00825650(local_16c,_Source,_Source,0);
            if (local_16c == 0) goto LAB_008253e1;
            aiStack_168[local_174] = local_16c;
            if (param_6 != (code *)0x0) {
              (*param_6)(local_16c,param_2);
            }
          }
          else {
            local_16c = aiStack_168[local_174];
          }
          if (((((*(int *)(local_16c + 8) != 0 || *(int *)(local_16c + 0xc) != 0) &&
                (*(int *)(local_16c + 0x84) != 0x28)) &&
               ((*(int *)(local_16c + 0x84) != 0x46 &&
                ((*(int *)(local_16c + 0x84) != 0x47 && (*(int *)(local_16c + 0x84) != 0x48)))))) &&
              (*(int *)(local_16c + 0x84) != 0x49)) &&
             ((*(int *)(local_16c + 0x84) != 0x4a && (*(int *)(local_16c + 0x84) != 0x26)))) {
            uVar2 = FUN_00824ad0(*(undefined4 *)(local_16c + 8),*(undefined4 *)(local_16c + 0xc),
                                 &DAT_0087a428,local_17c,local_178);
            FUN_004e3290(local_16c,uVar2);
          }
        }
        param_1 = param_1 + 1;
      }
    }
  }
LAB_008253e1:
  FUN_0083e885();
  return;
}

