/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2011. All Rights Reserved.                            */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "NetworkTables/TransactionEnd.h"
#include "NetworkTables/Buffer.h"
#include "NetworkTables/InterfaceConstants.h"

namespace NetworkTables
{

TransactionEnd::~TransactionEnd()
{
}

void TransactionEnd::Encode(Buffer *buffer)
{
    buffer->WriteByte(kNetworkTables_TRANSACTION);
}

} // namespace
