/*
 * StrandTask.h
 *
 *  Created on: Jan 17, 2021
 *      Author: benvh
 */

#ifndef MAIN_STRANDTASK_H_
#define MAIN_STRANDTASK_H_

#define MAX_PARTICLES 10

void chaserTask(void *pvParameters);

typedef enum {
    NONE = 0,
    RANDOMIZE = 1
} ParticleActions;

typedef struct {
    int16_t position;
    int8_t velocity;
    uint8_t color[4];
    uint8_t active;
    ParticleActions action = ParticleActions::NONE;

    void Randomize(uint8_t idx);
} Particle;

class ChaserState : public CommandInterface {
   public:
    ChaserState();

    virtual void inc();
    virtual void dec();
    virtual void randomize();
    virtual void energy(uint8_t energy_level);
    virtual void color_data(uint8_t *color_data);

    void Setup(Configuration *config, uint8_t start_particles);

    uint8_t Update();
    void Draw(DisplayBuffer *displayBuffer);

    uint8_t ActiveParticles() {
        uint8_t result = 0;

        for (uint8_t particle_idx = 0; particle_idx < MAX_PARTICLES;
             particle_idx++) {
            if (particles_[particle_idx].active) {
                result++;
            }
        }
        return result;
    };

    int32_t SignedParticleDelta() {
        return (int32_t)particle_delta_ - particle_delta_offset_;
    };

   private:
    Configuration *configuration_;
    Particle particles_[MAX_PARTICLES];
    uint8_t particle_count_ = 0;
    const int32_t particle_delta_offset_ = 0x7FFFFFFF;
    volatile uint32_t particle_delta_ = particle_delta_offset_;
    uint8_t particle_tail_length_;
    uint16_t max_particle_position_;
    uint16_t energy_level_;
};

#endif /* MAIN_STRANDTASK_H_ */
