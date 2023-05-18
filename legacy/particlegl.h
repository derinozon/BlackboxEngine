// #include "../src/editor.h"
#include "../blackbox.h"

using namespace Blackbox;
using namespace glm;

struct ParticleData {
    vec3 position;
    vec3 velocity;
    float mass;
};

std::vector<ParticleData> particles;

void Particle() {
    const int particleSize = 64;
    std::srand(Time.time);

    auto spawnParticle = []() {
        float size = RandomRange(1, 5);

        auto particle = CreateQuad("Particle");
        particle->transform.position = RandomBox(5);
        particle->transform.scale *= size * 0.01;
        particle->mesh = LoadObj(std::istringstream(SPHERE_MODEL));
        particle->material.color = RandomColor();

        ParticleData data;
        data.position = particle->transform.position;
        data.velocity = vec3(0.0f);
        data.mass = size;

        particles.push_back(data);
    };

    for (int i = 0; i < particleSize; i++) {
        spawnParticle();
    }

    // Create the compute shader program
	auto src = Resources::ReadFile("compute_shader.glsl");
	const char* shaderSrc = src.c_str();
    Shader computeShaderProgram = Shader(shaderSrc, GL_COMPUTE_SHADER);

    // Create a buffer object to store the particle data
    GLuint particleBuffer;
    glGenBuffers(1, &particleBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, particles.size() * sizeof(ParticleData), particles.data(), GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    // Dispatch the compute shader
    computeShaderProgram.Activate();
    glDispatchCompute(particles.size(), 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    // Retrieve the updated particle data from the buffer
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleBuffer);
    ParticleData* updatedParticles = static_cast<ParticleData*>(glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY));
    if (updatedParticles) {
        for (int i = 0; i < particles.size(); i++) {
            particles[i].position = updatedParticles[i].position;
            particles[i].velocity = updatedParticles[i].velocity;
        }
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    }
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    // Clean up
    glDeleteBuffers(1, &particleBuffer);
    computeShaderProgram.Delete();

    float col = 20.0 / 255.0;
    clearColor = vec4(col, col, col, 1.0);

    OnUpdate += []() {
        // Your rendering and other game update logic here
    };
}
