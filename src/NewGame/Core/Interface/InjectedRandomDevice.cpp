#include "NewGame/Core/Interface/InjectedRandomDevice.h"

#include <random>

namespace swexp::core::interface
{
    namespace
    {
        std::mt19937 random(0);
        std::uniform_int_distribution<std::mt19937::result_type> randomDistribution(1, 1000);
    }

    void InjectedRandomDevice::init()
    {
        std::random_device randomDevice;
        random.seed(randomDevice());
    }

    void InjectedRandomDevice::init(const uint32_t seed) { random.seed(seed); }

    uint32_t InjectedRandomDevice::next() { return static_cast<uint32_t>(randomDistribution(random)); }
}
