/*
 * Entry: 00514151
 * Name: Mapgrid_Goal::Display_Goal_Type
 * Namespace: Mapgrid_Goal
 * Signature: void Display_Goal_Type(Mapgrid_Goal * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Mapgrid_Goal::Display_Goal_Type(Mapgrid_Goal *this)

{
  char *pcVar1;
  
  switch(this->_padding_) {
  case 0:
    _tlog_line = 0x16c;
    pcVar1 = "NO_GOAL";
    break;
  case 1:
    _tlog_line = 0x16f;
    pcVar1 = "DEFEND_BASE";
    break;
  case 2:
    _tlog_line = 0x172;
    pcVar1 = "ATTACK_TROOPS";
    break;
  case 3:
    _tlog_line = 0x175;
    pcVar1 = "SEIGE";
    break;
  case 4:
    _tlog_line = 0x178;
    pcVar1 = "EXPLORATION";
    break;
  case 5:
    _tlog_line = 0x17b;
    pcVar1 = "SCRIPTED";
    break;
  case 6:
    _tlog_line = 0x17e;
    pcVar1 = "PERIMETER";
    break;
  case 7:
    _tlog_line = 0x181;
    pcVar1 = "RECON_GOAL";
    break;
  case 8:
    _tlog_line = 0x184;
    pcVar1 = "RESOURCE_GOAL";
    break;
  default:
    _tlog_line = 0x187;
    pcVar1 = "*";
  }
  _tlog_filename = ".\\Schedule\\Mapgrid_Goal.cpp";
  tlog(0x800,pcVar1);
  return;
}
