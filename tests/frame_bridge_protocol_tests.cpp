#include "frame_bridge_protocol.h"
#include "test_check.h"

int main()
{
    using namespace BZROpenShim::FrameBridge;
    SharedFrame f{};
    f.magic = kMagic;
    f.version = kVersion;
    f.byteSize = sizeof(f);
    f.producerPid = 42;
    f.width = 320;
    f.height = 180;
    f.format = 28;
    f.textureHandle = 0x1234;
    f.readyFenceHandle = 0x5678;
    f.qpcFrequency = 10000000;
    using OpenShimTest::Check;
    Check(ValidDescriptor(f, 42), "valid x86/x64 wire descriptor");
    Check(!ValidDescriptor(f, 43), "reject mismatched producer identity");
    f.version++;
    Check(!ValidDescriptor(f, 42), "reject unsupported ABI");
    f.version = kVersion;
    f.byteSize--;
    Check(!ValidDescriptor(f, 42), "reject truncated descriptor");
    f.byteSize = sizeof(f);
    f.width = 0;
    Check(!ValidDescriptor(f, 42), "reject empty surface");
    f.width = kMaxDimension + 1;
    Check(!ValidDescriptor(f, 42), "bound shared GPU allocation dimensions");
    f.width = 320;
    f.format = 10;
    Check(!ValidDescriptor(f, 42), "reject unsupported HDR format");
    f.format = 87;
    Check(ValidDescriptor(f, 42), "accept BGRA SDR");
    f.textureHandle = 0;
    Check(!ValidDescriptor(f, 42), "reject null resource handle");
    f.textureHandle = 0x1234;
    f.qpcFrequency = 0;
    Check(!ValidDescriptor(f, 42), "reject invalid timestamp scale");
    return OpenShimTest::ExitCode();
}
