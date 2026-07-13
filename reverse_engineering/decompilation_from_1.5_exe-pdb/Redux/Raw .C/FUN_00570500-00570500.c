
void __thiscall
FUN_00570500(int param_1,undefined4 param_2,ushort param_3,ushort *param_4,uint param_5)

{
  ushort uVar1;
  undefined1 uVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  ushort *puVar7;
  char local_1a9;
  ushort local_1a8;
  char local_198 [300];
  char local_6c [100];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00822e60();
  *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) & 0xfffffff7;
  *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) & 0xfffffffd;
  *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) & 0xfffffffb;
  *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) & 0xfffffffe;
  DAT_025cfa1c = DAT_008e9078;
  DAT_009183f4 = 0;
  DAT_009454b8 = 0;
  FUN_00822e60();
  if (*param_4 == 0x5050) {
    if (DAT_009180d4 != 0) {
      uVar4 = FUN_00822e10(0);
      **(undefined4 **)(param_1 + 0x858) = uVar4;
      **(undefined4 **)(param_1 + 0x85c) = *(undefined4 *)(param_4 + 1);
      uVar2 = FUN_00577840();
      **(undefined1 **)(param_1 + 0x860) = uVar2;
      if (DAT_009180d8 != 0) {
        uVar4 = FUN_0081e820("PING RECEIVED: mst %lu srt %lu\n",**(undefined4 **)(param_1 + 0x85c),
                             **(undefined4 **)(param_1 + 0x858));
        FUN_0081e710(uVar4);
      }
      FUN_007596b0(param_3,param_1 + 0x839,0xe,0);
    }
    cVar3 = FUN_0056fc40(param_3);
    if ((cVar3 != '\0') && ((*(int *)(param_4 + 3) != 0 || (*(int *)(param_4 + 9) != 0)))) {
      FUN_00822db0(*(undefined4 *)(param_4 + 3),*(undefined4 *)(param_4 + 9),
                   *(undefined4 *)(param_4 + 5));
    }
  }
  else if (*param_4 == 0x4147) {
    if (DAT_009180d4 != 0) {
      uVar4 = FUN_00822e10(0);
      **(undefined4 **)(param_1 + 0x858) = uVar4;
      **(undefined4 **)(param_1 + 0x85c) = *(undefined4 *)(param_4 + 1);
      uVar2 = FUN_00577840();
      **(undefined1 **)(param_1 + 0x860) = uVar2;
      if (DAT_009180d8 != 0) {
        uVar4 = FUN_0081e820("PING RECEIVED: mst %lu srt %lu\n",**(undefined4 **)(param_1 + 0x85c),
                             **(undefined4 **)(param_1 + 0x858));
        FUN_0081e710(uVar4);
      }
      FUN_007596b0(param_3,param_1 + 0x839,0xe,0);
    }
    cVar3 = FUN_0056fc40(param_3);
    if (cVar3 != '\0') {
      local_1a8 = 0;
      while ((local_1a8 < (byte)param_4[5] && (DAT_009180d4 != param_4[(uint)local_1a8 * 6 + 7]))) {
        local_1a8 = local_1a8 + 1;
      }
      if ((local_1a8 < (byte)param_4[5]) &&
         ((*(int *)(param_4 + (uint)local_1a8 * 6 + 9) != 0 ||
          (*(int *)(param_4 + (uint)local_1a8 * 6 + 0xb) != 0)))) {
        FUN_00822db0(*(undefined4 *)(param_4 + (uint)local_1a8 * 6 + 9),
                     *(undefined4 *)(param_4 + (uint)local_1a8 * 6 + 0xb),
                     *(undefined4 *)(param_4 + 3));
      }
    }
  }
  iVar5 = FUN_005771b0(param_3);
  if (iVar5 != 0) {
    if ((char)*param_4 == '_') {
      if (((param_3 != DAT_009180d4) && (*(int *)(param_1 + 8) == 4)) &&
         (iVar5 = FUN_0045ca50(), iVar5 != 0)) {
        uVar4 = *(undefined4 *)(param_4 + 1);
        uVar6 = (uint)*(byte *)((int)param_4 + 1);
        iVar5 = (param_5 - 6) - uVar6;
        if (uVar6 != 0) {
          FUN_00584620(param_4 + 3,uVar6,param_3,6);
        }
        FUN_00576820(param_3);
        if (0 < iVar5) {
          FUN_004b7750(param_3,(char *)((int)(param_4 + 3) + uVar6),iVar5,uVar4);
        }
      }
    }
    else {
      uVar1 = *param_4;
      if (uVar1 < 0x5348) {
        if (uVar1 == 0x5347) {
          if (DAT_00917f4c == '\0') {
            DAT_00917f4c = '\x01';
            FUN_005d48b0();
          }
        }
        else if (uVar1 < 0x4b4e) {
          if (uVar1 == 0x4b4d) {
            if ((param_3 != DAT_009180d4) && (*(int *)(param_1 + 8) == 4)) {
              FUN_00626130((int)(char)param_4[1],(int)*(char *)((int)param_4 + 3),(char)param_4[2],
                           (int)*(char *)((int)param_4 + 5));
            }
          }
          else if (uVar1 < 0x4351) {
            if (uVar1 == 0x4350) {
              if ((((param_3 != DAT_009180d4) && (*(int *)(param_1 + 8) == 4)) &&
                  (iVar5 = FUN_005771b0(param_3), iVar5 != 0)) && (*(char *)(iVar5 + 0x8e) == '\0'))
              {
                uVar4 = FUN_0041f870(param_5 - 2,param_4 + 1);
                _snprintf(local_198,300,"<%.*s> %.*s",0x20,uVar4);
                FUN_00624550(param_3,local_198);
              }
            }
            else if (uVar1 == 0x414b) {
              FUN_005773f0(param_3);
            }
            else if (uVar1 == 0x4250) {
              FUN_00571d00(param_4 + 1,param_5 - 2);
            }
            else if (((uVar1 == 0x4341) && (param_3 != DAT_009180d4)) &&
                    ((*(int *)(param_1 + 8) == 4 && (*(int *)(param_4 + 1) != DAT_02a13bb0)))) {
              iVar5 = FUN_005779d0(param_3);
              if (iVar5 == 0) {
                FUN_0056fcb0("\'unknown\' MAY BE CHEATING");
              }
              else {
                FUN_0056fcb0("%s MAY BE CHEATING",iVar5);
              }
            }
          }
          else if (uVar1 == 0x4752) {
            if ((param_3 != DAT_009180d4) && (*(int *)(param_1 + 8) == 4)) {
              FUN_005aa2b0(param_4 + 1,param_5 - 2);
            }
          }
          else if (uVar1 == 0x4b41) {
            if (DAT_00917f4c == '\0') {
              DAT_00917f4c = '\x01';
              FUN_005d48b0();
            }
          }
          else if ((uVar1 == 0x4b4b) && (DAT_00917f4c == '\0')) {
            DAT_00917f4c = '\x01';
            FUN_005d48b0();
          }
        }
        else if (uVar1 < 0x4f53) {
          if (uVar1 == 0x4f52) {
            if ((((param_3 != DAT_009180d4) && (*(int *)(param_1 + 8) == 4)) &&
                (param_3 != DAT_009180d4)) &&
               ((*(int *)(param_1 + 8) == 4 && (iVar5 = FUN_0045ca50(), iVar5 != 0)))) {
              FUN_00584620(param_4 + 1,param_5 - 2,param_3);
            }
          }
          else if (uVar1 == 0x4b50) {
            if ((*(int *)(param_1 + 8) == 4) && (iVar5 = FUN_0045ca50(), iVar5 != 0)) {
              FUN_00625f90();
            }
          }
          else if (uVar1 == 0x4d47) {
            if (((param_3 != DAT_009180d4) && (*(int *)(param_1 + 8) == 4)) &&
               (iVar5 = FUN_0045ca50(), iVar5 != 0)) {
              FUN_004b7780(param_3,param_4 + 1,param_5 - 2);
            }
          }
          else if (((uVar1 == 0x4f50) && (FUN_00576820(param_3), param_3 != DAT_009180d4)) &&
                  ((*(int *)(param_1 + 8) == 4 && (iVar5 = FUN_0045ca50(), iVar5 != 0)))) {
            FUN_004b7710(param_3,param_4 + 1,param_5 - 2);
          }
        }
        else if (uVar1 == 0x5250) {
          if (0xd < param_5) {
            uVar4 = FUN_00822e10(1);
            FUN_00571e20(param_3,param_4 + 1,uVar4);
          }
        }
        else if ((uVar1 == 0x5341) && (3 < param_5)) {
          iVar5 = FUN_00764760();
          if ((iVar5 != 0) && (iVar5 = FUN_00746720(param_4[1]), iVar5 != 0)) {
            *(undefined1 *)(iVar5 + 0x61) = 1;
          }
          iVar5 = FUN_005771b0(param_4[1]);
          if (iVar5 != 0) {
            uVar4 = FUN_0041f870();
            uVar4 = FUN_0081cb40("multi_message","host_autokicked",uVar4);
            FUN_0056fcb0(uVar4);
            if (iVar5 != 0) {
              FUN_005715a0(1);
            }
          }
        }
      }
      else if (uVar1 < 0x5371) {
        if (uVar1 == 0x5370) {
          if (((param_3 != DAT_009180d4) && (*(int *)(param_1 + 8) == 4)) &&
             ((iVar5 = FUN_005771b0(param_3), iVar5 != 0 && (*(char *)(iVar5 + 0x8e) == '\0')))) {
            uVar4 = FUN_0041f870(param_5 - 2,param_4 + 1);
            sprintf(local_6c,"<From: %.*s> %.*s",0x20,uVar4);
            FUN_00624550(param_3,local_6c);
          }
        }
        else {
          switch(uVar1) {
          case 0x534b:
            if (3 < param_5) {
              iVar5 = FUN_00764760();
              if ((iVar5 != 0) && (iVar5 = FUN_00746720(param_4[1]), iVar5 != 0)) {
                *(undefined1 *)(iVar5 + 0x61) = 1;
              }
              iVar5 = FUN_005771b0(param_4[1]);
              if (iVar5 != 0) {
                uVar4 = FUN_0041f870();
                uVar4 = FUN_0081cb40("multi_message","host_kicked",uVar4);
                FUN_0056fcb0(uVar4);
                if (iVar5 != 0) {
                  FUN_005715a0(1);
                }
              }
            }
            break;
          case 0x534c:
            if ((param_3 != DAT_009180d4) && (*(int *)(param_1 + 8) == 4)) {
              uVar4 = FUN_0081cb40("multi_message","locked");
              FUN_0056fcb0(&DAT_00879854,uVar4);
            }
            break;
          case 0x5350:
            FUN_00571c70(param_4 + 1);
            break;
          case 0x5353:
            local_1a9 = '\0';
            if (2 < param_5) {
              local_1a9 = (char)param_4[1];
            }
            cVar3 = FUN_00577360(param_3,local_1a9);
            if (cVar3 != '\0') {
              FUN_00573c60(param_3);
            }
            break;
          case 0x5355:
            if ((param_3 != DAT_009180d4) && (*(int *)(param_1 + 8) == 4)) {
              uVar4 = FUN_0081cb40("multi_message","unlocked");
              FUN_0056fcb0(&DAT_00879854,uVar4);
            }
          }
        }
      }
      else if (uVar1 < 0x6f79) {
        if (uVar1 == 0x6f78) {
          if ((param_3 != DAT_009180d4) && (*(int *)(param_1 + 8) == 4)) {
            FUN_00584c40(param_4 + 1,param_5 - 2,param_3,0x3e4ccccd);
          }
        }
        else if (uVar1 == 0x5450) {
          if ((param_3 != DAT_009180d4) && (*(int *)(param_1 + 8) == 4)) {
            FUN_004f6ae0(*(undefined4 *)(param_4 + 1),0x78,0x3c);
          }
        }
        else if (uVar1 == 0x616c) {
          if ((param_3 != DAT_009180d4) && (*(int *)(param_1 + 8) == 4)) {
            puVar7 = param_4 + 1;
            param_4 = param_4 + 3;
            if ((0 < *(int *)puVar7) &&
               (((*(int *)puVar7 < 0x10 && (0 < *(int *)param_4)) && (*(int *)param_4 < 0x10)))) {
              FUN_005e0bc0(*(undefined4 *)puVar7);
              FUN_005e12b0(*(undefined4 *)param_4);
            }
          }
        }
        else if (((uVar1 == 0x6f69) && (param_3 != DAT_009180d4)) && (*(int *)(param_1 + 8) == 4)) {
          FUN_00584c40(param_4 + 1,param_5 - 2,param_3,0);
        }
      }
      else if (uVar1 == 0x736e) {
        if ((param_3 != DAT_009180d4) && (*(int *)(param_1 + 8) == 4)) {
          FUN_00573ae0(param_3,param_4 + 1);
        }
      }
      else if (uVar1 == 0x756c) {
        if ((param_3 != DAT_009180d4) && (*(int *)(param_1 + 8) == 4)) {
          puVar7 = param_4 + 1;
          param_4 = param_4 + 3;
          if ((0 < *(int *)puVar7) &&
             (((*(int *)puVar7 < 0x10 && (0 < *(int *)param_4)) && (*(int *)param_4 < 0x10)))) {
            FUN_005e0bc0(*(undefined4 *)puVar7);
            FUN_005e12e0(*(undefined4 *)param_4);
          }
        }
      }
      else if (((uVar1 == 0x7878) && (param_3 != DAT_009180d4)) && (*(int *)(param_1 + 8) == 4)) {
        FUN_00584bb0(param_4 + 1,param_5 - 2,param_3);
      }
    }
  }
  FUN_0083e885();
  return;
}

