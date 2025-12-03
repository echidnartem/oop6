#pragma once


#include "npc.h"


class Bandit final: public NPC {
public:
    Bandit() : NPC() {};
    Bandit(const unsigned int x, const unsigned int y, const std::string &name) : NPC(x, y, name) {};

    Bandit(Bandit &&other) noexcept : NPC(std::move(other)) {};
    Bandit(const Bandit &other) = default;

    bool accept(std::shared_ptr<NPC> npc_ptr) const override;

    std::string info() const override;
};