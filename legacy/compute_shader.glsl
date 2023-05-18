#version 430

struct ParticleData {
    vec3 position;
    vec3 velocity;
    float mass;
};

layout(std430, binding = 0) buffer ParticleBuffer {
    ParticleData particles[];
};

uniform float deltaTime;
uniform float gravitationalConstant;

layout(local_size_x = 64, local_size_y = 1, local_size_z = 1) in;

void main() {
    uint particleIndex = gl_GlobalInvocationID.x;

    vec3 acceleration = vec3(0.0);

    // Calculate gravitational forces between particles
    for (uint i = 0; i < particles.length(); ++i) {
        if (i != particleIndex) {
            vec3 particlePosition = particles[particleIndex].position;
            vec3 otherParticlePosition = particles[i].position;
            float distance = length(otherParticlePosition - particlePosition);
            vec3 direction = normalize(otherParticlePosition - particlePosition);
            vec3 force = (gravitationalConstant * particles[particleIndex].mass * particles[i].mass) / (distance * distance) * direction;
            acceleration += force / particles[particleIndex].mass;
        }
    }

    // Update particle velocity and position using Verlet integration
    vec3 oldPosition = particles[particleIndex].position;
    vec3 oldVelocity = particles[particleIndex].velocity;
    particles[particleIndex].position += oldVelocity * deltaTime + 0.5 * acceleration * deltaTime * deltaTime;
    particles[particleIndex].velocity = (particles[particleIndex].position - oldPosition) / deltaTime;
}
