#pragma once

#include <map>
#include <vector>

#include "wmath/Vector.h"

class Space
{
public:
    struct Data {
        std::vector<double> masses;
        std::vector<wmath::Vec3d> accelerations;
        std::vector<wmath::Vec3d> colors;
        std::vector<wmath::Vec3d> positions;
        std::vector<wmath::Vec3d> velocities;
    };

    void tick();
    size_t particleCount() const;
    const std::vector<wmath::Vec3d> &accelerations() const;
    const std::vector<wmath::Vec3d> &colors() const;
    const std::vector<wmath::Vec3d> &positions() const;
    const std::vector<wmath::Vec3d> &velocities() const;

    void addParticleData(const wmath::Vec3d &position, const wmath::Vec3d &color, double mass);
    void resetData();
    void reserve(size_t count);

private:
    void applyEffects();
private:
    Data m_data;
};
