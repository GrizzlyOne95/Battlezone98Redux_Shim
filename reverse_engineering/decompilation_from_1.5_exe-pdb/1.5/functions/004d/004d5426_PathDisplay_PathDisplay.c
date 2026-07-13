/*
 * Entry: 004d5426
 * Name: PathDisplay::PathDisplay
 * Namespace: PathDisplay
 * Signature: PathDisplay * PathDisplay(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathDisplay * __thiscall PathDisplay::PathDisplay(PathDisplay *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::AddView((DisplayInterface *)this,9,-1);
  this->buildTeam = -1;
  this->teamMode = TEAM_NORMAL;
  this->buildItem = &buildMenu;
  return this;
}
