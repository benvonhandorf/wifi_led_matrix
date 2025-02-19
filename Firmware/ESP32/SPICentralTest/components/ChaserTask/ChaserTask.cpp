/*
 * ChaserTask.cpp
 *
 *  Created on: Jan 17, 2021
 *      Author: benvh
 */

#include "DisplayBuffer.h"
#include "TaskParameters.h"
#include "esp_log.h"
#include "esp_random.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/atomic.h"
#include "string.h"

#include "Colors.h"

#include "CommandInterface.h"
#include "ChaserTask.h"

#define START_PARTICLES 1

#define TAG "ChaserTask"

void chaserTask(void *pvParameters) {
    ESP_LOGI(TAG, "Task start");

    struct TaskParameters *taskParameters = (TaskParameters *)pvParameters;

    ChaserState *obj = (ChaserState *)taskParameters->user_ctx;

    obj->Setup(taskParameters->configuration, START_PARTICLES);

    DisplayBuffer *display_buffer;
    uint8_t update_result;

    obj->inc();

    ESP_LOGI(TAG, "%p, Delta: %ld", obj, obj->SignedParticleDelta());

    while (1) {
        vTaskDelay(20 / portTICK_PERIOD_MS);

        update_result = obj->Update();

        // if(!update_result) {
        //     ESP_LOGI(TAG, "%d active particles", obj->ActiveParticles());
        //     ESP_LOGI(TAG, "Delta: %ld", obj->SignedParticleDelta());
        // }

        if (xQueueReceive(AVAILABLE_DISPLAY_BUFFER, &display_buffer,
                          portMAX_DELAY) == pdPASS) {
            obj->Draw(display_buffer);
            xQueueSend(COMMITTED_DISPLAY_BUFFER, &display_buffer,
                       portMAX_DELAY);
        } else {
            ESP_LOGW(TAG, "Failed to obtain display buffer");
        }
    }
}

void Particle::Randomize(uint8_t idx) {
    uint32_t velocity_random = esp_random();

    action = ParticleActions::NONE;
    position = 0;
    velocity = ((int8_t)velocity_random & 0x7) * (idx & 0x80 ? -1 : 1);
    velocity = velocity ? velocity : 1;

    random_rgbw_uint8_t(color);

    color[3] /= 8;
}

void ChaserState::Setup(Configuration *config, uint8_t start_particles) {
    configuration_ = config;
    particle_count_ = start_particles;
    particle_tail_length_ = 10;

    max_particle_position_ = configuration_->width + particle_tail_length_;

    ESP_LOGI(TAG, "%p: Starting Particle Count: %d", this, particle_count_);

    for (uint8_t particle_idx = 0; particle_idx < particle_count_;
         particle_idx++) {
        Particle *p = &particles_[particle_idx];
        p->active = 0xFF;
        ESP_LOGI(TAG, "%p/%p, Particle %d is %d", &particles_[particle_idx], p, particle_idx, p->active);
        p->Randomize(particle_idx);
        ESP_LOGI(TAG, "%p/%p, Particle %d is %d", &particles_[particle_idx], p, particle_idx, p->active);
    }

    ESP_LOGI(TAG, "Particle 0: %d", particles_[0].active);
}

uint8_t ChaserState::Update() {
    uint32_t velocity_random;
    uint8_t result = 0;

    for (uint8_t particle_idx = 0; particle_idx < MAX_PARTICLES;
         particle_idx++) {
        if (!particles_[particle_idx].active) {
            if (SignedParticleDelta() > 0) {
                Atomic_Subtract_u32(&particle_delta_, 1);

                particles_[particle_idx].active = 1;
                particles_[particle_idx].Randomize(particle_idx);

                ESP_LOGI(TAG, "Particle %d made active", particle_idx);
            } else {
                continue;
            }
        }

        result++;

        particles_[particle_idx].position += particles_[particle_idx].velocity;
        if (particles_[particle_idx].position < -10
            || particles_[particle_idx].position > max_particle_position_) {
            if (SignedParticleDelta() < 0) {
                Atomic_Add_u32(&particle_delta_, 1);
                particles_[particle_idx].active = 0;

                result--;

                ESP_LOGI(TAG, "Particle %d made inactive", particle_idx);

                continue;
            }

            switch(particles_[particle_idx].action) {
                case ParticleActions::RANDOMIZE:
                    {
                    particles_[particle_idx].Randomize(particle_idx);
                    break;  
                    }
                default:
                    break;
            }

            velocity_random = esp_random();
            if ((velocity_random & 0x3) == 0x3 &&
                particles_[particle_idx].velocity > -10) {
                particles_[particle_idx].velocity -= 1;
                particles_[particle_idx].velocity =
                    particles_[particle_idx].velocity
                        ? particles_[particle_idx].velocity
                        : -1;
            } else if ((velocity_random & 0x1) == 0x1 &&
                       particles_[particle_idx].velocity < -0) {
                particles_[particle_idx].velocity += 1;
                particles_[particle_idx].velocity =
                    particles_[particle_idx].velocity
                        ? particles_[particle_idx].velocity
                        : 1;
            }

            if(particles_[particle_idx].velocity > 0) {
                particles_[particle_idx].position = 0;
            } else {
                particles_[particle_idx].position = configuration_->width;
            }
        } 
    }

    return result;
}

void ChaserState::Draw(DisplayBuffer *displayBuffer) {
    memset(displayBuffer->buffer, 0,
           displayBuffer->width * displayBuffer->height * 4);

    for (uint16_t particle_idx = 0; particle_idx < MAX_PARTICLES;
         particle_idx++) {
        Particle *particle = &particles_[particle_idx];

        if (!particle->active) {
            continue;
        }

        for (uint8_t tail = 0; tail < particle_tail_length_; tail++) {
            int16_t direction = particle->velocity > 0 ? -1 : 1;
            int16_t position = particle->position + (tail * direction);

            if (position > 0 && position < 300) {
                displayBuffer->buffer[(position * 4) + 0] =
                    particle->color[0] / (tail + 1);
                displayBuffer->buffer[(position * 4) + 1] =
                    particle->color[1] / (tail + 1);
                displayBuffer->buffer[(position * 4) + 2] =
                    particle->color[2] / (tail + 1);
                displayBuffer->buffer[(position * 4) + 3] =
                    particle->color[3] / (tail + 1);
            }
        }
    }
}

void ChaserState::inc() { Atomic_Add_u32(&particle_delta_, 1); }

void ChaserState::dec() { Atomic_Subtract_u32(&particle_delta_, 1); }

void ChaserState::randomize() {
    for(auto &p : particles_) {
        p.action = ParticleActions::RANDOMIZE;
    }
}

void ChaserState::energy(uint8_t energy_level) {
    energy_level_ = energy_level;
}

void ChaserState::color_data(uint8_t *color_data) {

}

ChaserState::ChaserState() {
    for (uint8_t particle_idx = 0; particle_idx < MAX_PARTICLES;
         particle_idx++) {
        particles_[particle_idx].active = 0;
    }
}
