#include "AwakeBehaviour.h"

#include <iostream>

qe::core::AwakeBehaviour::AwakeBehaviour()
{
}

qe::core::AwakeBehaviour::~AwakeBehaviour()
{
}

void qe::core::AwakeBehaviour::Awake()
{
    std::cout << "awake behaviour  ->  Awake()\n";
}

void qe::core::AwakeBehaviour::Update()
{
    std::cout << "awake behaviour  ->  Update() -----------------\n";
}
