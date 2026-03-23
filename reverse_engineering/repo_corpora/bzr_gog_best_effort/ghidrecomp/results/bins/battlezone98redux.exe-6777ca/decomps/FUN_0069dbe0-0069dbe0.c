
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0069dbe0(int param_1)

{
  switch(*(undefined4 *)(param_1 + 4)) {
  case 0:
    _DAT_009310bc = "Schedule\\Mapgrid_Goal.cpp";
    _DAT_009310c0 = 0x152;
    FUN_006a5f50(0x800,"NO_GOAL");
    break;
  case 1:
    _DAT_009310bc = "Schedule\\Mapgrid_Goal.cpp";
    _DAT_009310c0 = 0x155;
    FUN_006a5f50(0x800,"DEFEND_BASE");
    break;
  case 2:
    _DAT_009310bc = "Schedule\\Mapgrid_Goal.cpp";
    _DAT_009310c0 = 0x158;
    FUN_006a5f50(0x800,"ATTACK_TROOPS");
    break;
  case 3:
    _DAT_009310bc = "Schedule\\Mapgrid_Goal.cpp";
    _DAT_009310c0 = 0x15b;
    FUN_006a5f50(0x800,"SEIGE");
    break;
  case 4:
    _DAT_009310bc = "Schedule\\Mapgrid_Goal.cpp";
    _DAT_009310c0 = 0x15e;
    FUN_006a5f50(0x800,"EXPLORATION");
    break;
  case 5:
    _DAT_009310bc = "Schedule\\Mapgrid_Goal.cpp";
    _DAT_009310c0 = 0x161;
    FUN_006a5f50(0x800,"SCRIPTED");
    break;
  case 6:
    _DAT_009310bc = "Schedule\\Mapgrid_Goal.cpp";
    _DAT_009310c0 = 0x164;
    FUN_006a5f50(0x800,"PERIMETER");
    break;
  case 7:
    _DAT_009310bc = "Schedule\\Mapgrid_Goal.cpp";
    _DAT_009310c0 = 0x167;
    FUN_006a5f50(0x800,"RECON_GOAL");
    break;
  case 8:
    _DAT_009310bc = "Schedule\\Mapgrid_Goal.cpp";
    _DAT_009310c0 = 0x16a;
    FUN_006a5f50(0x800,"RESOURCE_GOAL");
    break;
  default:
    _DAT_009310bc = "Schedule\\Mapgrid_Goal.cpp";
    _DAT_009310c0 = 0x16d;
    FUN_006a5f50(0x800,&DAT_008922f0);
  }
  return;
}

