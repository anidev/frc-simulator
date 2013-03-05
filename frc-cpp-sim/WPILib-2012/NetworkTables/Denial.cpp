/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2011. All Rights Reserved.                            */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "NetworkTables/Denial.h"
#include "NetworkTables/Buffer.h"
#include "NetworkTables/InterfaceConstants.h"

namespace NetworkTables
{

Denial::Denial(int count) :
    m_count(count)
{
}

Denial::~Denial()
{
}

void Denial::Encode(Buffer *buffer)
{
    for (int i = m_count; i > 0; i -= kNetworkTables_DENIAL - 1)
        buffer->WriteByte(kNetworkTables_DENIAL | std::min(kNetworkTables_DENIAL - 1, i));
}

// Currently unused
Denial *Denial::Combine(Denial *a, Denial *b)
{
    a->m_count = a->m_count + b->m_count;
    delete b;
    return a;
}

}
