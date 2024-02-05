#pragma once

#ifdef USE_ARDUINO

#include "esphome/core/component.h"
#include "esphome/components/light/light_effect.h"
#include "esphome/components/light/light_output.h"

namespace esphome
{
  namespace diyhue
  {

    class DiyHueComponent;

    enum DiyHueScalingMode
    {
      DIYHUE_NO_SCALING = 0,
      DIYHUE_SCALE_PIXEL = 1,
      DIYHUE_SCALE_STRIP = 2,
      DIYHUE_SCALE_PACKET = 3,
      DIYHUE_SCALE_MULTIPLY = 4
    };

    class DiyHueLightEffectBase
    {
    public:
      DiyHueLightEffectBase();

      virtual const std::string &get_name() = 0;

      virtual void start();
      virtual void stop();
      bool timeout_check();

      void set_diyhue(DiyHueComponent *diyhue) { this->diyhue_ = diyhue; }
      void set_timeout(uint32_t timeout) { this->timeout_ = timeout; }
      void set_disable_gamma(bool disable_gamma) { this->disable_gamma_ = disable_gamma; }
      void set_scaling_mode(DiyHueScalingMode scaling_mode) { this->scaling_mode_ = scaling_mode; }

    protected:
      DiyHueComponent *diyhue_{nullptr};

      uint32_t timeout_{10000};
      uint32_t last_diyhue_time_ms_{0};

      bool disable_gamma_{true};
      float gamma_backup_{0.0};
      bool next_packet_will_be_first_{true};

      DiyHueScalingMode scaling_mode_{DIYHUE_NO_SCALING};

      virtual uint16_t process_(const uint8_t *payload, uint16_t size, uint16_t used) = 0;

      friend class DiyHueComponent;
    };

  } // namespace diyhue
} // namespace esphome

#endif // USE_ARDUINO
