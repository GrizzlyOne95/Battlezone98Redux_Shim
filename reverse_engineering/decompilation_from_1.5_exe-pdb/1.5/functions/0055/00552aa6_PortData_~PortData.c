/*
 * Entry: 00552aa6
 * Name: PortData::~PortData
 * Namespace: PortData
 * Signature: void ~PortData(PortData * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PortData::~PortData(PortData *this)

{
  operator_delete__(this->name);
  return;
}
