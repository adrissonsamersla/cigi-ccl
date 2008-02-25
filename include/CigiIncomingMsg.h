/** <pre>
 *  The SDK is used to create and format CIGI compliant messages.
 *  Copyright (c) 2001-2005 The Boeing Company
 *  
 *  This library is free software; you can redistribute it and/or modify it 
 *  under the terms of the GNU Lesser General Public License as published by 
 *  the Free Software Foundation; either version 2.1 of the License, or (at 
 *  your option) any later version.
 *  
 *  This library is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser Public License for more 
 *  details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License 
 *  along with this library; if not, write to the Free Software Foundation, 
 *  Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *  
 *  FILENAME:   CigiIncomingMsg.h
 *  LANGUAGE:   C++
 *  CLASS:      UNCLASSIFIED
 *  PROJECT:    Common Image Generator Interface (CIGI) SDK
 *  
 *  PROGRAM DESCRIPTION: 
 *  ...
 *  
 *  MODIFICATION NOTES:
 *  DATE     NAME                                SCR NUMBER
 *  DESCRIPTION OF CHANGE........................
 *  
 *  09/17/2003 Greg Basler                       CIGI_CR_DR_1
 *  Initial Release.
 *  
 *  01/21/2005 Greg Basler                       Version 1.5
 *  Added the CIGI_SPEC modifier to the class declaration for exporting the 
 *  class in a Windows DLL.
 *  
 *  07/05/2005 Greg Basler                       Version 1.5.4
 *  Noted that the ProcessIncomingMsg function can throw exceptions, listed 
 *  in the comments section of the method.
 *
 *  10/28/2005 Greg Basler                       Version 1.5.7
 *  Corrected the description for SetReaderCigiVersion.
 *  
 *  04/14/2006 Greg Basler                       Version 1.7.0
 *  Added the GetReaderCigiMinorVersion accessor method.
 *  
 *  04/14/2006 Greg Basler                       Version 1.7.0
 *  Added an overloaded SetReaderCigiVersion method to accept a 
 *  CigiMinorVersionIn parameter.
 *  
 *  04/14/2006 Greg Basler                       Version 1.7.0
 *  Updated the existing SetReaderCigiVersion method to call the new 
 *  implementation with a default version number of 0.
 *  
 *  06/23/2006 Greg Basler                       Version 1.7.1
 *  Changed native char and unsigned char types to CIGI types Cigi_int8 and 
 *  Cigi_uint8.
 * </pre>
 *  Author: The Boeing Company
 *  Version: 1.7.5
 */

#if !defined(_CIGI_INCOMING_MESSAGE_INCLUDED_)
#define _CIGI_INCOMING_MESSAGE_INCLUDED_

#include <stdlib.h>
#include "CigiMessage.h"
#include "CigiBaseEventProcessor.h"
#include "CigiEventList.h"
#include "CigiBaseSignalProcessing.h"


//=========================================================
//! The class for incoming messages
//!
class CIGI_SPEC CigiIncomingMsg : public CigiMessage  
{
public:


   //==> Management

   //=========================================================
   //! General Constructor
   //!
   CigiIncomingMsg();

   //=========================================================
   //! General Destructor
   //!
	virtual ~CigiIncomingMsg();




   //==> Processing Member functions


   //+> Processing Incoming Messages

   //=========================================================
   //! This processes the incoming message contained in a
   //!   user supplied buffer.<br>
   //! This routine can throw a CigiMissingIgControlException or
   //!   CigiMissingStartOfFrameException exception.
   //! \param Buff - Pointer to the beginning of the message
   //!    in a user supplied buffer.
   //! \param Size - Size in bytes of the message
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
	int ProcessIncomingMsg(Cigi_uint8 *Buff, int Size);

   //=========================================================
   //! This processes the incoming message using the internal buffer
   //! This can also throw the following exceptions:
   //!  - CigiMissingStartOfFrameException
   //!  - CigiMissingIgControlException
   //!  - CigiBufferOverrunException
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
	int ProcessIncomingMsg(void)
   {

      return( ProcessIncomingMsg(BasePtr[CrntMsgBuf],
                                 BuffFillCnt[CrntMsgBuf]));
   }


   //+> Interative packet processing method calls

   //=========================================================
   //! This gets the first packet of the message
   //!
   //! \return This returns a pointer to the first message
   //!
	CigiBasePacket * GetFirstPacket(void);

   //=========================================================
   //! This gets the next packet of the message
   //!
   //! \return This returns a pointer to the next message
   //!
	CigiBasePacket * GetNextPacket(void);


   //+> Packet Processor Management

   //=========================================================
   //! This places the specifed event method processor into
   //!   the event processor list for this packet.
   //! \param PacketID - The Packet ID to which the specified
   //!    event processor will be linked.
   //! \param EventMgr - A pointer to the event processor
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
	int RegisterEventProcessor(int PacketID,
                              CigiBaseEventProcessor *EventMgr);

