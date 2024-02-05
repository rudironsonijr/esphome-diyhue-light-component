#pragma once

#ifdef USE_ARDUINO

#include "esphome/core/component.h"
#include "esphome/components/light/light_effect.h"
#include "esphome/components/light/light_output.h"
#include "diyhue_light_effect_base.h"

namespace esphome
{
  namespace diyhue
  {

    class DiyHueLightEffect : public DiyHueLightEffectBase, public light::LightEffect
    {
    public:
      DiyHueLightEffect(const std::string &name);

      const std::string &get_name() override;

      void start() override;
      void stop() override;
      void apply() override;

    protected:
      uint16_t process_(const uint8_t *payload, uint16_t size, uint16_t used) override;
    };

  } // namespace diyhue
} // namespace esphome

#endif // ESPHOME_DIYHUE_LIGHT_EFFECT_H
