#include "construction_blob_faction.h"
#include "test_check.h"

#include <vector>

using namespace BZROpenShim::ConstructionBlobFaction;
using OpenShimTest::Check;

namespace
{
    struct FakeEngine
    {
        int creates = 0, updates = 0, detaches = 0;
        bool failCreate = false, failUpdate = false;
        int token = 0;
        float lastX = 0.0f;
    };

    bool Create(void* context, int, const BlobPose& pose, void** storage)
    {
        auto& e = *static_cast<FakeEngine*>(context);
        ++e.creates;
        e.lastX = pose.x;
        if (e.failCreate)
            return false;
        *storage = &e.token;
        return true;
    }
    bool Update(void* context, void**, const BlobPose& pose)
    {
        auto& e = *static_cast<FakeEngine*>(context);
        ++e.updates;
        e.lastX = pose.x;
        return !e.failUpdate;
    }
    bool Detach(void* context, void** storage)
    {
        ++static_cast<FakeEngine*>(context)->detaches;
        *storage = nullptr;
        return true;
    }
}

int main()
{
    Check(FactionSlot('a') == 0 && FactionSlot('S') == 1 && FactionSlot('c') == 2 &&
          FactionSlot('b') == 3 && FactionSlot('x') == -1 && FactionSlot('\0') == -1,
          "faction slots follow the ODF first letter");

    {
        const auto keys = ParseOdf("[ConstructionBlob]\r\nblobTexture = \"bpuff.0\"\r\n"
                                   "blobRenderA = \"cnstbla.render\" ; red\r\nBLOBRENDERS='cnstbls'\r\n");
        Check(keys.For(0) == "cnstbla.render" && keys.For(1) == "cnstbls" && keys.For(2).empty() &&
              keys.For(3).empty() && keys.For(-1).empty(),
              "keys ignore case, take quotes, skip comments and leave absent factions stock");
    }
    {
        const auto keys = ParseOdf("[ConstructionBlob]\nblobRender = all.render\nblobRenderC = \"\"\n"
                                   "blobRenderB = \"has space\"\n");
        Check(keys.For(0) == "all.render" && keys.For(1) == "all.render" && keys.For(-1) == "all.render",
              "blobRender is the default for every faction");
        Check(keys.For(2).empty() && keys.For(3).empty(),
              "an empty or invalid faction key forces the stock sprite over the default");
    }
    {
        const auto keys = ParseOdf("blobRenderA=x\n[Other]\nblobRenderC=y\n[constructionblob]\nblobRenderB=z // c");
        Check(keys.For(0).empty() && keys.For(2).empty() && keys.For(3) == "z",
              "only the ConstructionBlob section applies");
    }
    {
        constexpr char terminated[] = "[ConstructionBlob]\nblobRenderC=c.render\0blobRenderA=x";
        const auto keys = ParseOdf(std::string_view(terminated, sizeof(terminated) - 1));
        Check(keys.For(2) == "c.render" && keys.For(0).empty(), "engine item terminator ends the text");
    }
    {
        const std::string longName(64, 'a');
        const auto keys = ParseOdf("[ConstructionBlob]\nblobRenderA=" + longName + "\nblobRenderS=" +
                                   std::string(63, 'b') + "\n");
        Check(keys.For(0).empty() && keys.For(1).size() == 63, "names are 1..63 characters");
    }

    {
        FakeEngine engine;
        const BlobRenderBackend backend = { Create, Update, Detach, &engine };
        BlobRenderPool<2> pool;

        Check(pool.Touch(backend, 0x10, 0x20, 1, { 1, 2, 3 }), "first blob of a build creates its render");
        Check(pool.Touch(backend, 0x10, 0x20, 1, { 4, 2, 3 }), "the same build in the same pass updates");
        Check(engine.creates == 1 && engine.updates == 1 && engine.lastX == 4.0f, "one create, then moves");

        pool.EndPass(backend);
        Check(pool.Touch(backend, 0x10, 0x20, 1, { 5, 2, 3 }) && engine.creates == 1,
              "a build that keeps adding blobs keeps its render across passes");
        pool.EndPass(backend);
        pool.EndPass(backend);
        Check(engine.detaches == 1 && pool.Active() == 0, "a build that stopped is released at the next pass");

        Check(pool.Touch(backend, 0x10, 0x20, 1, {}) && pool.Touch(backend, 0x11, 0x20, 1, {}),
              "two builds fill the pool");
        Check(!pool.Touch(backend, 0x12, 0x20, 1, {}) && engine.creates == 3,
              "a full pool keeps the stock sprite and creates nothing");
        Check(pool.Touch(backend, 0x10, 0x21, 1, {}) == false, "a new target on a full pool is stock too");
        pool.ReleaseAll(backend);
        Check(pool.Active() == 0 && engine.detaches == 3, "release all detaches every live render");

        engine.failCreate = true;
        Check(!pool.Touch(backend, 0x30, 0x40, 2, {}), "a declined create keeps the stock sprite");
        Check(!pool.Touch(backend, 0x30, 0x40, 2, {}) && engine.creates == 4,
              "a declined create is not retried while the build continues");
        pool.EndPass(backend);
        Check(!pool.Touch(backend, 0x30, 0x40, 2, {}) && engine.creates == 4,
              "nor in the next pass");
        pool.EndPass(backend);
        pool.EndPass(backend);
        engine.failCreate = false;
        Check(pool.Touch(backend, 0x30, 0x40, 2, {}) && engine.creates == 5,
              "a later build on the released slot creates again");

        engine.failUpdate = true;
        Check(!pool.Touch(backend, 0x30, 0x40, 2, {}) && engine.detaches == 4,
              "a failed update detaches and falls back to stock");
        engine.failUpdate = false;
        Check(!pool.Touch(backend, 0x30, 0x40, 2, {}) && engine.creates == 5,
              "and the build is not re-created while it continues");

        Check(!pool.Touch(backend, 0x50, 0x60, -1, {}) && !pool.Touch(backend, 0, 0x60, 1, {}),
              "no effect or no owner is stock");

        Check(pool.Touch(backend, 0x70, 0x80, 1, {}) && pool.Active() == 1, "a live render before mission load");
        const int detachesBefore = engine.detaches;
        pool.ReleaseAll(backend);
        pool.Forget();
        Check(pool.Active() == 0 && engine.detaches == detachesBefore + 1 && pool.At(0).owner == 0,
              "mission load releases and forgets every slot");
    }
    return OpenShimTest::ExitCode();
}
