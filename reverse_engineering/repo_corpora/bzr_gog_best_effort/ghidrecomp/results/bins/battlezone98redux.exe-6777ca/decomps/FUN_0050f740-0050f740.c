
void __thiscall
FUN_0050f740(undefined4 param_1,PixelBox *param_2,float param_3,float param_4,float param_5,
            float param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined2 *puVar6;
  byte *pbVar7;
  uint uVar8;
  float fVar9;
  float fVar10;
  float local_28;
  float local_24;
  int local_1c;
  int local_18;
  undefined1 *local_14;
  undefined1 local_10 [5];
  undefined2 local_b;
  byte local_9;
  undefined2 local_8;
  byte local_6;
  
  iVar1 = *(int *)(param_2 + 8);
  iVar2 = *(int *)param_2;
  iVar3 = *(int *)(param_2 + 0xc);
  iVar4 = *(int *)(param_2 + 4);
  fVar9 = (param_5 - param_3) * DAT_02cc50e4;
  fVar10 = (param_4 - param_6) * DAT_02cc50e4;
  local_14 = *(undefined1 **)(param_2 + 0x18);
  local_28 = param_6 * DAT_02cc50e4;
  for (local_18 = 0; local_18 < iVar3 - iVar4; local_18 = local_18 + 1) {
    local_24 = param_3 * DAT_02cc50e4;
    for (local_1c = 0; local_1c < iVar1 - iVar2; local_1c = local_1c + 1) {
      uVar5 = FUN_00780dc0((int)local_24,(int)local_28,param_1);
      puVar6 = (undefined2 *)FUN_00780fd0(local_10,uVar5);
      local_b = *puVar6;
      local_9 = *(byte *)(puVar6 + 1);
      local_8 = local_b;
      local_6 = local_9;
      pbVar7 = (byte *)FUN_0050ce30((int)local_24,(int)local_28);
      uVar8 = (uint)*pbVar7;
      *local_14 = (char)((local_6 * uVar8) / 0xff);
      local_14[1] = (char)((local_8._1_1_ * uVar8) / 0xff);
      local_14[2] = (char)(((byte)local_8 * uVar8) / 0xff);
      local_14[3] = 0xff;
      local_14 = local_14 + 4;
      local_24 = local_24 + fVar9 / (float)(iVar1 - iVar2);
    }
    uVar8 = Ogre::PixelBox::getRowSkip(param_2);
    local_14 = local_14 + uVar8 * 4;
    local_28 = local_28 + fVar10 / (float)(iVar3 - iVar4);
  }
  return;
}

