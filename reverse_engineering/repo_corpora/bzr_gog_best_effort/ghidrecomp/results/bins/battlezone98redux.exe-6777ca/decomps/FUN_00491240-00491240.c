
void FUN_00491240(void)

{
  longlong lVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  char *pcVar6;
  char *pcVar7;
  char local_50 [4];
  undefined4 local_4c;
  char *local_48;
  int local_44;
  int local_3c;
  int local_38;
  undefined1 local_34 [16];
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008493a8;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_48 = "chunk.odf";
  local_14 = uVar2;
  FUN_00589430("chunk.odf");
  local_8 = 0;
  FUN_0047b6c0(0xf7d2616f,0x88f1ef89,local_34,"bsmoke.0");
  uVar3 = FUN_0068bed0(local_34,uVar2);
  *(undefined4 *)(local_38 + 0x8030) = uVar3;
  FUN_00589760(0xf7d2616f,0xdd33060c,local_38 + 0x8034,0x10);
  FUN_00589800(0xf7d2616f,0x567840fc,local_38 + 0x8038,0x3fcccccd);
  FUN_00589800(0xf7d2616f,&DAT_01f6a810,local_38 + 0x803c,0x3dcccccd);
  FUN_00589800(0xf7d2616f,0x8566cba4,local_38 + 0x8040,0x3f4ccccd);
  FUN_00589800(0xf7d2616f,0xbb8ad7d1,local_38 + 0x8044,0x3fc00000);
  FUN_00589800(0xf7d2616f,0x40a86add,local_38 + 0x8048,0x3f000000);
  *(undefined4 *)(local_38 + 0x8028) = 0;
  local_44 = FUN_0062ccc0(0,"fun3d\\ChunkEffect.cpp");
  builtin_strncpy((char *)(local_44 + 8),"chun",4);
  *(undefined4 *)(local_44 + 0xc) = 0x6b;
  *(undefined4 *)(local_44 + 0x14) = 0x101;
  *(undefined4 *)(local_44 + 0x84) = 0x35;
  *(undefined4 *)(local_44 + 0x88) = 0;
  *(undefined4 *)(local_44 + 0x7c) = 0;
  *(undefined4 *)(local_44 + 0x80) = 0;
  uVar3 = FUN_0062c4a0(local_44,0,0,0);
  *(undefined4 *)(local_38 + 0x804c) = uVar3;
  FUN_00589760(0xf7d2616f,0x26c0023a,local_38 + 0x8054,2);
  lVar1 = (ulonglong)*(uint *)(local_38 + 0x8054) * 4;
  local_4c = FUN_0083d92c(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
  *(undefined4 *)(local_38 + 0x8050) = local_4c;
  for (local_3c = 0; local_3c < *(int *)(local_38 + 0x8054); local_3c = local_3c + 1) {
    sprintf(local_50,"%d",local_3c + 1);
    sprintf(local_24,"chunk%d.geo",local_3c + 1);
    pcVar7 = local_24;
    pcVar6 = local_24;
    uVar3 = FUN_00446460(local_50,0x3acf08fb,pcVar6,pcVar7);
    FUN_0047b6c0(0xf7d2616f,uVar3,pcVar6,pcVar7);
    uVar3 = FUN_0062ccc0(0,"fun3d\\ChunkEffect.cpp");
    *(undefined4 *)(*(int *)(local_38 + 0x8050) + local_3c * 4) = uVar3;
    iVar4 = FUN_004e3290(*(undefined4 *)(*(int *)(local_38 + 0x8050) + local_3c * 4),local_24,0,0);
    if (iVar4 == 0) {
      FUN_007d6b70("ChunkEffect \"%s\" could not add geometry \"%s\"\n",local_48,local_24);
    }
    FUN_0062e650(*(undefined4 *)(*(int *)(local_38 + 0x8050) + local_3c * 4),
                 *(int *)(*(int *)(local_38 + 0x8050) + local_3c * 4) + 0xb0,
                 *(int *)(*(int *)(local_38 + 0x8050) + local_3c * 4) + 0xbc);
    *(float *)(*(int *)(*(int *)(local_38 + 0x8050) + local_3c * 4) + 0xa0) =
         (*(float *)(*(int *)(*(int *)(local_38 + 0x8050) + local_3c * 4) + 0xb0) +
         *(float *)(*(int *)(*(int *)(local_38 + 0x8050) + local_3c * 4) + 0xbc)) * 0.5;
    *(float *)(*(int *)(*(int *)(local_38 + 0x8050) + local_3c * 4) + 0xa4) =
         (*(float *)(*(int *)(*(int *)(local_38 + 0x8050) + local_3c * 4) + 0xb4) +
         *(float *)(*(int *)(*(int *)(local_38 + 0x8050) + local_3c * 4) + 0xc0)) * 0.5;
    *(float *)(*(int *)(*(int *)(local_38 + 0x8050) + local_3c * 4) + 0xa8) =
         (*(float *)(*(int *)(*(int *)(local_38 + 0x8050) + local_3c * 4) + 0xb8) +
         *(float *)(*(int *)(*(int *)(local_38 + 0x8050) + local_3c * 4) + 0xc4)) * 0.5;
    iVar4 = *(int *)(*(int *)(local_38 + 0x8050) + local_3c * 4);
    fVar5 = (float10)FUN_0062e590(*(undefined4 *)(*(int *)(local_38 + 0x8050) + local_3c * 4),
                                  *(undefined4 *)(iVar4 + 0xa0),*(undefined4 *)(iVar4 + 0xa4),
                                  *(undefined4 *)(iVar4 + 0xa8));
    *(float *)(*(int *)(*(int *)(local_38 + 0x8050) + local_3c * 4) + 0xac) = (float)fVar5;
  }
  local_8 = 0xffffffff;
  FUN_00589530();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

