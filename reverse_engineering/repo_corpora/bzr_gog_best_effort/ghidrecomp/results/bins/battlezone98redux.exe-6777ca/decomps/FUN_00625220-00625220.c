
void FUN_00625220(int param_1,int param_2,uint param_3,int param_4)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  byte bVar4;
  
  puVar2 = (uint *)((param_3 >> 3) + param_2 & 0xfffffffc);
  iVar1 = param_3 + (param_2 - (int)puVar2) * 8;
  bVar4 = (byte)iVar1;
  if ((uint)(iVar1 + param_4) < 0x20) {
    uVar3 = (1 << ((char)param_4 + bVar4 & 0x1f)) - (1 << (bVar4 & 0x1f));
    *puVar2 = ~uVar3 & *puVar2 | param_1 << (bVar4 & 0x1f) & uVar3;
  }
  else {
    uVar3 = -1 << (bVar4 & 0x1f);
    *puVar2 = ~uVar3 & *puVar2 | param_1 << (bVar4 & 0x1f) & uVar3;
    uVar3 = (1 << ((bVar4 - 0x20) + (char)param_4 & 0x1f)) - 1;
    puVar2[1] = ~uVar3 & puVar2[1] | param_1 >> (0x20 - bVar4 & 0x1f) & uVar3;
  }
  return;
}

