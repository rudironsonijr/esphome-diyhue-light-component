#ifdef USE_ARDUINO

#include "diyhue.h"
#include "diyhue_light_effect_base.h"

namespace esphome
{
  namespace diyhue
  {

    DiyHueLightEffectBase::DiyHueLightEffectBase() {}

    void DiyHueLightEffectBase::start()
    {
      if (this->diyhue_)
      {
        this->diyhue_->add_effect(this);
      }
    }

    void DiyHueLightEffectBase::stop()
    {
      if (this->diyhue_)
      {
        this->diyhue_->remove_effect(this);
      }
    }

    // returns true if this effect is timed out
    // next_packet_will_be_first_ variable keeps it from timing out multiple times
    bool DiyHueLightEffectBase::timeout_check()
    {

      // don't timeout if timeout is disabled
      if (this->timeout_ == 0)
      {
        return false;
      }

      // don't timeout if no diyhue stream was ever started
      if (this->next_packet_will_be_first_)
      {
        return false;
      }

      // don't timeout if timeout hasn't been reached
      if ((millis() - this->last_diyhue_time_ms_) <= this->timeout_)
      {
        return false;
      }

      return true;
    }

  } // namespace diyhue
} // namespace esphome

#endif // USE_ARDUINO
