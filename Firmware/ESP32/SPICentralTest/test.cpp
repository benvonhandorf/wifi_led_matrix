#include <stdio.h>
#include <stdint.h>

#define MAX_PARTICLES 10

typedef struct {
    uint16_t width;
} Configuration;

typedef struct {
    int16_t position;
    int8_t velocity;
    uint8_t color[4];
    uint8_t active;

    void Randomize(uint8_t idx);
} Particle;

class ChaserState {
   public:
    ChaserState();

    void Setup(Configuration *config, uint8_t start_particles);

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

   private:
    Configuration *configuration_;
    Particle particles_[MAX_PARTICLES];
    uint8_t particle_count_ = 0;
    const int32_t particle_delta_offset_ = 0x7FFFFFFF;
    volatile uint32_t particle_delta_ = particle_delta_offset_;
    uint8_t particle_tail_length_;
    uint16_t max_particle_position_;
};

ChaserState::ChaserState() {
    for (uint8_t particle_idx = 0; particle_idx < MAX_PARTICLES;
         particle_idx++) {
        particles_[particle_idx].active = 0;
    }

    particle_tail_length_ = 4;
}

void ChaserState::Setup(Configuration *config, uint8_t start_particles) {
    configuration_ = config;
    particle_count_ = start_particles;
    particle_tail_length_ = 10;

    max_particle_position_ = configuration_->width + particle_tail_length_;

    printf("%p: Starting Particle Count: %d\n", this, particle_count_);

    for (uint8_t particle_idx = 0; particle_idx < particle_count_;
         particle_idx++) {
        Particle *p = &particles_[particle_idx];
        p->active = 0xFF;
        printf("%p/%p, Particle %d is %d\n", &particles_[particle_idx], p, particle_idx, p->active);
    }

    printf("Particle 0: %d\n", particles_[0].active);
}

int main() {
    Configuration configuration = { .width = 300 };
    
    ChaserState chaser_state;

    chaser_state.Setup(&configuration, 4);
}