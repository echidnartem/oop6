#pragma once


#include "npc.h"


class Elf final: public NPC {
public:
    Elf() : NPC() {};
    Elf(const unsigned int x, const unsigned int y, const std::string &name) : NPC(x, y, name) {};

    Elf(Elf &&other) noexcept : NPC(std::move(other)) {};
    Elf(const Elf &other) = default;

    bool accept(std::shared_ptr<NPC> npc_ptr) const override;

    std::string info() const override;
};