   //=========================================================
   //! This removes the specifed event method processor from
   //!   the event processor list for this packet.
   //! \param PacketID - The Packet ID to which the specified
   //!    event processor is currently linked.
   //! \param EventMgr - A pointer to the event processor
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
	int UnregisterEventProcessor(int PacketID,
                              CigiBaseEventProcessor *EventMgr);


   //=========================================================
   //! This places the specifed callback method processor into
   //!   the callback processor list for this packet.
   //! \param PacketID - The Packet ID to which the specified
   //!    callback processor will be linked.
   //! \param CallBack - A pointer to the callback processor
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
   int RegisterCallBack(int PacketID, CigiCBProcessor CallBack);

   //=========================================================
   //! This removes the specifed callback method processor from
   //!   the callback processor list for this packet.
   //! \param PacketID - The Packet ID to which the specified
   //!    callback processor is currently linked.
   //! \param CallBack - A pointer to the callback processor
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
   int UnregisterCallBack(int PacketID, CigiCBProcessor CallBack);


   //=========================================================
   //! This places the specifed signal method processor into
   //!   the event processor list.
   //! \param SignalMgr - A pointer to the signal processor
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
   int RegisterSignalProcessor(CigiBaseSignalProcessing *SignalMgr);

   //=========================================================
   //! This removes the specifed signal method processor from
   //!   the signal processor list.
   //! \param SignalMgr - A pointer to the event processor
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
   int UnregisterSignalProcessor(CigiBaseSignalProcessing *SignalMgr);


   //=========================================================
   //! This places the specifed event method processor into
   //!   the unrecognized event processor list.
   //! \param EventMgr - A pointer to the event processor
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
   int RegisterUnrecognizedPacketEvent(CigiBaseEventProcessor *EventMgr)
   {
	return(RegisterEventProcessor(0,EventMgr));
   }

   //=========================================================
   //! This removes the specifed Event method processor from
   //!   the unrecognized Event processor list.
   //! \param EventMgr - A pointer to the event processor
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
   int UnregisterUnrecognizedPacketEvent(CigiBaseEventProcessor *EventMgr)
   {
      return(UnregisterEventProcessor(0,EventMgr));
   }


   //=========================================================
   //! This places the specifed CallBack method processor into
   //!   the unrecognized CallBack processor list.
   //! \param CallBack - A pointer to the CallBack processor
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
   int RegisterUnrecognizedPacketCallBack(CigiCBProcessor CallBack)
   {
      return(RegisterCallBack(0,CallBack));
   }

   //=========================================================
   //! This removes the specifed CallBack method processor from
   //!   the unrecognized CallBack processor list.
   //! \param CallBack - A pointer to the CallBack processor
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
   int UnregisterUnrecognizedPacketCallBack(CigiCBProcessor CallBack)
   {
      return(UnregisterCallBack(0,CallBack));
   }

   //=========================================================
   //! This places the specifed Event method processor into
   //!   the unhandled Event processor list.
   //! \param EventMgr - A pointer to the event processor
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
   int RegisterUnhandledPacketEvent(CigiBaseEventProcessor *EventMgr)
   {
	return(RegisterEventProcessor(256,EventMgr));
   }

   //=========================================================
   //! This removes the specifed signal method processor from
   //!   the signal processor list.
   //! \param EventMgr - A pointer to the event processor
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
   int UnregisterUnhandledPacketEvent(CigiBaseEventProcessor *EventMgr)
   {
      return(UnregisterEventProcessor(256,EventMgr));
   }


   //=========================================================
   //! This places the specifed CallBack method processor into
   //!   the unhandled callback processor list.
   //! \param CallBack - A pointer to the CallBack processor
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
   int RegisterUnhandledPacketCallBack(CigiCBProcessor CallBack)
   {
      return(RegisterCallBack(256,CallBack));
   }

   //=========================================================
   //! This removes the specifed CallBack method processor from
   //!   the unhandled callback processor list.
   //! \param CallBack - A pointer to the CallBack processor
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
   int UnregisterUnhandledPacketCallBack(CigiCBProcessor CallBack)
   {
      return(UnregisterCallBack(256,CallBack));
   }


   //==> Buffer Packing Managers


   //=========================================================
   //! Gets a pointer to the next Message buffer to be used to
   //!   input a message.
   //! \return This returns a pointer to the next Message buffer.
   //!
   Cigi_uint8 *GetNextBuffToLoad(void);

   //=========================================================
   //! Advances the message buffer index to the next Message buffer
   //!   to be used to process a message.
   //!
   void AdvanceCrntBuffer(void);

   //=========================================================
   //! Sets the size of the message in the Current fill buffer.
   //! \param MsgSize - the size (in bytes) of the message just 
   //!   placed into the current message fill buffer.
   //!
   void SetCrntMsgSize(int MsgSize)
   {
      BuffFillCnt[CrntFillBuf] = (MsgSize <= BufferSize) ? MsgSize : BufferSize;
   }



   //==> Accessing Member Variable Values functions

   //=========================================================
   //! Gets a pointer to the current Message buffer.
   //! \return the pointer to the Message buffer
   //!
   Cigi_uint8 * GetMsgBuffer()
   {
      return(BasePtr[CrntMsgBuf]);
   }

