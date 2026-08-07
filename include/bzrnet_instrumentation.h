#pragma once

namespace BZROpenShim
{
    // Installs observational BZRNet protocol instrumentation after the existing
    // network optimizer has installed its Winsock hooks. The instrumentation
    // chains through any existing IAT target and does not replace server logic.
    void InitializeBzrNetInstrumentation();
    void ShutdownBzrNetInstrumentation();
}
