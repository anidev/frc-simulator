/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2011. All Rights Reserved.                            */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef __TRANSACTION_END_H__
#define __TRANSACTION_END_H__

#include "NetworkTables/Data.h"

namespace NetworkTables
{
class Buffer;

class TransactionEnd : public Data
{
public:
    virtual ~TransactionEnd();
    virtual void Encode(Buffer *buffer);
    virtual bool IsTransaction() {return true;}
};

} // namespace

#endif // __TRANSACTION_END_H__