   //=========================================================
   //! Sets the size of the message in the Current fill buffer.
   //! \return This returns the message buffer size
   //!
   int GetMsgBufSize(void) { return(BufferSize); }


   //+> Iteration Method Flag

   //=========================================================
   //! Sets the flag specifying whether the Iteration method is being used.
   //! \param IterationIn - Iteration method flag.<br>
   //!  true - The Iteration method is being used.<br>
   //!  false - The Callback, Event, (and/or) Signal method(s) 
   //!    (is/are) used.
   //!
   void UsingIteration(bool IterationIn=true) { Iteration = IterationIn; }

   //=========================================================
   //! Gets the flag specifying whether the Iteration method is being used.
   //! \return - Iteration method flag.<br>
   //!  true - The Iteration method is being used.<br>
   //!  false - The Callback, Event, (and/or) Signal method(s) 
   //!    (is/are) used.
   //!
   bool CheckIteration(void) { return(Iteration); }


   //+> Reader's CIGI Version

   //=========================================================
   //! Sets the CIGI version that the reader is using.
   //! \param CigiVersionIn - The CIGI version to which the application
   //!   is coded.<br>
   //! \param bndchk - Enables (true) or disables (false) bounds checking
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
   int SetReaderCigiVersion(const int CigiVersionIn, bool bndchk=true)
   {
      return(VJmp->SetReaderCigiVersion(CigiVersionIn,0,bndchk));
   }

   //=========================================================
   //! Sets the CIGI version that the reader is using.
   //! \param CigiVersionIn - The CIGI version to which the application
   //!   is coded.<br>
   //! \param CigiMinorVersionIn - The CIGI minor version to which the application
   //!   is coded.<br>
   //! \param bndchk - Enables (true) or disables (false) bounds checking
   //!
   //! \return This returns CIGI_SUCCESS or an error code 
   //!   defined in CigiErrorCodes.h
   //!
   int SetReaderCigiVersion(const int CigiVersionIn, const int CigiMinorVersionIn, bool bndchk=true)
   {
      return(VJmp->SetReaderCigiVersion(CigiVersionIn,CigiMinorVersionIn,bndchk));
   }

   //=========================================================
   //! Gets the CIGI version that the reader is using.
   //! \return The CIGI version that the Reader is using.
   //!
   int GetReaderCigiVersion(void) const
   {
      return(VJmp->GetReaderCigiVersion());
   }

   //=========================================================
   //! Gets the Reader's Cigi Minor Version.
   //! \return the Cigi Minor Version of the reader and processing routines.
   //!
   int GetReaderCigiMinorVersion(void) const { return(VJmp->GetReaderCigiMinorVersion()); }



protected:

   //==> Member variables

   //=========================================================
   //! Iteration<br>
   //! Specifies whether the Iteration method is being used<br>
   //!  true - The Iteration method is being used.<br>
   //!  false - The Callback, Event, (and/or) Signal method(s) 
   //!    (is/are) used.
   //!
   bool Iteration;

   //=========================================================
   //! MsgStart<br>
   //! A pointer to the first byte of the message.
   //!
   Cigi_uint8 *MsgStart;

   //=========================================================
   //! CrntPacket<br>
   //! A pointer to the first byte of the current packet.
   //!
   Cigi_uint8 *CrntPacket;

   //=========================================================
   //! ReadBufferPos<br>
   //! An index into the message buffer specifying where the
   //!   the next byte to be read is.
   //!
   int ReadBufferPos;

   //=========================================================
   //! MsgSize<br>
   //! The current message size.
   //!
   int MsgSize;

   //=========================================================
   //! CallBackList<br>
   //! The table of Callback lists.
   //!
   CigiEventList *CallBackList[257];

   //=========================================================
   //! EventList<br>
   //! The table of Event lists.
   //!
   CigiEventList *EventList[257];

   //=========================================================
   //! SignalList<br>
   //! The beginning of the Signal list.
   //!
   CigiEventList *SignalList;

   //=========================================================
   //! Swap<br>
   //! Specifies when the message must be byte swapped.
   //!
   bool Swap;

   //=========================================================
   //! MostMatureCigiVersionReceived<br>
   //! Specifies the most mature (i.e. newest version) of CIGI received.
   //!
   int MostMatureCigiVersionReceived;

   //=========================================================
   //! IterationVersion<br>
   //! Specifies the current version of CIGI being used for iteration.
   //!
   int IterationVersion;


   //==> Member protected functions

   //=========================================================
   //! This takes the packet id and determines which signal method
   //!   to call.  It then goes through the signal list and calls
   //!   the correct signal method in each of the signal objects.
   //! \param PacketID - The Packet ID of the message to be processed.
   //! \param Packet - A pointer to the packet object that has
   //!    parsed the current message packet.
   //!
   bool SignalJump(const Cigi_uint8 PacketID, CigiBasePacket *Packet);

};

#endif // !defined(_CIGI_INCOMING_MESSAGE_INCLUDED_)
